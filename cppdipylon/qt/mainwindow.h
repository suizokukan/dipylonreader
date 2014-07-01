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
#include <QFile>  // [XAV]QFile

class QAction;
class QMenu;
class QSplitter;
class DipylonUI;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DipylonUI&);

    void load_text(const QString& source_text); // XAV

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    bool saveDipyDocAs();
    void about();
    void documentWasModified();

    void audiocontrols_play(void); // XAV
    void audiocontrols_stop(void); // XAV
    void audio_position_changed(qint64); // XAV

    void closing(void);	// XAV

private:
    DipylonUI& current_dipylonui;

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    SourceEditor *source_editor = nullptr;
    CommentaryEditor *commentary_zone = nullptr;
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
    QAction *saveDipyDocAsAct = nullptr;
    QAction *exitAct = nullptr;
    QAction *cutAct = nullptr;
    QAction *copyAct = nullptr;
    QAction *pasteAct = nullptr;
    QAction *aboutAct = nullptr;
    QAction *aboutQtAct = nullptr;

    QAction* audiocontrols_playAct = nullptr;     // XAV
    QAction* audiocontrols_stopAct = nullptr;     // XAV
    QToolBar* audiocontrolsToolBar = nullptr;     // XAV

    QMediaPlayer* audio_player = nullptr;
};

#endif
