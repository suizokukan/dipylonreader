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

    ❏DipylonReader❏ : pos/posintext2posinaudio.cpp

    See posintext2posinaudio.h for the documentation

*******************************************************************************/

#include "pos/posintext2posinaudio.h"
#include <vector>

/*______________________________________________________________________________

        PosInText2PosInAudio::checks() : do some tests and if something's wrong,
                                         modify _well_initialized and _internal_state .

        tests:

            o are the PosInTextRanges objects well initialized ?
                if not, INTERNALSTATE::BAD_POS_IN_TEXTRANGES

            o are the <PosInAudio, PosInAudio> well ordered ?
                if not, INTERNALSTATE::BAD_POS_IN_AUDIO_X0X1

______________________________________________________________________________*/
void PosInText2PosInAudio::checks(void) {
  /*
    are the PosInTextRanges objects ok ?
  */
  for (auto &i : this->map) {
    // i.first is a PosInTextRanges object.
    if (i.first._well_initialized == false) {
      this->_well_initialized = false;
      this->_internal_state = INTERNALSTATE::BAD_POS_IN_TEXTRANGES;
      return;
    }
  }

  /*
    are the <PosInAudio, PosInAudio> well ordered ?
  */
  for (auto &i : this->map) {
    // i.second is a pair of PosInAudio object.
    if (i.second.first > i.second.second) {
      this->_well_initialized = false;
      this->_internal_state = INTERNALSTATE::BAD_POS_IN_AUDIO_X0X1;
      return;
    }
  }
}

/*______________________________________________________________________________

        PosInText2PosInAudio::clear()
_____________________________________________________________________________*/
void PosInText2PosInAudio::clear(void) {
  this->_well_initialized = true;
  this->_internal_state = OK;
  this->map.clear();
}

/*______________________________________________________________________________

        PosInText2PosInAudio::contains(PosInText x0)

       search the first (PosInTextRanges)key in "this" that matches this->key.contains(x0)

       This function returns a PosInTextRanges. The result is an
       empty PosInTextRanges if indexes in "this" do not contain "x0".

_____________________________________________________________________________*/
PosInTextRanges PosInText2PosInAudio::contains(PosInText x0) const {
  for (auto &i : this->map) {
    // i->first is a PosInTextRanges object.
    if (i.first.contains(x0) == true) {
      // ok, the searched PosInTextRanges has been found and can be returned :
      return i.first;
    }
  }

  // no result : the function returns an empty vector.
  return PosInTextRanges();
}

/*______________________________________________________________________________

        PosInText2PosInAudio::contains(PosInText x0, x1)

       search the first (PosInTextRanges)key in "this" that matches
       this->key.contains(x0, x1)

       This function returns a vector of PosInTextRanges. The result is an empty
       vector if this do not contain "x0...x1"

_____________________________________________________________________________*/
VectorPosInTextRanges PosInText2PosInAudio::contains(PosInText x0, PosInText x1) const {
  std::vector<PosInTextRanges> res;

  for (auto &i : this->map) {
    // i->first is a PosInTextRanges object.
    if (i.first.contains(x0, x1) == true) {
      // ok, the searched PosInTextRanges has been found :
      res.push_back(i.first);
    }
  }

  return res;
}
