/*******************************************************************************

    Dipylon Copyright (C) 2008 Xavier Faure
    Contact: faure dot epistulam dot mihi dot scripsisti at orange dot fr

    This file is part of Dipylon.
    Dipylon is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Dipylon is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Dipylon.  If not, see <http://www.gnu.org/licenses/>.

    ____________________________________________________________________________

    ❏Dipylon❏ : qt/mainwindow.cpp

    see mainwindow.h for the dcumentation

*******************************************************************************/

#include "qt/mainwindow.h"
#include "debugmsg/debugmsg.h"

/*______________________________________________________________________________

  MainWindow::constructor

______________________________________________________________________________*/
MainWindow::MainWindow(DipylonUI& dipylonui) : current_dipylonui(dipylonui) {
    this->main_splitter = new QSplitter(this);
    this->main_splitter->setOrientation( Qt::Vertical );
    this->setCentralWidget(main_splitter);

    this->source_editor = new SourceEditor(this->current_dipylonui);
    this->commentary_editor = new CommentaryEditor(this->current_dipylonui);
    this->main_splitter->addWidget(this->source_editor);
    this->main_splitter->addWidget(this->commentary_editor);

    this->main_splitter->setSizes( fixedparameters::default__editors_size_in_main_splitter );

    this->createActions();
    this->createMenus();
    this->createToolBars();
    this->createStatusBar();

    this->readSettings();

    // let's update the icons' appearence :
    this->update_icons();

    // signal : the document has been modified.
    connect( this->source_editor->document(), &QTextDocument::contentsChanged,
             this, &MainWindow::documentWasModified);

    /*
      audio_player initialization

      http://qt-project.org/doc/qt-5/qmediaplayer.html#seekable-prop
    */
    this->audio_player = new QMediaPlayer(this);

    /*
       signal : the position in the audio record has been changed.
    */
    connect( this->audio_player, &QMediaPlayer::positionChanged,
             this, &MainWindow::audio_position_changed );

    this->audio_player->setNotifyInterval(fixedparameters::default__audio_notify_interval);
    this->audio_player->setVolume(fixedparameters::default__audio_player_volume);

    setCurrentDipyDoc("");
    setUnifiedTitleAndToolBarOnMac(true);
}

/*______________________________________________________________________________

  MainWindow::about
______________________________________________________________________________*/
void MainWindow::about() {
   QMessageBox::about(this, tr("About Application"),
            tr("The <b>Application</b> example demonstrates how to "
               "write modern GUI applications using Qt, with a menu bar, "
               "toolbars, and a status bar."));
}

/*______________________________________________________________________________

  MainWindow::audiocontrols_play()

  Function connected to this->audiocontrols_playAct::triggered()

  known cases :

  o [1] karaoke
        o [1.1] KARAOKE + PLAYING -> KARAOKE + ON PAUSE
        o [1.2] KARAOKE + ON PAUSE -> KARAOKE + PLAYING
        o [1.3] KARAOKE + STOP -> KARAOKE + PLAYING
        o [1.4] KARAOKE + UNDEFINED : nothing to do.
  o [2] grammar
  o [3] undefined, default
________________________________________________________________________________*/
void MainWindow::audiocontrols_play(void) {
  switch (this->current_dipylonui.reading_mode ) {

    /*
      [1] karaoke
    */
    case DipylonUI::READINGMODE_KARAOKE: {

      switch (this->current_dipylonui.reading_mode_details ) {

        // [1.1] KARAOKE + PLAYING -> KARAOKE + ON PAUSE
        case DipylonUI::READINGMODEDETAIL_KARAOKE_PLAYING: {
          this->current_dipylonui.reading_mode_details = DipylonUI::READINGMODEDETAIL_KARAOKE_ONPAUSE;
          this->audiocontrols_playAct->setIcon( *(this->current_dipylonui.icon_audio_pause) );
          this->audio_player->pause();
          break;
        }

        // [1.2] KARAOKE + ON PAUSE -> KARAOKE + PLAYING
        case DipylonUI::READINGMODEDETAIL_KARAOKE_ONPAUSE: {
          this->current_dipylonui.reading_mode_details = DipylonUI::READINGMODEDETAIL_KARAOKE_PLAYING;
          this->audiocontrols_playAct->setIcon( *(this->current_dipylonui.icon_audio_play) );
          this->audio_player->play();
          break;
        }

        // [1.3] KARAOKE + STOP -> KARAOKE + PLAYING
        case DipylonUI::READINGMODEDETAIL_KARAOKE_STOP: {
          this->current_dipylonui.reading_mode_details = DipylonUI::READINGMODEDETAIL_KARAOKE_PLAYING;
          this->audiocontrols_playAct->setIcon( *(this->current_dipylonui.icon_audio_play) );
          this->audio_player->play();
          break;
        }

        // [1.4] default
        default : {
          break;
        }
      }

      break;
    }

    /*
      grammar
    */
    case DipylonUI::READINGMODE_GRAMMAR: {
      break;
    }

    /*
      undefined, default
    */
    case DipylonUI::READINGMODE_UNDEFINED: {
      break;
    }
    default: {
        break;
    }

  }
}

/*______________________________________________________________________________

  MainWindow::audiocontrols_stop()

  Function connected to this->audiocontrols_stopAct::triggered()

  o stop the sound
  o set the mode's detail to READINGMODEDETAIL_KARAOKE_STOP
  o set the source editor's text format to "default".

________________________________________________________________________________*/
void MainWindow::audiocontrols_stop(void) {
  DebugMsg() << "MainWindow::audiocontrols_stop";

  // KARAOKE + ON PAUSE ? we set the icon from "pause" to "play".
  if( this->current_dipylonui.reading_mode == DipylonUI::READINGMODE_KARAOKE &&
      this->current_dipylonui.reading_mode_details == DipylonUI::READINGMODEDETAIL_KARAOKE_ONPAUSE ) {

    this->audiocontrols_playAct->setIcon( *(this->current_dipylonui.icon_audio_play) );
  }

  this->current_dipylonui.reading_mode_details = DipylonUI::READINGMODEDETAIL_KARAOKE_STOP;

  audio_player->stop();

  this->source_editor->reset_all_text_format_to_default();
}

/*______________________________________________________________________________

  MainWindow::audio_position_changed

________________________________________________________________________________*/
void MainWindow::audio_position_changed(qint64 arg_pos) {

  /* KARAOKE + PLAYING :
   */
  if( this->current_dipylonui.reading_mode == DipylonUI::READINGMODE_KARAOKE &&
      this->current_dipylonui.reading_mode_details == DipylonUI::READINGMODEDETAIL_KARAOKE_PLAYING ) {

      // where are the characters linked to "arg_pos" ?
      PosInTextRanges text_ranges = this->current_dipylonui.current_dipydoc.audio2text_contains( arg_pos );
      std::size_t text_ranges_hash = text_ranges.get_hash();

      if( text_ranges_hash != this->source_editor->modified_chars_hash ) {

        // the function modifies the appearence of such characters :
        this->source_editor->modify_the_text_format(text_ranges);

        // hash update :
        this->source_editor->modified_chars_hash = text_ranges_hash;

        this->current_dipylonui.mainWin->commentary_editor->update_content__translation_expected(text_ranges);
      }

      return;
  }

  /*
    this->current_dipylonui.reading_mode == DipylonUI::READINGMODE_KARAOKE &&
    this->current_dipylonui.reading_mode_details == DipylonUI::READINGMODEDETAIL_KARAOKE_ONPAUSE

    -> nothing to do.
  */
}

/*______________________________________________________________________________

  MainWindow::closeEvent

  Function called when the main window is closed.
______________________________________________________________________________*/
void MainWindow::closeEvent(QCloseEvent *arg_event) {
  DebugMsg() << "MainWindow::closeEvent";

  if (maybeSave()) {
      writeSettings();
      arg_event->accept();
  } else {
      arg_event->ignore();
  }
}

/*______________________________________________________________________________

  MainWindow::closing

  from the doc of QCoreApplication::exec:

    We recommend that you connect clean-up code to the aboutToQuit() signal, instead of putting it in your application's main() function because on some platforms the QCoreApplication::exec() call may not return. For example, on Windows when the user logs off, the system terminates the process after Qt closes all top-level windows. Hence, there is no guarantee that the application will have time to exit its event loop and execute code at the end of the main() function after the QCoreApplication::exec() call.

    see e.g. http://stackoverflow.com/questions/8165487/how-to-do-cleaning-up-on-exit-in-qt
________________________________________________________________________________*/
void MainWindow::closing(void) {
  DebugMsg() << "MainWindow::closing";

  DebugMsg() << "(MainWindow::closing) calling DipylonUI::write_settings()";
  this->current_dipylonui.write_settings();
}

/*______________________________________________________________________________

  MainWindow::createActions
______________________________________________________________________________*/
void MainWindow::createActions() {
    newAct = new QAction( *(this->current_dipylonui.icon_new),
                          tr("&New"),
                          this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered,
            this, &MainWindow::newFile);

    openAct = new QAction( *(this->current_dipylonui.icon_open),
                           tr("&Open"),
                           this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing DipyDoc"));
    connect(openAct, &QAction::triggered,
            this, &MainWindow::open);

    saveAct = new QAction( *(this->current_dipylonui.icon_save),
                           tr("&Save"),
                           this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered,
            this, &MainWindow::save);

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, &QAction::triggered,
            this, &MainWindow::saveAs);

    #ifdef READANDWRITE
    saveMainFileOfADipyDocAsAct = new QAction(tr("Save DipyDoc's main file as..."), this);
    saveMainFileOfADipyDocAsAct->setStatusTip(tr("Save DipyDoc's main file as"));
    connect(saveMainFileOfADipyDocAsAct, &QAction::triggered,
            this, &MainWindow::saveMainFileOfADipyDocAs);
    #endif

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered,
            this, &MainWindow::close);

    cutAct = new QAction( *(this->current_dipylonui.icon_cut),
                          tr("Cu&t"),
                          this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, &QAction::triggered,
            source_editor, &QTextEdit::cut);

    copyAct = new QAction( *(this->current_dipylonui.icon_copy),
                           tr("&Copy"),
                           this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, &QAction::triggered,
            source_editor, &QTextEdit::copy);

    pasteAct = new QAction( *(this->current_dipylonui.icon_paste),
                            tr("&Paste"),
                            this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, &QAction::triggered,
            source_editor, &QTextEdit::paste);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered,
            this, &MainWindow::about);

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    #ifdef CROSSCOMPILE_TO_WIN_USING_MXE
    // old signals style with SIGNAL and SLOT :
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    #else
    // new signals style :
    connect(aboutQtAct, &QAction::triggered,
            qApp, &QApplication::aboutQt);
    #endif

    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
    connect(source_editor, &QTextEdit::copyAvailable,
            cutAct, &QAction::setEnabled);
    connect(source_editor, &QTextEdit::copyAvailable,
            copyAct, &QAction::setEnabled);

    this->readingmodeAct = new QAction( *(this->current_dipylonui.icon_readingmode_karaoke),
                                 tr("change the mode"),
                                 this);
    this->readingmodeAct->setStatusTip(tr("change the mode"));
    connect(this->readingmodeAct, &QAction::triggered,
            this, &MainWindow::readingmodeAct_buttonpressed);

    this->audiocontrols_playAct = new QAction( *(this->current_dipylonui.icon_audio_play),
                                               tr("play"),
                                               this);
    this->audiocontrols_playAct->setStatusTip(tr("play..."));
    connect(this->audiocontrols_playAct, &QAction::triggered,
            this, &MainWindow::audiocontrols_play);

    this->audiocontrols_stopAct = new QAction( *(this->current_dipylonui.icon_audio_stop),
                                               tr("stop"),
                                               this);
    this->audiocontrols_stopAct->setStatusTip(tr("stop..."));
    connect(this->audiocontrols_stopAct, &QAction::triggered,
            this, &MainWindow::audiocontrols_stop);
}

/*______________________________________________________________________________

  MainWindow::createMenus
______________________________________________________________________________*/
void MainWindow::createMenus() {
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(newAct);
  fileMenu->addAction(openAct);
  fileMenu->addAction(saveAct);
  fileMenu->addAction(saveAsAct);
  #ifdef READANDWRITE
  fileMenu->addAction(saveMainFileOfADipyDocAsAct);
  #endif
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);

  editMenu = menuBar()->addMenu(tr("&Edit"));
  editMenu->addAction(cutAct);
  editMenu->addAction(copyAct);
  editMenu->addAction(pasteAct);

  menuBar()->addSeparator();

  helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAct);
  helpMenu->addAction(aboutQtAct);
}

/*______________________________________________________________________________

  MainWindow::createStatusBar
______________________________________________________________________________*/
void MainWindow::createStatusBar() {
    statusBar()->showMessage(tr("Ready"));
}

/*______________________________________________________________________________

  MainWindow::createToolBars
______________________________________________________________________________*/
void MainWindow::createToolBars() {
    this->fileToolBar = addToolBar(tr("File"));
    this->fileToolBar->addAction(this->newAct);
    this->fileToolBar->addAction(this->openAct);
    this->fileToolBar->addAction(this->saveAct);

    this->editToolBar = addToolBar(tr("Edit"));
    this->editToolBar->addAction(this->cutAct);
    this->editToolBar->addAction(this->copyAct);
    this->editToolBar->addAction(this->pasteAct);

    this->modecontrolToolBar = addToolBar(tr("AudioControls"));
    this->modecontrolToolBar->addAction(this->readingmodeAct);
    this->modecontrolToolBar->addAction(this->audiocontrols_playAct);
    this->modecontrolToolBar->addAction(this->audiocontrols_stopAct);
}

/*______________________________________________________________________________

  MainWindow::documentWasModified
______________________________________________________________________________*/
void MainWindow::documentWasModified() {
    setWindowModified(source_editor->document()->isModified());
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

  this->current_dipylonui.current_dipydoc = DipyDoc(directoryName);

  if( this->current_dipylonui.current_dipydoc.well_initialized() == false ) {

    // an error occurs :
    QMessageBox msgBox;
    msgBox.setText( tr("Unable to load any valid Dipydoc's document from <b>") + directoryName + "</b> ." +\
                    "<br/><br/>" + this->current_dipylonui.current_dipydoc.diagnosis() + \
                    "<br/><br/>" + tr("See more details below.") );
    this->current_dipylonui.current_dipydoc.err_messages.prepend( "internal state = " + \
                                       QString().setNum(this->current_dipylonui.current_dipydoc.internal_state()) );

    msgBox.setDetailedText( this->current_dipylonui.current_dipydoc.err_messages.join("\n\n") + \
                            "\n\n\n*** internal debug message ***\n\n\n" + \
                            DebugMsg::messages.join("\n") );
    msgBox.exec();
  }
  else {
    // no error, let's load the DipyDoc :
    this->load_text(this->current_dipylonui.current_dipydoc.source_text);

    if( this->current_dipylonui.current_dipydoc.audiorecord.found == true ) {
      DebugMsg() << "loading audiofile" << this->current_dipylonui.current_dipydoc.audiorecord.filename;
      this->audio_player->setMedia(QUrl::fromLocalFile(this->current_dipylonui.current_dipydoc.audiorecord.filename));
    }
  }

  #ifndef QT_NO_CURSOR
  QApplication::restoreOverrideCursor();
  #endif

  if( this->current_dipylonui.current_dipydoc.well_initialized() == true ) {

    // update source editor aspect :
    this->source_editor->update_aspect_from_dipydoc_aspect_informations();

    // update commentary editor aspect :
    this->commentary_editor->update_aspect_from_dipydoc_aspect_informations();

    // update the rest of the UI :
    this->update_icons();
    setCurrentDipyDoc(directoryName);
    statusBar()->showMessage(tr("DipyDoc loaded"), 2000);
  }

  /*
    Let's initialize this->current_dipylonui.path_to_dipydocs :

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
    this->current_dipylonui.path_to_dipydocs = parent_directory.absolutePath();
  }
  else {
    /*
      No, for some reasons the upper directory isn't readable : we
      keep the current directory.
    */
    this->current_dipylonui.path_to_dipydocs = directoryName;
  }

  // default reading mode :
  this->current_dipylonui.reading_mode         = DipylonUI::READINGMODE::READINGMODE_GRAMMAR;
  this->current_dipylonui.reading_mode_details = DipylonUI::READINGMODEDETAILS::READINGMODEDETAIL_GRAMMAR;

  // updating the UI :
  this->update_icons();
}

/*______________________________________________________________________________

  MainWindow::load_text

________________________________________________________________________________*/
void MainWindow::load_text(const DipyDocSourceText& source_text)  {
  this->source_editor->load_text(source_text);
}

/*______________________________________________________________________________

  MainWindow::maybeSave

 http://qt-project.org/doc/qt-5/qtwidgets-mainwindows-application-example.html

The maybeSave() function is called to save pending changes. If there are pending changes, it pops up a QMessageBox giving the user to save the document. The options are QMessageBox::Yes, QMessageBox::No, and QMessageBox::Cancel. The Yes button is made the default button (the button that is invoked when the user presses Return) using the QMessageBox::Default flag; the Cancel button is made the escape button (the button that is invoked when the user presses Esc) using the QMessageBox::Escape flag.

The maybeSave() function returns true in all cases, except when the user clicks Cancel. The caller must check the return value and stop whatever it was doing if the return value is false.
______________________________________________________________________________*/
bool MainWindow::maybeSave() {
    if (source_editor->document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Application"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

/*______________________________________________________________________________

  MainWindow::newFile
_____________________________________________________________________________*/
void MainWindow::newFile() {
  if (maybeSave()) {
      source_editor->clear();
      setCurrentDipyDoc("");
  }
}

/*______________________________________________________________________________

  MainWindow::open
______________________________________________________________________________*/
void MainWindow::open(void) {

  if (maybeSave()) {
    QString directoryName = QFileDialog::getExistingDirectory(this,
                                                              QObject::tr("Open a DipyDoc directory"),
                                                              this->current_dipylonui.path_to_dipydocs,
                                                              QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!directoryName.isEmpty()) {
      // loading the DipyDoc :
      this->loadDipyDoc(directoryName);
    }
  }
}

/*______________________________________________________________________________

  MainWindow::readingmodeAct_buttonpressed()

  connected to readingmodeAct::triggered()
______________________________________________________________________________*/
void MainWindow::readingmodeAct_buttonpressed(void) {
  switch (this->current_dipylonui.reading_mode ) {

    case DipylonUI::READINGMODE_KARAOKE: {
      this->audiocontrols_stop();
      this->current_dipylonui.reading_mode = DipylonUI::READINGMODE_GRAMMAR;
      this->current_dipylonui.reading_mode_details = DipylonUI::READINGMODEDETAIL_GRAMMAR;
      DebugMsg() << "switched to GRAMMAR mode";
      break;
    }

    case DipylonUI::READINGMODE_GRAMMAR: {
      this->current_dipylonui.reading_mode = DipylonUI::READINGMODE_KARAOKE;
      this->current_dipylonui.reading_mode_details = DipylonUI::READINGMODEDETAIL_KARAOKE_STOP;
      DebugMsg() << "switched to KARAOKE mode";
      break;
    }

    default : {
      this->current_dipylonui.reading_mode = DipylonUI::READINGMODE_UNDEFINED;
      DebugMsg() << "switched to UNDEFINED mode";
      break;
    }
  }

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

  MainWindow::save
______________________________________________________________________________*/
bool MainWindow::save() {
  if (curFile.isEmpty()) {
      return saveAs();
  } else {
      return saveFile(curFile);
  }
}

/*______________________________________________________________________________

  MainWindow::saveAs
______________________________________________________________________________*/
bool MainWindow::saveAs() {
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.exec();
    QStringList files = dialog.selectedFiles();

    if (files.isEmpty())
        return false;

    return saveFile(files.at(0));
}

/*______________________________________________________________________________

  MainWindow::saveFile

________________________________________________________________________________*/
bool MainWindow::saveFile(const QString &fileName) {
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
    out << source_editor->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentDipyDoc(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
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
    out << this->current_dipylonui.current_dipydoc.get_xml_repr();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentDipyDoc(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
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

  /*
    "reading mode" icon :
  */
  switch (this->current_dipylonui.reading_mode ) {

    case DipylonUI::READINGMODE_KARAOKE: {
      this->readingmodeAct->setIcon( *(this->current_dipylonui.icon_readingmode_karaoke) );
      break;
    }

    case DipylonUI::READINGMODE_GRAMMAR: {
      this->readingmodeAct->setIcon( *(this->current_dipylonui.icon_readingmode_grammar) );
      break;
    }

    default : {
      break;
    }
  }

  /*
    "audio controls" icons :
  */
  if (this->current_dipylonui.reading_mode != DipylonUI::READINGMODE_KARAOKE ||
      this->current_dipylonui.current_dipydoc.well_initialized() == false ||
      (this->current_dipylonui.current_dipydoc.well_initialized() == true and
       this->current_dipylonui.current_dipydoc.audiorecord.found == false)) {
    /*
       No karaoke mode or no current DipyDoc or no audio in the current DipyDoc :
    */
    this->audiocontrols_playAct->setVisible(false);
    this->audiocontrols_playAct->setEnabled(false);
    // we refresh the icon to display it using only shades of gray :
    this->audiocontrols_playAct->setIcon( *(this->current_dipylonui.icon_audio_play) );

    this->audiocontrols_stopAct->setVisible(false);
    this->audiocontrols_stopAct->setEnabled(false);
    // we refresh the icon to display it using only shades of gray :
    this->audiocontrols_stopAct->setIcon( *(this->current_dipylonui.icon_audio_stop) );
  }
  else {
    /*
       the current DipyDoc is ok and contains an audio record :
    */
    this->audiocontrols_playAct->setVisible(true);
    this->audiocontrols_playAct->setEnabled(true);
    // we refresh the icon to display it in colors :
    this->audiocontrols_playAct->setIcon( *(this->current_dipylonui.icon_audio_play) );

    this->audiocontrols_stopAct->setVisible(true);
    this->audiocontrols_stopAct->setEnabled(true);
    // we refresh the icon to display it in colors :
    this->audiocontrols_stopAct->setIcon( *(this->current_dipylonui.icon_audio_stop) );
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
