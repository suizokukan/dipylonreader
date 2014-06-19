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

MainWindow::MainWindow(DipylonUI& dipylonui) : current_dipylonui(dipylonui)
{
    main_splitter = new QSplitter(this);
    main_splitter->setOrientation( Qt::Vertical );
    setCentralWidget(main_splitter);

    source_editor = new SourceEditor(this->current_dipylonui);
    commentary_zone = new CommentaryEditor();
    main_splitter->addWidget(source_editor);
    main_splitter->addWidget(commentary_zone);

    this->main_splitter->setSizes( fixedparameters::editors_size_in_main_splitter );

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    readSettings();

    connect(source_editor->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));

    setCurrentFile("");
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::closeEvent(QCloseEvent *arg_event)
{
    if (maybeSave()) {
        writeSettings();
        arg_event->accept();
    } else {
        arg_event->ignore();
    }
}

void MainWindow::newFile()
{
    if (maybeSave()) {
        source_editor->clear();
        setCurrentFile("");
    }
}

void MainWindow::open(void) {

    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

void MainWindow::open(QString file_name) {

    if (maybeSave()) {
        loadFile(file_name);
    }
}

bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.exec();
    QStringList files = dialog.selectedFiles();

    if (files.isEmpty())
        return false;

    return saveFile(files.at(0));
}

void MainWindow::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("The <b>Application</b> example demonstrates how to "
               "write modern GUI applications using Qt, with a menu bar, "
               "toolbars, and a status bar."));
}

void MainWindow::documentWasModified()
{
    setWindowModified(source_editor->document()->isModified());
}

void MainWindow::createActions()
{
    newAct = new QAction(QIcon(":ressources/images/icons/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":ressources/images/icons/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":ressources/images/icons/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    cutAct = new QAction(QIcon(":ressources/images/icons/cut.png"), tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), source_editor, SLOT(cut()));

    copyAct = new QAction(QIcon(":ressources/images/icons/copy.png"), tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, SIGNAL(triggered()), source_editor, SLOT(copy()));

    pasteAct = new QAction(QIcon(":ressources/images/icons/paste.png"), tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), source_editor, SLOT(paste()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
    connect(source_editor, SIGNAL(copyAvailable(bool)),
            cutAct, SLOT(setEnabled(bool)));
    connect(source_editor, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));

    // XAV :
    audiocontrols_playAct = new QAction(QIcon("ressources/images/icons/audio_play.png"), \
                                    tr("play"), this);
    audiocontrols_playAct->setStatusTip(tr("play..."));
    connect(audiocontrols_playAct, SIGNAL(triggered()), this, SLOT(audiocontrols_play()));

    audiocontrols_stopAct = new QAction(QIcon("ressources/images/icons/audio_stop.png"), \
                                    tr("stop"), this);
    audiocontrols_stopAct->setStatusTip(tr("stop..."));
    connect(audiocontrols_stopAct, SIGNAL(triggered()), this, SLOT(audiocontrols_stop()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
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

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);

    // XAV :
    audiocontrolsToolBar = addToolBar(tr("AudioControls"));
    audiocontrolsToolBar->addAction(audiocontrols_playAct);
    audiocontrolsToolBar->addAction(audiocontrols_stopAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings("QtProject", "Application Example");
    QPoint _pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize _size = settings.value("size", QSize(400, 400)).toSize();
    resize(_size);
    move(_pos);
}

void MainWindow::writeSettings()
{
    QSettings settings("QtProject", "Application Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

/* http://qt-project.org/doc/qt-5/qtwidgets-mainwindows-application-example.html

The maybeSave() function is called to save pending changes. If there are pending changes, it pops up a QMessageBox giving the user to save the document. The options are QMessageBox::Yes, QMessageBox::No, and QMessageBox::Cancel. The Yes button is made the default button (the button that is invoked when the user presses Return) using the QMessageBox::Default flag; the Cancel button is made the escape button (the button that is invoked when the user presses Esc) using the QMessageBox::Escape flag.

The maybeSave() function returns true in all cases, except when the user clicks Cancel. The caller must check the return value and stop whatever it was doing if the return value is false.
*/
bool MainWindow::maybeSave()
{
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

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    source_editor->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::saveFile(const QString &fileName)
{
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

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    source_editor->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

// XAV
void MainWindow::audiocontrols_play(void)
{
  qDebug() << "MainWindow::audiocontrols_play";
  // http://qt-project.org/doc/qt-5/qmediaplayer.html#seekable-prop
  audio_player = new QMediaPlayer(this);

  // can't change qint64 to PosInAudio here...
  connect(audio_player, SIGNAL(positionChanged(qint64)), this, SLOT(audio_position_changed(qint64)));
  audio_player->setMedia(QUrl::fromLocalFile("/home/suizokukan/projets/dipylon/last/dipylon/texts/Ovid_M_I_452_465/record.ogg"));
  // audio_player->setMedia(QUrl("qrc:/ressources/sounds/test.ogg"));
  audio_player->setNotifyInterval(fixedparameters::audio_notify_interval);
  audio_player->setVolume(50);
  audio_player->play();
}

// XAV
void MainWindow::audiocontrols_stop(void) {
  qDebug() << "MainWindow::audiocontrols_stop";

  if ( this->audio_player != nullptr ) {
    audio_player->stop();
  }
}

// [XAV]
// "qint64" and not PosInAudio
void MainWindow::audio_position_changed(qint64 arg_pos) {

  // where are the characters linked to "arg_pos" ?
  auto text_ranges = this->current_dipylonui.current_dipydoc.audio2text_contains( arg_pos );

  // the function modifies the appearence of such characters :
  this->source_editor->modify_the_text_format(6123, text_ranges);
}

// [XAV]
void MainWindow::load_text(const QString& source_text)  {
  this->source_editor->setPlainText(source_text);
}

// XAV
// app::SIGNAL(aboutToQuit()) -> mainWin::SLOT(closing())
/*
  from the doc of QCoreApplication::exec:

    We recommend that you connect clean-up code to the aboutToQuit() signal, instead of putting it in your application's main() function because on some platforms the QCoreApplication::exec() call may not return. For example, on Windows when the user logs off, the system terminates the process after Qt closes all top-level windows. Hence, there is no guarantee that the application will have time to exit its event loop and execute code at the end of the main() function after the QCoreApplication::exec() call.

    see e.g. http://stackoverflow.com/questions/8165487/how-to-do-cleaning-up-on-exit-in-qt
*/
void MainWindow::closing(void) {
  qDebug() << "MainWindow::closing";
}