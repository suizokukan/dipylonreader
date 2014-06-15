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

    ❏Dipylon❏ : pos/posintext/posintext2str.h

    See posintext2str.h for the documentation

*******************************************************************************/

#include "pos/posintext/posintext2str.h"

/*______________________________________________________________________________

        PosInText2Str::checks() : do some tests and if something's wrong,
                            modify _well_initialized and _internal_state .

        tests:

            o are the PosInTextRanges objects well initialized ?
                if not, INTERNALSTATE_BADPOSINTEXTRANGES

______________________________________________________________________________*/
void PosInText2Str::checks(void) {
  /*
    are the PosInTextRanges objects ok ?
  */
  // i is an iterator over a pair<PosInTextRanges, QString> :
  for(auto &i : this->map)
  {
    // i.irst is a PosInTextRanges object.
    if( i.first._well_initialized == false ) {
      this->_well_initialized = false;
      this->_internal_state = INTERNALSTATE_BADPOSINTEXTRANGES;
      return;
    }
  }
}

/*______________________________________________________________________________

        PosInText2Str::contains(PosInText x0)

       search the first (PosInTextRanges)key in" this" that matches this->key.contains(x0)

       This function returns a PosInTextRanges. The result is an
       empty PosInTextRanges if indexes in "this" do not contain "x0".

_____________________________________________________________________________*/
PosInTextRanges PosInText2Str::contains(PosInText x0) const
{
  // i is an iterator over a pair<PosInTextRanges, QString> :
  for(auto &i : this->map) {

    // i->first is a PosInTextRanges object.
    if( i.first.contains(x0) == true ) {
      // ok, the searched PosInTextRanges has been found and can be returned :
      return i.first;
    }
  }

  // no result : the function returns an empty vector.
  return PosInTextRanges();
}

/*______________________________________________________________________________

        PosInText2Str::contains(PosInText x0, x1) : search the first (PosInTextRanges)key in this
                                             that matches this->key.contains(x0, x1)

       This function returns a vector of PosInTextRanges. The result is an empty
       vector if this do not contain "x0...x1"

_____________________________________________________________________________*/
VectorPosInTextRanges PosInText2Str::contains(PosInText x0, PosInText x1) const
{
  std::vector<PosInTextRanges> res;

  // i is an iterator over a pair<PosInTextRanges, QString> :
  for(auto &i : this->map) {
    // i->first is a PosInTextRanges object.
    if( i.first.contains(x0, x1) == true ) {
      // ok, the searched PosInTextRanges has been found :
      res.push_back( i.first );
    }
  }

  return res;
}
