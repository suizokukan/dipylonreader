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

    ❏Dipylon❏ : posintxt/vectorposranges.cpp

    See vectorposranges.h for the documentation

*******************************************************************************/

#include "posintxt/vectorposranges.h"

/*______________________________________________________________________________

        PosRanges::sort()
______________________________________________________________________________*/
void VectorPosRanges::sort(void) {

  std::sort( this->vposranges.begin(),
             this->vposranges.end(),
             VectorPosRangesCMP(this) );
}

/*______________________________________________________________________________

        PosRanges::to_str : return a QString representation of this.
______________________________________________________________________________*/
QString VectorPosRanges::to_str(void) const {

  QString res = QString("");

  // i is an iterator over PosRanges objects :
  for(auto &i : this->vposranges) {
    res += i.to_str();
    res += this->MAIN_SEPARATOR;
  }

  // removing the last MAIN_SEPARATOR character :
  res.chop(1);

  return res;
}
