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
#include <QString>
#include <QTranslator>

#include "./fixedparameters.h"
#include "debugmsg/debugmsg.h"
#include "dipydoc/dipydoc.h"
#include "dipydoc/menunames.h"
#include "qt/mainwindow.h"

class MainWindow;

/*
  reading mode type

  see UI::READINGMODE and UI::READINGMODEDETAILS for the values.
*/
typedef unsigned int ReadingMode;
typedef unsigned int ReadingModeDetails;

/*______________________________________________________________________________

  UI class : a wrapper around the QApplication object.
________________________________________________________________________________*/
class UI {
  friend class CommentaryEditor;
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

  // set to true if no 'settings' (see QSettings) can be read.
  bool        first_launch;
  // display splash screen when the program has been launched ?
  bool        display_splashscreen = fixedparameters::default__display_splashscreen;

  // current document displayed in the source zone :
  DipyDoc     current_dipydoc = DipyDoc();

  QIcon*      icon_app = nullptr;
  QIcon*      icon_audio_pause = nullptr;
  QIcon*      icon_audio_play = nullptr;
  QIcon*      icon_audio_play_unavailable = nullptr;
  QIcon*      icon_audio_stop = nullptr;
  QIcon*      icon_audio_stop_unavailable = nullptr;
  QIcon*      icon_downloaddemo = nullptr;
  QIcon*      icon_hide_toolbars = nullptr;
  QIcon*      icon_open = nullptr;
  QIcon*      icon_readingmode_amode_off = nullptr;
  QIcon*      icon_readingmode_amode_on  = nullptr;
  QIcon*      icon_readingmode_lmode_off = nullptr;
  QIcon*      icon_readingmode_lmode_on  = nullptr;
  QIcon*      icon_readingmode_rmode_off = nullptr;
  QIcon*      icon_readingmode_rmode_on  = nullptr;
  QIcon*      icon_save = nullptr;
  QIcon*      icon_textminus = nullptr;
  QIcon*      icon_textplus = nullptr;

  // path to the DipyDocs : the initial value is initialized by UI's constructor.
  QString     path_to_dipydocs;

  // menu names available :
  MenuNames   available_menu_names;

  MainWindow* mainWin = nullptr;

  // if set to true, protect the commentary zone to be modified.
  bool        selected_text_and_blocked_commentaries = false;

 public:
  /*
    READINGMODE, READINGMODEDETAILS :

    o READINGMODE_UNDEFINED : no reading mode defined
      o READINGMODEDETAIL_UNDEFINED

    o READINGMODEDETAIL_AMODE : "analyse" mode

    o READINGMODE_RMODE : "read" mode
      o READINGMODEDETAIL_LMODE

    o READINGMODE_LMODE : "read and listen" mode
      o READINGMODEDETAIL_LMODE_PLAYING
      o READINGMODEDETAIL_LMODE_ONPAUSE
  */
  enum READINGMODE : ReadingMode {
    READINGMODE_UNDEFINED = 0,
    READINGMODE_RMODE     = 1,
    READINGMODE_LMODE    = 2,
    READINGMODE_AMODE     = 3,
  };
  enum READINGMODEDETAILS : ReadingModeDetails {
      READINGMODEDETAIL_UNDEFINED      = 0,
      READINGMODEDETAIL_RMODE          = 0x1000,
      READINGMODEDETAIL_LMODE_PLAYING  = 0x2000,
      READINGMODEDETAIL_LMODE_ONPAUSE  = 0x2001,
      READINGMODEDETAIL_LMODE_STOP     = 0x2002,
      READINGMODEDETAIL_AMODE          = 0x3000,
  };

  ReadingMode        reading_mode = UI::READINGMODE_UNDEFINED;
  ReadingModeDetails reading_mode_details = UI::READINGMODEDETAIL_UNDEFINED;

                     UI(void);
                     ~UI(void);
  bool               at_least_one_dipydoc_has_been_loaded(void) const;
  QString            get_translations_for(PosInText, PosInText) const;
  int                go(int argc, char **argv);
  void               read_menu_names(void);
  void               read_settings(void);
  void               set_content_of_the_commentary_editor(QString text);
  void               update_commentary_editor__translation_expected(PosInTextRanges&);
  void               write_settings(void);
};

#endif  // CPPDIPYLON_QT_UI_H_
