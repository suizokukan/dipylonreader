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

    ❏DipylonReader❏ : pos/posinaudio/posinaudio.h

    A PosInAudio (=audio position) is an integer.

*******************************************************************************/

#ifndef CPPDIPYLON_POS_POSINAUDIO_POSINAUDIO_H_
#define CPPDIPYLON_POS_POSINAUDIO_POSINAUDIO_H_

#include <QtGlobal>

#include <utility>

// base type :

/*
  qint64 : Typedef for long long int (__int64 on Windows). This type is guaranteed to be 64-bit on all platforms supported by Qt.

 from http://qt-project.org/doc/qt-5/qtglobal.html#qint64-typedef

 Several lines of code (linked to Qt signals) in this project assume that PosInAudio is equal to qint64.
 see http://stackoverflow.com/questions/25402685
*/
typedef qint64 PosInAudio;

typedef std::pair<PosInAudio, PosInAudio> PairOfPosInAudio;

#endif  // CPPDIPYLON_POS_POSINAUDIO_POSINAUDIO_H_
