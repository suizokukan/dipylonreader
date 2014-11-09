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

    ❏DipylonReader❏ : qt/ui.h

    Definition of the "user interface".

    o UI class

*******************************************************************************/

#ifndef CPPDIPYLON_QT_UI_H_
#define CPPDIPYLON_QT_UI_H_

#include <QApplication>
#include <QFontDatabase>
#include <QNetworkAccessManager>
#include <QObject>
#include <QSplashScreen>
#include <QString>
#include <QTranslator>

#include "./fixedparameters.h"
#include "debugmsg/debugmsg.h"
#include "dipydoc/dipydoc.h"
#include "dipydoc/menunames.h"
#include "qt/mainwindow.h"
#include "qt/presentationscreen.h"
#include "qt/readingmodes.h"

class MainWindow;

/*______________________________________________________________________________

  UI class : a wrapper around the QApplication object.
________________________________________________________________________________*/
class UI {
  friend class CommentaryEditor;
  friend class CommentaryToolBar;
  friend class CommentaryZone;
  friend class DownloadDemoDipydocs;
  friend class MainWindow;
  friend class Settings;
  friend class SourceEditor;
  friend class SourceToolBar;
  friend class SourceZone;

 public:
  /* unique network manager of the program :

     o initialized by MainWindow::MainWindow() since this object has to be
     initialized inside the event loop.
     o destroyed by ~UI
  */
  QNetworkAccessManager* network_manager = nullptr;

 private:
  /*
    unique PSLauncher object, used to display "splashscreens".

    n.b. : PSLauncher stands for P(resentation)S(creen)Launcher
  */
  PSLauncher presentation_screen_launcher = PSLauncher();

  /*
    settings :

    see UI::read_settings() and UI::write_settings()
  */
  // set to true if no 'settings' (see QSettings) can be read.
  bool        first_launch;
  // display splash screen when the program has been launched ?
  bool        display_splashscreen = fixedparameters::default__display_splashscreen;

  // path to the DipyDocs : the initial value is initialized by UI's constructor.
  QString     path_to_dipydocs;

  // menu names available :
  MenuNames   available_menu_names;

  MainWindow* mainWin = nullptr;

  QSplashScreen* splashscreen = nullptr;

 public:
                     UI(void);
                    ~UI(void);
  int                go(int argc, char **argv);

 private:
  bool               at_least_one_dipydoc_has_been_loaded(void) const;
  void               display_the_splashscreen(const QString& text);
  void               read_menu_names(void);
  void               read_settings(void);
  void               set_content_of_the_commentary_editor(QString text);
  void               update_commentary_editor__translation_expected(PosInTextRanges&);
  void               write_settings(void);
};

#endif  // CPPDIPYLON_QT_UI_H_
