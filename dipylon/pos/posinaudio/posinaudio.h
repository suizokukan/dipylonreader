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

    ❏Dipylon❏ : pos/posinaudio/posinaudio.h

    A PosInAudio (=audio position) is an integer.

*******************************************************************************/

#ifndef POSINAUDIO_H
#define POSINAUDIO_H

#include <vector>
#include <QtGlobal>

// base type :

/*
  qint64 : Typedef for long long int (__int64 on Windows). This type is guaranteed to be 64-bit on all platforms supported by Qt.

 from http://qt-project.org/doc/qt-5/qtglobal.html#qint64-typedef
*/
typedef qint64 PosInAudio;

typedef std::pair<PosInAudio, PosInAudio> PairOfPosInAudio;

/*______________________________________________________________________________

  PairOfPosInAudioHasher
________________________________________________________________________________*/
struct PairOfPosInAudioHasher {
  std::size_t operator()(const PairOfPosInAudio& k) const;
};

#endif