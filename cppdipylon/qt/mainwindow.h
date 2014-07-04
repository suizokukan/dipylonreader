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

    ❏Dipylon❏ : qt/mainwindow.h

    the MainWindow object : see http://qt-project.org/doc/qt-5/qmainwindow.html

*******************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class SourceEditor;

#include "fixedparameters.h"
#include "qt/sourceeditor.h"
#include "qt/commentaryeditor.h"
#include "dipydoc/dipydoc.h"
#include "qt/dipylonui.h"

#include <QMediaPlayer>
#include <QMainWindow>
#include <QtWidgets>
#include <QFile>

class QAction;
class QMenu;
class QSplitter;
class DipylonUI;
class CommentaryEditor;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DipylonUI&);

    void load_text(const QString& source_text);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    bool saveMainFileOfADipyDocAs();
    void about();
    void documentWasModified();

    void audiocontrols_play(void);
    void audiocontrols_stop(void);
    void audio_position_changed(qint64);

    void closing(void);

private:
    DipylonUI& current_dipylonui;

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void loadDipyDoc(const QString&);
    bool saveFile(const QString &fileName);
    void setCurrentDipyDoc(const QString&);
    QString strippedName(const QString &fullFileName);


    SourceEditor *source_editor = nullptr;
    CommentaryEditor *commentary_editor = nullptr;
    QSplitter *main_splitter = nullptr;
    QString curFile;

    QMenu *fileMenu = nullptr;
    QMenu *editMenu = nullptr;
    QMenu *helpMenu = nullptr;
    QToolBar *fileToolBar = nullptr;
    QToolBar *editToolBar = nullptr;
    QAction *newAct = nullptr;
    QAction *openAct = nullptr;
    QAction *saveAct = nullptr;
    QAction *saveAsAct = nullptr;
    QAction *saveMainFileOfADipyDocAsAct = nullptr;
    QAction *exitAct = nullptr;
    QAction *cutAct = nullptr;
    QAction *copyAct = nullptr;
    QAction *pasteAct = nullptr;
    QAction *aboutAct = nullptr;
    QAction *aboutQtAct = nullptr;

    QAction* audiocontrols_playAct = nullptr;
    QAction* audiocontrols_stopAct = nullptr;
    QToolBar* audiocontrolsToolBar = nullptr;

    QMediaPlayer* audio_player = nullptr;
};

#endif
