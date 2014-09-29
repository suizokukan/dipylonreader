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
MainWindow::MainWindow(UI& _ui) : ui(_ui) {
#ifdef NO_STATUS_BAR
  this->setStatusBar(0);
#endif
}

/*______________________________________________________________________________

  MainWindow::about
______________________________________________________________________________*/
void MainWindow::about() {
    QMessageBox msgBox;
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(QString( tr("<b>%1</b> %2, "
                               "a software by %3.<br/><br/>"
                               "  This program is covered by the <b>%4</b> "
                               "(<a href='%5'>%5</a>) license : "
                               "checkout the code of the project at the following "
                               "<a href='%6'>address</a>.").arg(fixedparameters::application_name_for_the_user,
                                                                fixedparameters::application_version,
                                                                fixedparameters::CODESOURCE_AUTHOR,
                                                                fixedparameters::CODESOURCE_LICENSE,
                                                                fixedparameters::CODESOURCE_LICENSE_ADDRESS,
                                                                fixedparameters::CODESOURCE_ADDRESS)));

    #ifdef DISPLAY_INTERNAL_MESSAGES_IN_HELP_MENUITEM
    msgBox.setDetailedText( "internal state = " + QString().setNum(this->ui.current_dipydoc.internal_state()) +
                            this->ui.current_dipydoc.err_messages.join("\n\n") + \
                            "\n\n\n*** internal debug message ***\n\n\n" + \
                            DebugMsg::messages.join("\n") );
    #endif

    msgBox.exec();
}

/*______________________________________________________________________________

  MainWindow::audiocontrols_play()

  Function connected to this->audiocontrols_playAct::triggered()

  known cases :

  o [1] lmode
        o [1.1] LMODE + PLAYING -> LMODE + ON PAUSE
        o [1.2] LMODE + ON PAUSE -> LMODE + PLAYING
        o [1.3] LMODE + STOP -> LMODE + PLAYING
        o [1.4] LMODE + UNDEFINED : nothing to do.
  o [2] other modes
________________________________________________________________________________*/
void MainWindow::audiocontrols_play(void) {
  switch (this->ui.reading_mode ) {

    /*
      [1] lmode
    */
    case UI::READINGMODE_LMODE: {

      switch (this->ui.reading_mode_details ) {

        // [1.1] LMODE + PLAYING -> LMODE + ON PAUSE
        case UI::READINGMODEDETAIL_LMODE_PLAYING: {
          this->ui.reading_mode_details = UI::READINGMODEDETAIL_LMODE_ONPAUSE;
          this->audiocontrols_playAct->setIcon( *(this->ui.icon_audio_pause) );
          this->audio_player->pause();
          break;
        }

        // [1.2] LMODE + ON PAUSE -> LMODE + PLAYING
        case UI::READINGMODEDETAIL_LMODE_ONPAUSE: {
          this->ui.reading_mode_details = UI::READINGMODEDETAIL_LMODE_PLAYING;
          this->audiocontrols_playAct->setIcon( *(this->ui.icon_audio_play) );
          this->audio_player->play();
          break;
        }

        // [1.3] LMODE + STOP -> LMODE + PLAYING
        case UI::READINGMODEDETAIL_LMODE_STOP: {
          this->ui.reading_mode_details = UI::READINGMODEDETAIL_LMODE_PLAYING;
          this->audiocontrols_playAct->setIcon( *(this->ui.icon_audio_play) );
          this->audio_player->play();
          break;
        }

        // [1.4] LMODE + UNDEFINED
        default : {
          break;
        }
      }

      break;
    }

    /*
      [2] other modes
    */
    default: {
        break;
    }

  }
}

/*______________________________________________________________________________

  MainWindow::audiocontrols_stop()

  Function connected to this->audiocontrols_stopAct::triggered()

  o stop the sound
  o set the mode's detail to READINGMODEDETAIL_LMODE_STOP
  o set the source editor's text format to "default".

________________________________________________________________________________*/
void MainWindow::audiocontrols_stop(void) {
  DebugMsg() << "MainWindow::audiocontrols_stop";

  // LMODE + ON PAUSE ? we set the icon from "pause" to "play".
  if( this->ui.reading_mode == UI::READINGMODE_LMODE &&
      this->ui.reading_mode_details == UI::READINGMODEDETAIL_LMODE_ONPAUSE ) {

    this->audiocontrols_playAct->setIcon( *(this->ui.icon_audio_play) );
  }

  this->ui.reading_mode_details = UI::READINGMODEDETAIL_LMODE_STOP;

  audio_player->stop();

  this->source_editor->reset_all_text_format_to_default();
}

/*______________________________________________________________________________

  MainWindow::audio_position_changed

________________________________________________________________________________*/
void MainWindow::audio_position_changed(qint64 arg_pos) {

  /* LMODE + PLAYING :
   */
  if( this->ui.reading_mode == UI::READINGMODE_LMODE &&
      this->ui.reading_mode_details == UI::READINGMODEDETAIL_LMODE_PLAYING ) {

      // where are the characters linked to "arg_pos" ?
      PosInTextRanges text_ranges = this->ui.current_dipydoc.audio2text_contains( arg_pos );
      std::size_t text_ranges_hash = text_ranges.get_hash();

      if( text_ranges_hash != this->source_editor->modified_chars_hash ) {

        // the function modifies the appearence of such characters :
        this->source_editor->modify_the_text_format(text_ranges);

        // hash update :
        this->source_editor->modified_chars_hash = text_ranges_hash;

        this->ui.mainWin->commentary_editor->update_content__translation_expected(text_ranges);
      }

      return;
  }

  /*
    this->ui.reading_mode == UI::READINGMODE_LMODE &&
    this->ui.reading_mode_details == UI::READINGMODEDETAIL_LMODE_ONPAUSE

    -> nothing to do.
  */
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

    We recommend that you connect clean-up code to the aboutToQuit() signal, instead of putting it in your application's main() function because on some platforms the QCoreApplication::exec() call may not return. For example, on Windows when the user logs off, the system terminates the process after Qt closes all top-level windows. Hence, there is no guarantee that the application will have time to exit its event loop and execute code at the end of the main() function after the QCoreApplication::exec() call.

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
    audiocontrols_playAct
  */
  this->audiocontrols_playAct = new QAction( *(this->ui.icon_audio_play),
                                             tr("play"),
                                             this);
  this->audiocontrols_playAct->setStatusTip(tr("play..."));
  QObject::connect(this->audiocontrols_playAct, &QAction::triggered,
                   this,                        &MainWindow::audiocontrols_play);

  /*
    audiocontrols_stopAct
  */
  this->audiocontrols_stopAct = new QAction( *(this->ui.icon_audio_stop),
                                             tr("stop"),
                                             this);
  this->audiocontrols_stopAct->setStatusTip(tr("stop..."));
  QObject::connect(this->audiocontrols_stopAct, &QAction::triggered,
                   this,                        &MainWindow::audiocontrols_stop);

  /*
    commentary_textminusAct
  */
  this->commentary_textminusAct = new QAction( *(this->ui.icon_textminus),
                                               tr("--- TEXT $$$"),
                                               this);
  this->commentary_textminusAct->setStatusTip(tr("TEXT $$$ -"));

  /*
    commentary_textplusAct
  */
  this->commentary_textplusAct = new QAction( *(this->ui.icon_textplus),
                                               tr("--- TEXT $$$"),
                                               this);
  this->commentary_textplusAct->setStatusTip(tr("TEXT $$$ -"));

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
    readingmode_aAct
  */
  this->readingmode_aAct = new QAction( *(this->ui.icon_readingmode_amode_on),
                                        tr("change the mode$$$rl"),
                                        this);
  this->readingmode_aAct->setStatusTip(tr("change the mode to 'analyse'"));
  QObject::connect(this->readingmode_aAct, &QAction::triggered,
                   this,                   &MainWindow::readingmode_aAct__buttonpressed);

  /*
    readingmode_lAct
  */
  this->readingmode_lAct = new QAction( *(this->ui.icon_readingmode_lmode_on),
                                        tr("change the mode$$$rl"),
                                        this);
  this->readingmode_lAct->setStatusTip(tr("change the mode to 'read & listen'"));
  QObject::connect(this->readingmode_lAct, &QAction::triggered,
                   this,                   &MainWindow::readingmode_lAct__buttonpressed);

  /*
    readingmode_rAct
  */
  this->readingmode_rAct = new QAction( *(this->ui.icon_readingmode_rmode_on),
                                        tr("change the mode$$$r"),
                                        this);
  this->readingmode_rAct->setStatusTip(tr("change the mode to 'read'"));
  QObject::connect(this->readingmode_rAct, &QAction::triggered,
                   this,                   &MainWindow::readingmode_rAct__buttonpressed);

  /*
    saveMainFileOfADipyDocAsAct
  */
  #ifdef READANDWRITE
  saveMainFileOfADipyDocAsAct = new QAction(tr("Save DipyDoc's main file as..."), this);
  saveMainFileOfADipyDocAsAct->setStatusTip(tr("Save DipyDoc's main file as"));
  QObject::connect(saveMainFileOfADipyDocAsAct, &QAction::triggered,
                   this,                        &MainWindow::saveMainFileOfADipyDocAs);
  #endif

  /*
    source_textminusAct
  */
  this->source_textminusAct = new QAction( *(this->ui.icon_textminus),
                                           tr("--- TEXT $$$"),
                                           this);
  this->source_textminusAct->setStatusTip(tr("TEXT $$$ -"));

  /*
    source_textplusAct
  */
  this->source_textplusAct = new QAction( *(this->ui.icon_textplus),
                                          tr("--- TEXT $$$"),
                                          this);
  this->source_textplusAct->setStatusTip(tr("TEXT $$$ -"));
}

/*______________________________________________________________________________

  MainWindow::createMenus
______________________________________________________________________________*/
void MainWindow::createMenus() {
  this->fileMenu = menuBar()->addMenu(tr("&File"));
  this->openMenu = fileMenu->addMenu(tr("&Open"));

  this->fill_open_menu();

  this->fileMenu->addSeparator();

  this->fileMenu->addAction(downloaddemoAct);

  #ifdef READANDWRITE
  fileMenu->addAction(saveMainFileOfADipyDocAsAct);
  #endif
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);

  menuBar()->addSeparator();

  helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAct);
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
    this->mainwintoolbar = addToolBar(tr("unique toolbar"));
    this->mainwintoolbar->addAction(this->openAct);
    this->mainwintoolbar->addAction(this->hidetoolbarsAct);
}

/*______________________________________________________________________________

  MainWindow::download_dipydocs_demo

  This function removes old demo files, then download and install the new ones.
______________________________________________________________________________*/
void MainWindow::download_dipydocs_demo(void) {
  // using the DownloadDemoDipydocs class to download the files :
  DownloadDemoDipydocs d(this->ui);

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
  if( this->ui.available_menu_names.size() == 0) {
    QAction* emptyAction = new QAction( *this->ui.icon_app,
                                        "(No Dipydoc could be found)",
                                        this );
    this->openMenu->addAction(emptyAction);

    openMenu->addSeparator();
    this->openMenu->addAction(openAct);
    return;
  }

  /*
    normal case : at least one dipydoc was found.
  */
  int number_of_items = 0;
  for( auto &item : this->ui.available_menu_names ) {
    number_of_items++;

    if(number_of_items <= fixedparameters::maximum_number_of_items_in_submenu_open) {
      QAction* newAction = new QAction( *this->ui.icon_app,
                                        item.first,
                                        this );
      /*
         see MainWindow::load_a_dipydoc_from_a_qaction() for the format of the
         internal data.
      */
      newAction->setData(item.second);

      this->openMenu->addAction(newAction);
      QObject::connect(newAction, &QAction::triggered,
                       this,      &MainWindow::load_a_dipydoc_from_a_qaction);
    }
    else {
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

  this->main_splitter = new QSplitter(this);
  this->main_splitter->setOrientation(Qt::Vertical);
  this->setCentralWidget(main_splitter);

  this->source_zone = new SourceZone(this->ui);
  this->commentary_zone = new CommentaryZone(this->ui);
  this->main_splitter->addWidget(this->source_zone);
  this->main_splitter->addWidget(this->commentary_zone);

  this->main_splitter->setSizes( fixedparameters::default__editors_size_in_main_splitter );

  this->createMenus();
  this->createMainToolBars();
  #ifndef NO_STATUS_BAR
  this->createStatusBar();
  #endif

  this->readSettings();

  // let's update the icons' appearence :
  this->update_icons();

  /*
    audio_player initialization

    http://qt-project.org/doc/qt-5/qmediaplayer.html#seekable-prop
  */
  this->audio_player = new QMediaPlayer(this);

  /*
     signal : the position in the audio record has been changed.
  */
  QObject::connect( this->audio_player, &QMediaPlayer::positionChanged,
                    this,               &MainWindow::audio_position_changed );

  this->audio_player->setNotifyInterval(fixedparameters::default__audio_notify_interval);
  this->audio_player->setVolume(fixedparameters::default__audio_player_volume);

  this->setCurrentDipyDoc("");
  this->setUnifiedTitleAndToolBarOnMac(true);

  /*
    initialization of the network manager :
  */
  this->ui.network_manager = new QNetworkAccessManager();
  DebugMsg() << "network_manager.networkAccessible (1 if ok) =" \
             << static_cast<int>(this->ui.network_manager->networkAccessible());

  DebugMsg() << "MainWindow::exit() : entry point";
}

/*______________________________________________________________________________

  MainWindow::load_a_dipydoc_from_a_qaction

  Load a Dipydoc from a QAction with the path stored in the internal data.
______________________________________________________________________________*/
void MainWindow::load_a_dipydoc_from_a_qaction(void) {
  QAction* action = qobject_cast<QAction*>(this->sender());
  this->loadDipyDoc( action->data().toString() );
}

/*______________________________________________________________________________

  MainWindow::loadDipyDoc() : load a DipyDoc from "directoryName".

  Display an informative message if something's wrong happened.

______________________________________________________________________________*/
void MainWindow::loadDipyDoc(const QString &directoryName) {
  DebugMsg() << "MainWindow::loadDipyDoc" << directoryName;

  #ifndef QT_NO_CURSOR
  QApplication::setOverrideCursor(Qt::WaitCursor);
  #endif

  this->ui.current_dipydoc = DipyDoc(directoryName);

  if( this->ui.current_dipydoc.well_initialized() == false ) {

    // an error occurs :
    QMessageBox msgBox;
    msgBox.setText( tr("Unable to load any valid Dipydoc's document from <b>") + directoryName + "</b> ." +\
                    "<br/><br/>" + this->ui.current_dipydoc.diagnosis() + \
                    "<br/><br/>" + tr("See more details below.") );

    msgBox.setDetailedText( "internal state = " + \
                            QString().setNum(this->ui.current_dipydoc.internal_state()) + \
                            "\n\n" + \
                            this->ui.current_dipydoc.err_messages.join("\n\n") + \
                            "\n\n\n*** internal debug message ***\n\n\n" + \
                            DebugMsg::messages.join("\n") );
    msgBox.exec();
  }
  else {
    // no error, let's load the DipyDoc :
    this->load_text(this->ui.current_dipydoc.source_text);

    if( this->ui.current_dipydoc.audiorecord.found == true ) {
      DebugMsg() << "loading audiofile" << this->ui.current_dipydoc.audiorecord.filename;
      this->audio_player->setMedia(QUrl::fromLocalFile(this->ui.current_dipydoc.audiorecord.filename));
    }
  }

  #ifndef QT_NO_CURSOR
  QApplication::restoreOverrideCursor();
  #endif

  if( this->ui.current_dipydoc.well_initialized() == true ) {

    // update source editor aspect :
    this->source_editor->update_aspect_from_dipydoc_aspect_informations();

    // update commentary editor aspect :
    this->commentary_editor->update_aspect_from_dipydoc_aspect_informations();

    // update the rest of the UI :
    this->update_icons();
    setCurrentDipyDoc(directoryName);
    #ifndef NO_STATUS_BAR
    statusBar()->showMessage(tr("DipyDoc loaded"), 2000);
    #endif
  }

  /*
    Let's initialize this->ui.path_to_dipydocs :

    It can't be set to "directoryName" since we don't want the user
    looks into the current directory, full of the Dipydoc files
    (main.xml, ...) : we need to place the user in the parent directory.
  */
  QDir parent_directory = QDir(directoryName);
  if( parent_directory.cdUp() == true ) {
    /*
       Ok, we can go upper and set path_to_dipydocs to the parent
       directory
    */
    this->ui.path_to_dipydocs = parent_directory.absolutePath();
  }
  else {
    /*
      No, for some reasons the upper directory isn't readable : we
      keep the current directory.
    */
    this->ui.path_to_dipydocs = directoryName;
  }

  // default reading mode :
  this->ui.reading_mode         = UI::READINGMODE::READINGMODE_RMODE;
  this->ui.reading_mode_details = UI::READINGMODEDETAILS::READINGMODEDETAIL_RMODE;

  // updating the UI :
  this->ui.mainWin->source_toolbar->show();
  this->ui.mainWin->commentary_toolbar->show();
  this->update_icons();
}

/*______________________________________________________________________________

  MainWindow::load_text

________________________________________________________________________________*/
void MainWindow::load_text(const DipyDocSourceText& source_text)  {
  this->source_editor->load_text(source_text);
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

  MainWindow::readingmode_aAct__buttonpressed()

  connected to readingmode_aAct::triggered()
______________________________________________________________________________*/
void MainWindow::readingmode_aAct__buttonpressed(void) {
  this->ui.reading_mode = UI::READINGMODE_AMODE;
  this->ui.reading_mode_details = UI::READINGMODEDETAIL_AMODE;
  DebugMsg() << "switched to AMODE mode";
  this->update_icons();
}

/*______________________________________________________________________________

  MainWindow::readingmode_rAct__buttonpressed()

  connected to readingmode_rAct::triggered()
______________________________________________________________________________*/
void MainWindow::readingmode_rAct__buttonpressed(void) {
  this->ui.reading_mode = UI::READINGMODE_RMODE;
  this->ui.reading_mode_details = UI::READINGMODEDETAIL_RMODE;
  DebugMsg() << "switched to RMODE mode";
  this->update_icons();
}

/*______________________________________________________________________________

  MainWindow::readingmode_lAct__buttonpressed()

  connected to readingmode_lAct::triggered()
______________________________________________________________________________*/
void MainWindow::readingmode_lAct__buttonpressed(void) {
  this->ui.reading_mode = UI::READINGMODE_LMODE;
  this->ui.reading_mode_details = UI::READINGMODEDETAIL_LMODE_STOP;
  DebugMsg() << "switched to LMODE mode";
  this->update_icons();
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

  MainWindow::saveMainFileOfADipyDocAs
______________________________________________________________________________*/
bool MainWindow::saveMainFileOfADipyDocAs() {
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.exec();
    QStringList files = dialog.selectedFiles();

    if (files.isEmpty()) {
      return false;
    }

    QString fileName = files.at(0);

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << this->ui.current_dipydoc.get_xml_repr();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentDipyDoc(fileName);
    #ifndef NO_STATUS_BAR
    statusBar()->showMessage(tr("File saved"), 2000);
    #endif
    return true;
}

/*______________________________________________________________________________

  MainWindow::setCurrentDipyDoc

________________________________________________________________________________*/
void MainWindow::setCurrentDipyDoc(const QString &directoryName) {
    curFile = directoryName;
    source_editor->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

/*______________________________________________________________________________

  MainWindow::update_icons()

  Update the icons along the current Dipydoc and the reading mode.
________________________________________________________________________________*/
void MainWindow::update_icons(void) {
  DebugMsg() << "MainWindow::update_icons" << this->ui.reading_mode;

  /*............................................................................
    a special case : no Dipydoc.
  ............................................................................*/
  if( this->ui.at_least_one_dipydoc_has_been_loaded() == false ) {
    this->ui.mainWin->hidetoolbarsAct->setIcon( *(this->ui.icon_hide_toolbars_off) );
    this->ui.mainWin->source_toolbar->hide();
    this->ui.mainWin->commentary_toolbar->hide();
    return;
  }

  /*............................................................................
    normal case : more than one Dipydoc has been loaded.
  ............................................................................*/
  if(this->ui.visible_toolbars == false) {
    /*
      invisible toolbars :
    */
    this->ui.mainWin->source_toolbar->hide();
    this->ui.mainWin->commentary_toolbar->hide();

    this->ui.mainWin->hidetoolbarsAct->setIcon( *(this->ui.icon_hide_toolbars_off) );
  }
  else {
    /*
       visible toolbars :
    */

    // toolbars are visible :
    if(this->ui.visible_toolbars == true and this->ui.mainWin->source_toolbar->isVisible() == false) {
      this->ui.mainWin->source_toolbar->show();
      this->ui.mainWin->commentary_toolbar->show();
    }

    // hidetoolbars button is visible :
    this->ui.mainWin->hidetoolbarsAct->setIcon( *(this->ui.icon_hide_toolbars_on) );

    /*
      source zone.toolbar.readingmode_icons :
    */
    switch (this->ui.reading_mode ) {

      case UI::READINGMODE_AMODE: {
        this->readingmode_aAct->setIcon( *(this->ui.icon_readingmode_amode_on) );
        this->readingmode_rAct->setIcon( *(this->ui.icon_readingmode_rmode_off) );
        this->readingmode_lAct->setIcon( *(this->ui.icon_readingmode_lmode_off) );
        this->audiocontrols_playAct->setEnabled(false);
        this->audiocontrols_stopAct->setEnabled(false);
        break;
      }

      case UI::READINGMODE_LMODE: {
        this->readingmode_aAct->setIcon( *(this->ui.icon_readingmode_amode_off) );
        this->readingmode_rAct->setIcon( *(this->ui.icon_readingmode_rmode_off) );
        this->readingmode_lAct->setIcon( *(this->ui.icon_readingmode_lmode_on) );
        this->audiocontrols_playAct->setEnabled(true);
        this->audiocontrols_stopAct->setEnabled(true);
        break;
      }

      case UI::READINGMODE_RMODE: {
        this->readingmode_aAct->setIcon( *(this->ui.icon_readingmode_amode_off) );
        this->readingmode_rAct->setIcon( *(this->ui.icon_readingmode_rmode_on) );
        this->readingmode_lAct->setIcon( *(this->ui.icon_readingmode_lmode_off) );
        this->audiocontrols_playAct->setEnabled(false);
        this->audiocontrols_stopAct->setEnabled(false);
        break;
      }

      default : {
        break;
      }
    }

    /*
      source zone.toolbar.audiocontrol_icons :
    */
    if (this->ui.reading_mode != UI::READINGMODE_LMODE ||
        this->ui.current_dipydoc.well_initialized() == false ||
        (this->ui.current_dipydoc.well_initialized() == true and
         this->ui.current_dipydoc.audiorecord.found == false)) {
      /*
         No lmode mode or no current DipyDoc or no audio in the current DipyDoc :
      */
      this->audiocontrols_playAct->setEnabled(false);
      // we refresh the icon to display it using only shades of gray :
      this->audiocontrols_playAct->setIcon( *(this->ui.icon_audio_play) );

      this->audiocontrols_stopAct->setEnabled(false);
      // we refresh the icon to display it using only shades of gray :
      this->audiocontrols_stopAct->setIcon( *(this->ui.icon_audio_stop) );
    }
    else {
      /*
        the current DipyDoc is ok and contains an audio record :
      */
      this->audiocontrols_playAct->setEnabled(true);
      // we refresh the icon to display it in colors :
      this->audiocontrols_playAct->setIcon( *(this->ui.icon_audio_play) );

      this->audiocontrols_stopAct->setEnabled(true);
      // we refresh the icon to display it in colors :
      this->audiocontrols_stopAct->setIcon( *(this->ui.icon_audio_stop) );
    }
  }
}

/*______________________________________________________________________________

  MainWindow::writeSettings
______________________________________________________________________________*/
void MainWindow::writeSettings() {
    QSettings settings("QtProject", "Application Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}
