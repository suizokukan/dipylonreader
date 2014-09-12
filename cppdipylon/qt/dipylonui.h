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

    ❏DipylonReader❏ : qt/dipylonui.h

    Definition of the "user interface".

    o DipylonUI class

*******************************************************************************/

#ifndef CPPDIPYLON_QT_DIPYLONUI_H_
#define CPPDIPYLON_QT_DIPYLONUI_H_

#include <QApplication>
#include <QString>
#include <QTranslator>
#include <QFontDatabase>

#include "./fixedparameters.h"
#include "qt/mainwindow.h"
#include "dipydoc/dipydoc.h"

class MainWindow;

/*
  reading mode type
*/
typedef unsigned int ReadingMode;
typedef unsigned int ReadingModeDetails;

/*______________________________________________________________________________

  DipylonUI class : a wrapper around the QApplication object.
________________________________________________________________________________*/
class DipylonUI {
  friend class Settings;
  friend class MainWindow;
  friend class SourceEditor;
  friend class CommentaryEditor;

 private:
  // set to true if no 'settings' (see QSettings) can be read.
  bool        first_launch;
  // display splash screen when the program has been launched ?
  bool        display_splashscreen = fixedparameters::default__display_splashscreen;

  // current document displayed in the source zone :
  DipyDoc     current_dipydoc = DipyDoc();

  QIcon*      icon_new = nullptr;
  QIcon*      icon_open = nullptr;
  QIcon*      icon_save = nullptr;
  QIcon*      icon_cut = nullptr;
  QIcon*      icon_copy = nullptr;
  QIcon*      icon_paste = nullptr;
  QIcon*      icon_audio_pause = nullptr;
  QIcon*      icon_audio_play = nullptr;
  QIcon*      icon_audio_play_unavailable = nullptr;
  QIcon*      icon_audio_stop = nullptr;
  QIcon*      icon_audio_stop_unavailable = nullptr;
  QIcon*      icon_readingmode_rlmode = nullptr;
  QIcon*      icon_readingmode_amode = nullptr;

  // path to the DipyDocs : the initial value is initialized by DipylonUI's constructor.
  QString     path_to_dipydocs;

  MainWindow* mainWin = nullptr;

 public:
  /*
    READINGMODE, READINGMODEDETAILS :

    o READINGMODE_UNDEFINED : no reading mode defined
      o READINGMODEDETAIL_UNDEFINED

    o READINGMODEDETAIL_AMODE : AMODE only, no sound

    o READINGMODE_RLMODE : audio record
      o READINGMODEDETAIL_RLMODE_PLAYING
      o READINGMODEDETAIL_RLMODE_ONPAUSE
  */
  enum READINGMODE : ReadingMode {
    READINGMODE_UNDEFINED = 0,
    READINGMODE_RLMODE    = 1,
    READINGMODE_AMODE     = 2,
  };
  enum READINGMODEDETAILS : ReadingModeDetails {
      READINGMODEDETAIL_UNDEFINED      = 0,
      READINGMODEDETAIL_RLMODE_PLAYING = 0x1000,
      READINGMODEDETAIL_RLMODE_ONPAUSE = 0x1001,
      READINGMODEDETAIL_RLMODE_STOP    = 0x1002,
      READINGMODEDETAIL_AMODE          = 0x2000,
  };

  ReadingMode        reading_mode = DipylonUI::READINGMODE_UNDEFINED;
  ReadingModeDetails reading_mode_details = DipylonUI::READINGMODEDETAIL_UNDEFINED;

                     DipylonUI(void);
                     ~DipylonUI(void);
  QString            get_translations_for(PosInText, PosInText) const;
  int                go(int argc, char **argv);
  void               read_settings(void);
  void               set_content_of_the_commentary_editor(QString text);
  void               update_commentary_editor__translation_expected(PosInTextRanges&);
  void               write_settings(void);
};

#endif  // CPPDIPYLON_QT_DIPYLONUI_H_
