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

    ❏DipylonReader❏ : qt/icons.cpp

    See icons.h for the documentation.

*******************************************************************************/

#include "qt/icons.h"

/*______________________________________________________________________________

  Icons::load_icons()

_______________________________________________________________________________*/
void Icons::load_icons(void) {
  DebugMsg() << "Icons::load_icons : entry point";

  this->app                     = new QIcon(":/ressources/images/icons/application_icon.png");
  this->audio_pause             = new QIcon(":ressources/images/icons/audio_pause.png");
  this->audio_play              = new QIcon(":ressources/images/icons/audio_play.png");
  this->audio_play_unavailable  = new QIcon(":ressources/images/icons/audio_play_unavailable.png");
  this->audio_stop              = new QIcon(":ressources/images/icons/audio_stop.png");
  this->audio_stop_unavailable  = new QIcon(":ressources/images/icons/audio_stop_unavailable.png");
  this->downloaddemo            = new QIcon(":ressources/images/icons/downloaddemo.png");
  this->hide_toolbars_off       = new QIcon(":ressources/images/icons/hidetoolbars_off.png");
  this->hide_toolbars_on        = new QIcon(":ressources/images/icons/hidetoolbars_on.png");
  this->open                    = new QIcon(":ressources/images/icons/open.png");
  this->popup_mainmenu          = new QIcon(":ressources/images/icons/popup_mainmenu.png");
  this->readingmode_amode_off   = new QIcon(":ressources/images/icons/readingmode_amode_off.png");
  this->readingmode_amode_on    = new QIcon(":ressources/images/icons/readingmode_amode_on.png");
  this->readingmode_lmode_off   = new QIcon(":ressources/images/icons/readingmode_lmode_off.png");
  this->readingmode_lmode_on    = new QIcon(":ressources/images/icons/readingmode_lmode_on.png");
  this->readingmode_rmode_off   = new QIcon(":ressources/images/icons/readingmode_rmode_off.png");
  this->readingmode_rmode_on    = new QIcon(":ressources/images/icons/readingmode_rmode_on.png");
  this->textminus               = new QIcon(":ressources/images/icons/textminus.png");
  this->textplus                = new QIcon(":ressources/images/icons/textplus.png");

  DebugMsg() << "Icons::load_icons : exit point";
}

/*______________________________________________________________________________

  Icons::~Icons

  Icons destructor
_______________________________________________________________________________*/
Icons::~Icons(void) {
  DebugMsg() << "Icons::~Icons : entry point";

  delete this->audio_pause;
  delete this->audio_play;
  delete this->audio_play_unavailable;
  delete this->audio_stop;
  delete this->audio_stop_unavailable;
  delete this->downloaddemo;
  delete this->hide_toolbars_off;
  delete this->hide_toolbars_on;
  delete this->open;
  delete this->popup_mainmenu;
  delete this->readingmode_amode_off;
  delete this->readingmode_amode_on;
  delete this->readingmode_lmode_off;
  delete this->readingmode_lmode_on;
  delete this->readingmode_rmode_off;
  delete this->readingmode_rmode_on;
  delete this->save;
  delete this->textminus;
  delete this->textplus;

  DebugMsg() << "Icons::~Icons : exit point";
}
