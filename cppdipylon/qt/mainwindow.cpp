/*******************************************************************************

    DipylonReader Copyright (C) 2008 Xavier Faure
    Contact: faure dot epistulam dot mihi dot scripsisti at orange dot fr

    This file is part of DipylonReader.
    DipylonReader is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    DipylonReader is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with DipylonReader.  If not, see <http://www.gnu.org/licenses/>.

    ____________________________________________________________________________

    ❏DipylonReader❏ : qt/mainwindow.cpp

    see mainwindow.h for the documentation

*******************************************************************************/

#include "qt/mainwindow.h"

/*______________________________________________________________________________

  MainWindow::constructor

______________________________________________________________________________*/
MainWindow::MainWindow(UI& _ui,
                       QWidget *_parent) : QMainWindow(_parent),
                                           ui(_ui) {
  this->setObjectName("main_window");
  // DEBUG1 DebugMsg() << "[MainWindow::MainWindow] this->setStyleSheet = "
  // DEBUG1            << fixedparameters::default__mainwindow_stylesheet;
  this->setStyleSheet(fixedparameters::default__mainwindow_stylesheet);

  #ifdef NO_STATUS_BAR
  this->setStatusBar(0);
  #endif

  // giving the focus so that keyboard shortcuts allow to access the main menu :
  this->setFocus(Qt::MenuBarFocusReason);
}

/*______________________________________________________________________________

  MainWindow::about
______________________________________________________________________________*/
void MainWindow::about(void) {
  // presentation screen message :
  QString msg = QString("<span style=\"color:#000000\">");

  msg += "\n\n";

  msg += QString(QObject::tr("<b>%1</b> %2, "
                        "a software by %3.<br/><br/>"
                        "  This program is covered by the <b>%4</b> "
                        "(<a href='%5'>%5</a>) license : "
                        "checkout the code of the project at the following "
                        "<a href='%6'>address</a>.").arg(fixedparameters::application_name_for_the_user,
                                                         fixedparameters::application_version,
                                                         fixedparameters::CODESOURCE_AUTHOR,
                                                         fixedparameters::CODESOURCE_LICENSE,
                                                         fixedparameters::CODESOURCE_LICENSE_ADDRESS,
                                                         fixedparameters::CODESOURCE_ADDRESS));

  this->ui.presentation_screen_launcher.launch(msg, this->geometry());
}

/*______________________________________________________________________________

  SCTabs::cleaning_up_tabs_before_changing_current_tab

  Function called when the current tab has changed.
______________________________________________________________________________*/
void MainWindow::cleaning_up_tabs_before_changing_current_tab(void) {
  // DEBUG1 DebugMsg() << "MainWindow::cleaning_up_tabs_before_changing_current_tab";

  /*
    if in 'lmode', we stop all the audio readings :
  */
  for (int index = 0; index < this->sctabs->count(); ++index) {
    SCSplitter* splitter = qobject_cast<SCSplitter*>(this->sctabs->widget(index));
    if (splitter->readingmode == READINGMODE::READINGMODE_LMODE) {
      splitter->readingmode_details = READINGMODEDETAIL_LMODE_STOP;
      splitter->source_zone->audio_player->stop();
    }
  }
}

/*______________________________________________________________________________

  MainWindow::closeEvent

  Function called when the main window is closed.
______________________________________________________________________________*/
void MainWindow::closeEvent(QCloseEvent *arg_event) {
  // DEBUG1 DebugMsg() << "MainWindow::closeEvent";
  arg_event->accept();
}

/*______________________________________________________________________________

  MainWindow::closing

  from the doc of QCoreApplication::exec:

  |   We recommend that you connect clean-up code to the aboutToQuit() signal,
  |  instead of putting it in your application's main() function because on some
  |  platforms the QCoreApplication::exec() call may not return. For example,
  |  on Windows when the user logs off, the system terminates the process after
  |  Qt closes all top-level windows. Hence, there is no guarantee that the
  |  application will have time to exit its event loop and execute code at the
  |  end of the main() function after the QCoreApplication::exec() call.

  See e.g. http://stackoverflow.com/questions/8165487/how-to-do-cleaning-up-on-exit-in-qt
________________________________________________________________________________*/
void MainWindow::closing(void) {
  // DEBUG1 DebugMsg() << "MainWindow::closing : entry point";

  // DEBUG1 DebugMsg() << "(MainWindow::closing) calling SCSPlitter::write_settings()";
  for (int index = 0; index < this->sctabs->count(); ++index) {
    SCSplitter* splitter = qobject_cast<SCSplitter*>(this->sctabs->widget(index));
    splitter->write_settings();
  }

  // DEBUG1 DebugMsg() << "(MainWindow::closing) calling UI::write_settings()";
  this->ui.write_settings();

  // DEBUG1 DebugMsg() << "(MainWindow::closing) about to delete all dipydocs still opened";
  for (int splitter_index =0; splitter_index < this->sctabs->count(); ++splitter_index) {
    // DEBUG1 DebugMsg() << "(MainWindow::closing) about to delete "
    // DEBUG1            << qobject_cast<SCSplitter*>(this->sctabs->widget(splitter_index))->dipydoc->menu_name;
    delete qobject_cast<SCSplitter*>(this->sctabs->widget(splitter_index))->dipydoc;
  }

  // DEBUG1 DebugMsg() << "MainWindow::closing : exit point";
}

/*______________________________________________________________________________

  MainWindow::createActions
______________________________________________________________________________*/
void MainWindow::createActions(void) {
  // DEBUG1 DebugMsg() << "MainWindow::createActions : entry point";

  /*
    aboutAct
  */
  this->aboutAct = new QAction(tr("&About"), this);
  this->aboutAct->setStatusTip(tr("Show the application's About box"));
  // connection #C015 (confer documentation)
  QObject::connect(this->aboutAct, &QAction::triggered,
                   this,           &MainWindow::about);

  /*
    downloaddemoAct
  */
  this->downloaddemoAct = new QAction( *(icons.downloaddemo),
                                       tr("Download demo Dipydocs"),
                                 this);
  this->downloaddemoAct->setStatusTip(tr("Download demo Dipydocs/statustip"));
  // connection #C016 (confer documentation)
  QObject::connect(this->downloaddemoAct, &QAction::triggered,
                   this,                  &MainWindow::download_dipydocs_demo);

  /*
    exitAct
  */
  this->exitAct = new QAction(tr("E&xit"), this);
  this->exitAct->setShortcuts(QKeySequence::Quit);
  this->exitAct->setStatusTip(tr("Exit the application"));
  // connection #C017 (confer documentation)
  QObject::connect(this->exitAct, &QAction::triggered,
                   this,          &MainWindow::close);

  /*
    hidetoolbarsAct
  */
  this->hidetoolbarsAct = new QAction( *(icons.hide_toolbars_on),
                                       tr("hide toolbars"),
                                       this);
  this->hidetoolbarsAct->setStatusTip(tr("hide the editors' toolbars"));
  // connection #C018 (confer documentation)
  QObject::connect(this->hidetoolbarsAct, &QAction::triggered,
                   this,                  &MainWindow::hidetoolbarsAct__buttonPressed);

  /*
    internalmsgAct
  */
  this->internalmsgAct = new QAction( *(icons.app),
                                       tr("internal messages"),
                                       this);
  this->internalmsgAct->setStatusTip(tr("internal messages"));
  // connection #C019 (confer documentation)
  QObject::connect(this->internalmsgAct, &QAction::triggered,
                   this,                 &MainWindow::internalmsgAct__buttonPressed);

  /*
    openAct
  */
  this->openAct = new QAction( *(icons.open),
                               tr("Open"),
                               this);
  openAct->setShortcuts(QKeySequence::Open);
  openAct->setStatusTip(tr("Open an existing DipyDoc"));
  // connection #C020 (confer documentation)
  QObject::connect(this->openAct, &QAction::triggered,
                   this,          &MainWindow::open);

  /*
    popup_mainmenuAct
  */
  #ifndef NO_MAIN_POPUPMENU
  this->popup_mainmenuAct = new QAction( *(icons.popup_mainmenu),
                                         tr("display the main pop menu"),
                                         this);
  // connection #C021 (confer documentation)
  QObject::connect(this->popup_mainmenuAct, &QAction::triggered,
                   this,                    &MainWindow::popup_mainmenuAct__buttonPressed);
  #endif

  // DEBUG1 DebugMsg() << "MainWindow::createActions : exit point";
}

/*______________________________________________________________________________

  MainWindow::createMenus

  o  main menu
  o  main popup menu
______________________________________________________________________________*/
void MainWindow::createMenus(void) {
  // DEBUG1 DebugMsg() << "MainWindow::createMenus : entry point";

  /*
    main menu :
  */
  this->fileMenu = menuBar()->addMenu(tr("&File"));
  this->openMenu = fileMenu->addMenu(tr("Open"));

  this->fill_open_menu();

  this->fileMenu->addSeparator();

  this->fileMenu->addAction(downloaddemoAct);

  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);

  menuBar()->addSeparator();

  helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAct);
  #ifdef MENUACCESS_TO_INTERNAL_MESSAGES
  menuBar()->addSeparator();
  helpMenu->addAction(internalmsgAct);
  #endif

  /*
    main popup menu :
  */
  #ifndef NO_MAIN_POPUPMENU
  this->mainpopupmenu = new QMenu();
  this->mainpopupmenu->addMenu(this->openMenu);
  this->mainpopupmenu->addAction(downloaddemoAct);
  this->mainpopupmenu->addSeparator();
  this->mainpopupmenu->addAction(exitAct);
  this->mainpopupmenu->addAction(aboutAct);
  #endif

  // DEBUG1 DebugMsg() << "MainWindow::createMenus : exit point";
}

/*______________________________________________________________________________

  MainWindow::createStatusBar
______________________________________________________________________________*/
void MainWindow::createStatusBar(void) {
#ifndef NO_STATUS_BAR
  statusBar()->showMessage(tr("Ready"));
#endif
}

/*______________________________________________________________________________

  MainWindow::createMainToolBars
______________________________________________________________________________*/
void MainWindow::createMainToolBars(void) {
  // DEBUG1 DebugMsg() << "MainWindow::createMainToolBars : entry point";

  this->mainwintoolbar = this->addToolBar(tr("main toolbar"));

  this->mainwintoolbar->setObjectName("main_window__main_toolbar");

  #ifndef NO_MAIN_POPUPMENU
  this->mainwintoolbar->addAction(this->popup_mainmenuAct);
  #endif
  this->mainwintoolbar->addAction(this->openAct);
  this->mainwintoolbar->addAction(this->hidetoolbarsAct);

  // DEBUG1 DebugMsg() << "MainWindow::createMainToolBars : exit point";
}

/*______________________________________________________________________________

  MainWindow::current_splitter
______________________________________________________________________________*/
SCSplitter* MainWindow::current_splitter(void) {
  return qobject_cast<SCSplitter*>(this->sctabs->currentWidget());
}

/*______________________________________________________________________________

  MainWindow::download_dipydocs_demo

  This function removes old demo files, then download and install the new ones.
______________________________________________________________________________*/
void MainWindow::download_dipydocs_demo(void) {
  // using the DownloadDemoDipydocs class to download the files :
  DownloadDemoDipydocs d(this->ui, this);

  // update menu names :
  this->ui.read_menu_names();
  this->fill_open_menu();
}

/*______________________________________________________________________________

  MainWindow::fill_open_menu

  Fill the Open menu with the available dipydocs, whose name are stored in
  this->ui.available_menu_names .
______________________________________________________________________________*/
void MainWindow::fill_open_menu(void) {
  // DEBUG1 DebugMsg() << "MainWindow::fill_open_menu : entry point";

  /*
    let's clear the menu content :
  */
  this->openMenu->clear();

  /*
    special case : no dipydoc could be found.
  */
  if (this->ui.available_menu_names.size() == 0) {
    // DEBUG1 DebugMsg() << "MainWindow::fill_open_menu : no dipydoc";
    QAction* emptyAction = new QAction(*icons.app,
                                       "(No Dipydoc could be found)",
                                       this);
    this->openMenu->addAction(emptyAction);

    openMenu->addSeparator();
    this->openMenu->addAction(openAct);
    return;
  }

  /*
    normal case : at least one dipydoc was found.
  */
  int number_of_items = 0;
  for (auto &item : this->ui.available_menu_names) {
    // DEBUG1 DebugMsg() << "MainWindow::fill_open_menu : found " << item.first;
    number_of_items++;

    if (number_of_items <= fixedparameters::maximum_number_of_items_in_submenu_open) {
      QAction* newAction = new QAction(*icons.app,
                                       item.first,
                                       this);
      /*
         see MainWindow::load_a_dipydoc_from_a_qaction() for the format of the
         internal data.
      */
      newAction->setData(item.second);

      this->openMenu->addAction(newAction);
      // connection #C022 (confer documentation)
      QObject::connect(newAction, &QAction::triggered,
                       this,      &MainWindow::load_a_dipydoc_from_a_qaction);
    } else {
      break;
    }
  }

  /*
    we add the "open other file(s)" element :
  */
  if (this->ui.available_menu_names.size() <= fixedparameters::maximum_number_of_items_in_submenu_open) {
    openMenu->addSeparator()->setText(tr("choose other files :"));
    openMenu->addAction(openAct);
  } else {
    openMenu->addSeparator()->setText(tr("(...)"));
    openMenu->addSeparator()->setText(tr("choose other files :"));
    openMenu->addAction(openAct);
  }

  // DEBUG1 DebugMsg() << "MainWindow::fill_open_menu : exit point";
}

/*______________________________________________________________________________

  MainWindow::hidetoolbarsAct__buttonPressed
______________________________________________________________________________*/
void MainWindow::hidetoolbarsAct__buttonPressed(void) {
  this->visible_toolbars = !this->visible_toolbars;
  this->update_icons();
}

/*______________________________________________________________________________

  MainWindow::init()
______________________________________________________________________________*/
void MainWindow::init(void) {
  // DEBUG1 DebugMsg() << "MainWindow::init() : entry point";

  /*
       The actions created by the the call to createActions() method are
       required by the rest of this function :
  */
  this->createActions();

  this->sctabs = new SCTabs(this);

  // connection #C023 (confer documentation)
  QObject::connect(this->sctabs,          &SCTabs::signal__open_a_new_dipydoc,
                   this,                  &MainWindow::open);

  // connection #C024 (confer documentation)
  QObject::connect(this->sctabs,          &SCTabs::signal__display_hidetoolbar_icon,
                   this->hidetoolbarsAct, &QAction::setVisible);

  // connection #C025 (confer documentation)
  QObject::connect(this->sctabs,          &SCTabs::currentChanged,
                   this,                  &MainWindow::cleaning_up_tabs_before_changing_current_tab);

  this->setCentralWidget(this->sctabs);

  this->createMenus();
  this->createMainToolBars();
  #ifndef NO_STATUS_BAR
  this->createStatusBar();
  #endif

  this->readSettings();

  /*
    let's update the icons' appearence :
  */
  this->update_icons();

  this->setUnifiedTitleAndToolBarOnMac(true);

  /*
    initialization of the network manager :
  */
  this->ui.network_manager = new QNetworkAccessManager(this);
  // DEBUG1 DebugMsg() << "network_manager.networkAccessible (1 if ok, 0 if not ok, -1 if unknown) ="
  // DEBUG1            << static_cast<int>(this->ui.network_manager->networkAccessible());

  // DEBUG1 DebugMsg() << "MainWindow::exit() : entry point";
}

/*______________________________________________________________________________

  MainWindow::internalmsgAct__buttonPressed
______________________________________________________________________________*/
void MainWindow::internalmsgAct__buttonPressed(void) {
  SCSplitter* splitter = this->current_splitter();

  QMessageBox msgBox;

  msgBox.setText("Internal messages are used to debug the program. See details below.");

  if (splitter == nullptr) {
    msgBox.setDetailedText(QString("(no messages linked to a DipyDoc : this->current_splitter==nullptr)") + \
                           QString("\n\n\n*** internal debug message ***\n\n\n") + \
                           DebugMsg::messages.join("\n"));
  } else {
    msgBox.setDetailedText("internal state = " + QString().setNum(splitter->dipydoc->internal_state()) +
                           splitter->dipydoc->err_messages.join("\n\n") + \
                           "\n\n\n*** internal debug message ***\n\n\n" + \
                           DebugMsg::messages.join("\n"));
  }
  msgBox.exec();
}

/*______________________________________________________________________________

  MainWindow::load_a_dipydoc_from_a_qaction

  Load a Dipydoc from a QAction with the path stored in the internal data.
______________________________________________________________________________*/
void MainWindow::load_a_dipydoc_from_a_qaction(void) {
  QAction* action = qobject_cast<QAction*>(this->sender());
  this->loadDipyDoc(action->data().toString());
}

/*______________________________________________________________________________

  MainWindow::loadDipyDoc() : load a DipyDoc from the path "directoryName"
  and set this DipyDoc as the current one.

  This function creates a new SCSplitter object.
______________________________________________________________________________*/
void MainWindow::loadDipyDoc(const QString &directoryName) {
  // DEBUG1 DebugMsg() << "MainWindow::loadDipyDoc" << directoryName;

  SCSplitter* source_commentary_splitter = new SCSplitter(this->sctabs->count(),
                                                          directoryName,
                                                          this->visible_toolbars,
                                                          this->sctabs);

  if (source_commentary_splitter->well_initialized() == false) {
    // DEBUG1 DebugMsg() << "MainWindow::loadDipyDoc : error -> deleting the splitter and its DipyDoc :";
    delete source_commentary_splitter;
  } else {
    // DEBUG1 DebugMsg() << "MainWindow::loadDipyDoc : ok";
    this->sctabs->addTab(source_commentary_splitter,
                         source_commentary_splitter->dipydoc->get_tab_name());

    this->sctabs->setCurrentWidget(source_commentary_splitter);
  }
}

/*______________________________________________________________________________

  MainWindow::open
______________________________________________________________________________*/
void MainWindow::open(void) {
  QString directoryName = QFileDialog::getExistingDirectory(this,
                                    QObject::tr("Open a DipyDoc directory"),
                                    this->ui.path_to_dipydocs,
                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (!directoryName.isEmpty()) {
    // loading the DipyDoc :
    this->loadDipyDoc(directoryName);
  }
}

/*______________________________________________________________________________

  MainWindow::readSettings
______________________________________________________________________________*/
void MainWindow::readSettings() {
  QSettings settings("QtProject", "Application Example");
  QPoint _pos = settings.value("pos", QPoint(200, 200)).toPoint();
  QSize _size = settings.value("size", QSize(400, 400)).toSize();
  resize(_size);
  move(_pos);
}

/*______________________________________________________________________________

  MainWindow::update_icons()

  Update the icons along the current Dipydoc and the reading mode.
________________________________________________________________________________*/
void MainWindow::update_icons(void) {
  // DEBUG1 DebugMsg() << "MainWindow::update_icons;";

  SCSplitter* splitter = this->current_splitter();

  /*............................................................................
    a special case : no Dipydoc->
  ............................................................................*/
  if (splitter == nullptr || \
      splitter->dipydoc->well_initialized() == false) {
    // DEBUG1 DebugMsg() << "MainWindow::update_icons : no splitter.";
    this->hidetoolbarsAct->setVisible(false);
    return;
  }

  /*............................................................................
    normal case : more than one Dipydoc has been loaded.
  ............................................................................*/
  this->hidetoolbarsAct->setVisible(true);

  if (this->visible_toolbars == false) {
    this->hidetoolbarsAct->setIcon(*(icons.hide_toolbars_off));
    this->hidetoolbarsAct->setText(tr("show toolbars"));

    for (int index = 0; index < this->sctabs->count(); index++) {
      splitter = qobject_cast<SCSplitter*>(this->sctabs->widget(index));
      splitter->update_icons();
    }
  } else {
    this->hidetoolbarsAct->setIcon(*(icons.hide_toolbars_on));
    this->hidetoolbarsAct->setText(tr("hide toolbars"));

    for (int index = 0; index < this->sctabs->count(); index++) {
      splitter = qobject_cast<SCSplitter*>(this->sctabs->widget(index));
      splitter->update_icons();
    }
  }
}

/*______________________________________________________________________________

  MainWindow::popup_mainmenuAct__buttonPressed
______________________________________________________________________________*/
void MainWindow::popup_mainmenuAct__buttonPressed(void) {
  this->mainpopupmenu->popup(QCursor::pos());
}
