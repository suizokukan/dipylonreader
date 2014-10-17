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
MainWindow::MainWindow(UI& _ui, QWidget *_parent) : QMainWindow(_parent), ui(_ui) {
  this->setObjectName("main_window");

#ifdef NO_STATUS_BAR
  this->setStatusBar(0);
#endif
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

  MainWindow::closeEvent

  Function called when the main window is closed.
______________________________________________________________________________*/
void MainWindow::closeEvent(QCloseEvent *arg_event) {
  DebugMsg() << "MainWindow::closeEvent";
  arg_event->accept();
}

/*______________________________________________________________________________

  MainWindow::closing

  from the doc of QCoreApplication::exec:

      We recommend that you connect clean-up code to the aboutToQuit() signal,
    instead of putting it in your application's main() function because on some
    platforms the QCoreApplication::exec() call may not return. For example,
    on Windows when the user logs off, the system terminates the process after
    Qt closes all top-level windows. Hence, there is no guarantee that the
    application will have time to exit its event loop and execute code at the
    end of the main() function after the QCoreApplication::exec() call.

    see e.g. http://stackoverflow.com/questions/8165487/how-to-do-cleaning-up-on-exit-in-qt
________________________________________________________________________________*/
void MainWindow::closing(void) {
  DebugMsg() << "MainWindow::closing";

  DebugMsg() << "(MainWindow::closing) calling UI::write_settings()";
  this->ui.write_settings();
}

/*______________________________________________________________________________

  MainWindow::createActions
______________________________________________________________________________*/
void MainWindow::createActions() {
  /*
    aboutAct
  */
  aboutAct = new QAction(tr("&About"), this);
  aboutAct->setStatusTip(tr("Show the application's About box"));
  QObject::connect(aboutAct, &QAction::triggered,
                   this,     &MainWindow::about);

  /*
    downloaddemoAct
  */
  downloaddemoAct = new QAction( *(this->ui.icon_downloaddemo),
                                 tr("Download demo Dipydocs"),
                                 this);
  downloaddemoAct->setStatusTip(tr("Download demo Dipydocs/statustip"));
  QObject::connect(downloaddemoAct, &QAction::triggered,
                   this,            &MainWindow::download_dipydocs_demo);

  /*
    exitAct
  */
  exitAct = new QAction(tr("E&xit"), this);
  exitAct->setShortcuts(QKeySequence::Quit);
  exitAct->setStatusTip(tr("Exit the application"));
  QObject::connect(exitAct, &QAction::triggered,
                   this,    &MainWindow::close);

  /*
    hidetoolbarsAct
  */
  this->hidetoolbarsAct = new QAction( *(this->ui.icon_hide_toolbars_on),
                                       tr("hide toolbars"),
                                       this);
  this->hidetoolbarsAct->setStatusTip(tr("hide the editors' toolbars"));
  QObject::connect(hidetoolbarsAct, &QAction::triggered,
                   this,            &MainWindow::hidetoolbarsAct__buttonPressed);

  /*
    internalmsgAct
  */
  this->internalmsgAct = new QAction( *(this->ui.icon_app),
                                       tr("internal messages"),
                                       this);
  this->internalmsgAct->setStatusTip(tr("internal messages"));
  QObject::connect(internalmsgAct, &QAction::triggered,
                   this,           &MainWindow::internalmsgAct__buttonPressed);

  /*
    openAct
  */
  openAct = new QAction( *(this->ui.icon_open),
                         tr("Open"),
                         this);
  openAct->setShortcuts(QKeySequence::Open);
  openAct->setStatusTip(tr("Open an existing DipyDoc"));
  QObject::connect(openAct, &QAction::triggered,
                   this,    &MainWindow::open);

  /*
    popup_mainmenuAct
  */
  #ifndef NO_MAIN_POPUPMENU
  popup_mainmenuAct = new QAction( *(this->ui.icon_popup_mainmenu),
                         tr("Popup_Mainmenu$$$"),
                         this);
  popup_mainmenuAct->setStatusTip(tr("Popup_Main$$$"));
  QObject::connect(this->popup_mainmenuAct, &QAction::triggered,
                   this,                    &MainWindow::popup_mainmenuAct__buttonPressed);
  #endif
}

/*______________________________________________________________________________

  MainWindow::createMenus

  o  main menu
  o  main popup menu
______________________________________________________________________________*/
void MainWindow::createMenus() {
  /*
    main menu :
  */
  this->fileMenu = menuBar()->addMenu(tr("&File"));
  this->openMenu = fileMenu->addMenu(tr("&Open"));

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
}

/*______________________________________________________________________________

  MainWindow::createStatusBar
______________________________________________________________________________*/
void MainWindow::createStatusBar() {
#ifndef NO_STATUS_BAR
  statusBar()->showMessage(tr("Ready"));
#endif
}

/*______________________________________________________________________________

  MainWindow::createMainToolBars
______________________________________________________________________________*/
void MainWindow::createMainToolBars() {
    this->mainwintoolbar = this->addToolBar(tr("main toolbar"));

    this->mainwintoolbar->setObjectName("main_window__main_toolbar");

    #ifndef NO_MAIN_POPUPMENU
    this->mainwintoolbar->addAction(this->popup_mainmenuAct);
    #endif
    this->mainwintoolbar->addAction(this->openAct);
    this->mainwintoolbar->addAction(this->hidetoolbarsAct);
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

  Fill the Open menu with the available dipydocs.
______________________________________________________________________________*/
void MainWindow::fill_open_menu(void) {
  /*
    let's clear the menu content :
  */
  this->openMenu->clear();

  /*
    special case : no dipydoc could be found.
  */
  if (this->ui.available_menu_names.size() == 0) {
    QAction* emptyAction = new QAction(*this->ui.icon_app,
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
    number_of_items++;

    if (number_of_items <= fixedparameters::maximum_number_of_items_in_submenu_open) {
      QAction* newAction = new QAction(*this->ui.icon_app,
                                       item.first,
                                       this);
      /*
         see MainWindow::load_a_dipydoc_from_a_qaction() for the format of the
         internal data.
      */
      newAction->setData(item.second);

      this->openMenu->addAction(newAction);
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
}

/*______________________________________________________________________________

  MainWindow::hidetoolbarsAct__buttonPressed
______________________________________________________________________________*/
void MainWindow::hidetoolbarsAct__buttonPressed(void) {
  this->ui.visible_toolbars = !this->ui.visible_toolbars;
  this->update_icons();
}

/*______________________________________________________________________________

  MainWindow::init()
______________________________________________________________________________*/
void MainWindow::init(void) {
  DebugMsg() << "MainWindow::init() : entry point";

  /*
       The actions created by the the call to createActions() method are
       required by the rest of this function :
  */
  this->createActions();

  this->tabs = new QTabWidget(this);
  this->tabs.setTabsClosable(true);
  this->setCentralWidget(this->tabs);

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
  DebugMsg() << "network_manager.networkAccessible (1 if ok) =" \
             << static_cast<int>(this->ui.network_manager->networkAccessible());

  DebugMsg() << "MainWindow::exit() : entry point";
}

/*______________________________________________________________________________

  MainWindow::internalmsgAct__buttonPressed
______________________________________________________________________________*/
void MainWindow::internalmsgAct__buttonPressed(void) {
  QMessageBox msgBox;

  msgBox.setText("Internal messages are used to debug the program. See details below.");

  msgBox.setDetailedText("internal state = " + QString().setNum(this->ui.current_dipydoc.internal_state()) +
                         this->ui.current_dipydoc.err_messages.join("\n\n") + \
                         "\n\n\n*** internal debug message ***\n\n\n" + \
                         DebugMsg::messages.join("\n"));
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

  MainWindow::loadDipyDoc() : load a DipyDoc from "directoryName".
______________________________________________________________________________*/
void MainWindow::loadDipyDoc(const QString &directoryName) {
  DebugMsg() << "MainWindow::loadDipyDoc" << directoryName;

  SourceCommentarySplitter* source_commentary_splitter = new SourceCommentarySplitter(directoryName,
                                                                                      ui,
                                                                                      this->tabs);

  if (source_commentary_splitter->well_initialized() == false ) {
    DebugMsg() << "MainWindow::loadDipyDoc : error";
    delete source_commentary_splitter;
  }
  else {
    DebugMsg() << "MainWindow::loadDipyDoc : ok";
    this->tabs->addWidget(source_commentary_splitter);
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
  DebugMsg() << "MainWindow::update_icons; ui.reading_mode=" << this->ui.reading_mode;

  /*............................................................................
    a special case : no Dipydoc.
  ............................................................................*/
  if (this->ui.at_least_one_dipydoc_has_been_loaded() == false) {
    this->ui.mainWin->hidetoolbarsAct->setIcon(*(this->ui.icon_hide_toolbars_off));
    this->ui.mainWin->source_toolbar->hide();
    this->ui.mainWin->commentary_toolbar->hide();
    return;
  }

  /*............................................................................
    normal case : more than one Dipydoc has been loaded.
  ............................................................................*/
  if (this->ui.visible_toolbars == false) {
    /*
      invisible toolbars :
    */
    this->ui.mainWin->source_toolbar->hide();
    this->ui.mainWin->commentary_toolbar->hide();

    // hidetoolbars button is "on" :
    this->ui.mainWin->hidetoolbarsAct->setIcon(*(this->ui.icon_hide_toolbars_off));
  } else {
    /*
       visible toolbars :
    */

    // toolbars are visible :
    if (this->ui.visible_toolbars == true && this->ui.mainWin->source_toolbar->isVisible() == false) {
      this->ui.mainWin->source_toolbar->show();
      this->ui.mainWin->commentary_toolbar->show();
    }

    // hidetoolbars button is "off" :
    this->ui.mainWin->hidetoolbarsAct->setIcon(*(this->ui.icon_hide_toolbars_on));
  }
}

/*______________________________________________________________________________

  MainWindow::popup_mainmenuAct__buttonPressed
______________________________________________________________________________*/
void MainWindow::popup_mainmenuAct__buttonPressed(void) {
  this->mainpopupmenu->popup(QCursor::pos());
}
