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

    ❏DipylonReader❏ : qt/mainwindow.h

    about the MainWindow object : see http://qt-project.org/doc/qt-5/qmainwindow.html

*******************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./fixedparameters.h"
#include "debugmsg/debugmsg.h"
#include "dipydoc/dipydoc.h"
#include "qt/commentaryeditor.h"
#include "qt/commentaryzone.h"
#include "qt/downloaddemodipydocs.h"
#include "qt/sourceeditor.h"
#include "qt/sourcezone.h"
#include "qt/ui.h"

#include <QFile>
#include <QFrame>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QtWidgets>
#include <QTimer>
#include <QToolBar>

class CommentaryEditor;
class QAction;
class QMenu;
class QSplitter;
class SourceEditor;
class UI;

class MainWindow : public QMainWindow
{
friend class CommentaryEditor;
friend class CommentaryToolBar;
friend class CommentaryZone;
friend class SourceEditor;
friend class SourceToolBar;
friend class SourceZone;
friend class UI;

    Q_OBJECT

public:
    MainWindow(UI&);

    void load_text(const DipyDocSourceText& source_text);

protected:
    void closeEvent(QCloseEvent *event);

 private slots:
    void about(void);
    void audiocontrols_play(void);
    void audiocontrols_stop(void);
    void audio_position_changed(PosInAudio);
    void closing(void);
    void hidetoolbarsAct__buttonPressed(void);
    void open(void);
    void popup_mainmenuAct__buttonPressed(void);
    void readingmode_aAct__buttonpressed(void);
    void readingmode_rAct__buttonpressed(void);
    void readingmode_lAct__buttonpressed(void);
    bool saveMainFileOfADipyDocAs(void);

private:
    UI& ui;

    void    createActions(void);
    void    createMenus(void);
    void    createStatusBar(void);
    void    createMainToolBars(void);
    void    download_dipydocs_demo(void);
    void    fill_open_menu(void);
    void    init(void);
    void    loadDipyDoc(const QString&);
    void    load_a_dipydoc_from_a_qaction(void);
    void    readSettings(void);
    void    setCurrentDipyDoc(const QString&);
    void    update_icons(void);
    void    writeSettings(void);

    QFrame*           commentary_zone = nullptr;
    CommentaryEditor* commentary_editor = nullptr;
    QToolBar*         commentary_toolbar = nullptr;
    QFrame*           source_zone = nullptr;
    SourceEditor*     source_editor = nullptr;
    QToolBar*         source_toolbar = nullptr;

    QSplitter*        main_splitter = nullptr;
    QString           curFile;

    QMenu     *fileMenu = nullptr;
    QMenu     *openMenu = nullptr;
    QMenu     *helpMenu = nullptr;
    QMenu     *mainpopupmenu = nullptr;

    QAction*   aboutAct = nullptr;
    QAction*   commentary_textminusAct = nullptr;
    QAction*   commentary_textplusAct = nullptr;
    QAction*   downloaddemoAct = nullptr;
    QAction*   exitAct = nullptr;
    QAction*   hidetoolbarsAct = nullptr;
    QAction*   openAct = nullptr;
    QAction*   popup_mainmenuAct = nullptr;
    QAction*   saveMainFileOfADipyDocAsAct = nullptr;
    QAction*   source_textminusAct = nullptr;
    QAction*   source_textplusAct = nullptr;

    QAction*  readingmode_aAct = nullptr;
    QAction*  readingmode_rAct = nullptr;
    QAction*  readingmode_lAct = nullptr;
    QAction*  audiocontrols_playAct = nullptr;
    QAction*  audiocontrols_stopAct = nullptr;

    QToolBar  *mainwintoolbar = nullptr;
    QToolBar  *editToolBar = nullptr;
    QToolBar  *modecontrolToolBar = nullptr;

    QMediaPlayer* audio_player = nullptr;
};

#endif
