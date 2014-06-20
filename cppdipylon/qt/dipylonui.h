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

    ❏Dipylon❏ : qt/dipylonui.h

    Definition of the "user interface".

*******************************************************************************/

#ifndef DIPYLONUI_H
#define DIPYLONUI_H

#include "fixedparameters.h"
#include "qt/mainwindow.h"
#include "dipydoc/dipydoc.h"

#include <QApplication>
#include <QString>
#include <QTranslator>

/*
  reading mode type
*/
typedef unsigned int ReadingMode;
typedef unsigned int ReadingModeDetails;

/*______________________________________________________________________________

  DipylonUI class : a wrapper around the QApplication object.
________________________________________________________________________________*/
class DipylonUI {

friend class MainWindow;

private:
  // attributes used to initialize the QApplication constructor :
  int         cmdline_argc = 0;
  char**      cmdline_argv = nullptr;

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
  QIcon*      icon_audio_stop = nullptr;

public:

  enum READINGMODE : ReadingMode {
      READINGMODE_UNDEFINED = 0,
      READINGMODE_KARAOKE = 1,
  };

  enum READINGMODEDETAILS : ReadingModeDetails {
      READINGMODEDETAIL_UNDEFINED = 0,
      READINGMODEDETAIL_KARAOKE_PLAYING = 0x1000,
      READINGMODEDETAIL_KARAOKE_ONPAUSE = 0x1001,
  };


  ReadingMode        reading_mode = DipylonUI::READINGMODE_UNDEFINED;
  ReadingModeDetails reading_mode_details = DipylonUI::READINGMODEDETAIL_UNDEFINED;

                     DipylonUI(int argc, char **argv);
                     ~DipylonUI(void);
  int                go(void);
};

#endif
