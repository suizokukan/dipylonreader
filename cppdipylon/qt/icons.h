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

    ❏DipylonReader❏ : qt/icons.h

*******************************************************************************/

#ifndef CPPDIPYLON_QT_ICONS_H_
#define CPPDIPYLON_QT_ICONS_H_

#include <QIcon>

#include "debugmsg/debugmsg.h"

/*______________________________________________________________________________

  Icons class
_______________________________________________________________________________*/
struct Icons {
  void        load_icons(void);
             ~Icons(void);

  QIcon*      app = nullptr;
  QIcon*      audio_pause = nullptr;
  QIcon*      audio_play = nullptr;
  QIcon*      audio_play_unavailable = nullptr;
  QIcon*      audio_stop = nullptr;
  QIcon*      audio_stop_unavailable = nullptr;
  QIcon*      down = nullptr;
  QIcon*      downloaddemo = nullptr;
  QIcon*      hide_toolbars_off = nullptr;
  QIcon*      hide_toolbars_on = nullptr;
  QIcon*      level = nullptr;
  QIcon*      open = nullptr;
  QIcon*      popup_mainmenu = nullptr;
  QIcon*      readingmode_amode_off = nullptr;
  QIcon*      readingmode_amode_on  = nullptr;
  QIcon*      readingmode_lmode_off = nullptr;
  QIcon*      readingmode_lmode_on  = nullptr;
  QIcon*      readingmode_rmode_off = nullptr;
  QIcon*      readingmode_rmode_on  = nullptr;
  QIcon*      save = nullptr;
  QIcon*      textminus = nullptr;
  QIcon*      textplus = nullptr;
  QIcon*      up = nullptr;
};

#endif  // CPPDIPYLON_QT_ICONS_H_
