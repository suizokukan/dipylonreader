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

    ❏Dipylon❏ : pos/posintext/vectorposintextranges.cpp

    See vectorposintextranges.h for the documentation

*******************************************************************************/

#include "pos/posintext/vectorposintextranges.h"

/*______________________________________________________________________________

        VectorPosInTextRanges::clear()
______________________________________________________________________________*/
void VectorPosInTextRanges::clear(void) {
  this->vposintextranges.clear();
}

/*______________________________________________________________________________

        VectorPosInTextRanges::sort()
______________________________________________________________________________*/
void VectorPosInTextRanges::sort(void) {

  std::sort( this->vposintextranges.begin(),
             this->vposintextranges.end(),
             VectorPosInTextRangesCMP(this) );
}

/*______________________________________________________________________________

        VectorPosInTextRanges::repr : return a QString representation of this.
______________________________________________________________________________*/
QString VectorPosInTextRanges::repr(void) const {

  QString res = QString("");

  // i is an iterator over PosInTextRanges objects :
  for(auto &i : this->vposintextranges) {
    res += i.repr();
    res += this->MAIN_SEPARATOR;
  }

  // removing the last MAIN_SEPARATOR character :
  res.chop(1);

  return res;
}

/*______________________________________________________________________________

        VectorPosInTextRanges::toPosInTextRanges

        Return a unique PosInTextRanges agglomerating all the PosInTextRanges
        objects stored in 'this'.
______________________________________________________________________________*/
PosInTextRanges VectorPosInTextRanges::toPosInTextRanges(void) const {
  PosInTextRanges res;

  for (auto &posintextranges : this->vposintextranges) {
    for (auto &vpairofposintext: posintextranges) {
      res.vec.push_back( vpairofposintext );
    }
  }

  res.checks();

  return res;
}
