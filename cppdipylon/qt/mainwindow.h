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

#ifndef CPPDIPYLON_QT_MAINWINDOW_H_
#define CPPDIPYLON_QT_MAINWINDOW_H_

#include <QFile>
#include <QFrame>
#include <QMainWindow>
#include <QtWidgets>
#include <QTimer>
#include <QToolBar>

#include "./fixedparameters.h"
#include "debugmsg/debugmsg.h"
#include "qt/downloaddemodipydocs.h"
#include "qt/scsplitter.h"
#include "qt/sctabs.h"
#include "qt/ui.h"

class CommentaryEditor;
class QAction;
class QMenu;
class QSplitter;
class SourceEditor;
class UI;

enum SETCOMMENTARYLOCATION : int {SETCOMMENTARYLOCATION__NOCOMMENT = 0,
                                  SETCOMMENTARYLOCATION__POPUP = 1,
                                  SETCOMMENTARYLOCATION__COMMENTARYZONE = 2};

class MainWindow : public QMainWindow {
friend class CommentaryEditor;
friend class CommentaryToolBar;
friend class CommentaryZone;
friend class SourceEditor;
friend class SourceToolBar;
friend class SourceZone;
friend class UI;

    Q_OBJECT

 public:
    explicit MainWindow(UI& _ui, QWidget *_parent = 0);

 protected:
    void closeEvent(QCloseEvent *event);

 private slots:  // NOLINT(whitespace/indent)
    void about(void);
    void cleaning_up_tabs_before_changing_current_tab(void);
    void closing(void);
    void hidetoolbarsAct__buttonPressed(void);
    void internalmsgAct__buttonPressed(void);
    void open(void);
    void popup_mainmenuAct__buttonPressed(void);
    void setnovelsizeAct__buttonPressed(void);
    void setcommentarylocationAct__buttonPressed(void);
    void setcommentarylocationAct__refreshui(void);

 private:
    UI&         ui;

    bool        visible_toolbars = fixedparameters::default__visible_toolbars;
    int         setcommentarylocation_value = SETCOMMENTARYLOCATION__NOCOMMENT;

    void        createActions(void);
    void        createMenus(void);
    void        createStatusBar(void);
    void        createMainToolBars(void);
    SCSplitter* current_splitter(void);
    void        download_dipydocs_demo(void);
    void        fill_open_menu(void);
    void        init(void);
    void        loadDipyDoc(const QString&);
    void        load_a_dipydoc_from_a_qaction(void);
    void        readSettings(void);
    void        update_icons(void);

    SCTabs*    sctabs = nullptr;

    QMenu     *fileMenu = nullptr;
    QMenu     *openMenu = nullptr;
    QMenu     *helpMenu = nullptr;
    QMenu     *mainpopupmenu = nullptr;

    QAction*   aboutAct = nullptr;
    QAction*   downloaddemoAct = nullptr;
    QAction*   exitAct = nullptr;
    QAction*   hidetoolbarsAct = nullptr;
    QAction*   internalmsgAct = nullptr;
    QAction*   openAct = nullptr;
    QAction*   popup_mainmenuAct = nullptr;
    QAction*   setnovelsizeAct = nullptr;
    QAction*   setcommentarylocationAct = nullptr;

    QToolBar  *mainwintoolbar = nullptr;
    QToolBar  *editToolBar = nullptr;
    QToolBar  *modecontrolToolBar = nullptr;
};

#endif  // CPPDIPYLON_QT_MAINWINDOW_H_
