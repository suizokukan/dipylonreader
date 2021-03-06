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

    ❏DipylonReader❏ : pos/posintext/posintext.h

    A PosInText (=text position) is an integer greater or equal to 0.

*******************************************************************************/

#ifndef CPPDIPYLON_POS_POSINTEXT_POSINTEXT_H_
#define CPPDIPYLON_POS_POSINTEXT_POSINTEXT_H_

#include <utility>
#include <vector>

// base type :
typedef unsigned int PosInText;
const PosInText MINIMAL_POSINTEXT = 0;
const PosInText MAXIMAL_POSINTEXT = 0xFFFFFFFF;

typedef std::vector<std::pair<PosInText, PosInText> > VPairOfPosInText;

typedef std::vector<std::pair<PosInText, PosInText> >::const_iterator VPairOfPosInTextCI;

#endif  // CPPDIPYLON_POS_POSINTEXT_POSINTEXT_H_
