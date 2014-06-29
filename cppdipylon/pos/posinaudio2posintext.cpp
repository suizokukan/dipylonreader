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

    ❏Dipylon❏ : pos/posinaudio2posintext.cpp

    See posinaudio2posintex.h for the documentation

*******************************************************************************/

#include "pos/posinaudio2posintext.h"

#include <QDebug>

/*______________________________________________________________________________

        PosInAudio2PosInText::PosInAudio2PosInText(const PosInText2PosInAudio)

        Fill "this" from a PosInText2PosInAudio object : "this" will be the
        reversed source.

_____________________________________________________________________________*/
PosInAudio2PosInText::PosInAudio2PosInText(const PosInText2PosInAudio& src) {

  if( src._well_initialized == false ) {
    this->_well_initialized = false;
    this->_internal_state = PosInAudio2PosInText::INTERNALSTATE::WRONG_INITIALIZATION;
  }

  this->map.clear();
  this->_well_initialized = true;
  this->_internal_state = PosInAudio2PosInText::INTERNALSTATE::OK;

  /*
    src_i : iterator over
        src_i.first : PosInTextRanges
        src_i.second : (PosInAudio, PosInAudio)

      qDebug() << typeid(src_i).name();
      qDebug() << src_i.first.to_str()  << src_i.second.first << "-" << src_i.second.second;
  */
  for(auto &src_i : src.map) {
    this->map[ src_i.second ] = src_i.first;
  }

}

/*______________________________________________________________________________

        PosInAudio2PosInText::PosInAudio2PosInText(const PosInText2PosInAudio)

        Fill "this" from a PosInText2PosInAudio object : "this" will be the
        reversed source.

_____________________________________________________________________________*/
void PosInAudio2PosInText::clear(void) {
  this->_well_initialized = false;
  this->_internal_state = INTERNALSTATE::NOT_YET_INITIALIZED;
  this->map.clear();
}


/*______________________________________________________________________________

        PosInAudio2PosInText::contains(PosInAudioRange pos)

       search the first PosInAudioRange in "this" so that
       pair.first <= pos <= pair.second

       This function returns a PosInTextRanges. The result is an
       empty PosInTextRanges if indexes in "this" do not contain "pos".

_____________________________________________________________________________*/
PosInTextRanges PosInAudio2PosInText::contains(PosInAudio pos) const
{
  PosInTextRanges res = PosInTextRanges();

  for(auto &i : this->map) {

    if( (i.first.pair.first <= pos) && (pos <= i.first.pair.second) ) {
      // ok, the searched PosInAudioRange has been found and can be returned :
      return i.second;
    }
  }

  // no result : the function returns an empty vector.
  return PosInTextRanges();
}
