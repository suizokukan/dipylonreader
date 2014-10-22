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

    ❏DipylonReader❏ : qt/readingmodes.h

*******************************************************************************/

#ifndef CPPDIPYLON_QT_READINGMODES_H_
#define CPPDIPYLON_QT_READINGMODES_H_

/*
  reading mode type

  see UI::READINGMODE and UI::READINGMODEDETAILS for the values.
*/
typedef unsigned int ReadingMode;
typedef unsigned int ReadingModeDetails;

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
  READINGMODE_LMODE     = 2,
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

#endif  // CPPDIPYLON_QT_READINGMODES_H_
