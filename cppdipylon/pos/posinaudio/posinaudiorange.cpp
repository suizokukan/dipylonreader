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

    ❏Dipylon❏ : pos/posinaudio/posinaudiorange.cpp

    See posinaudiorange.h for the documentation.

*******************************************************************************/

#include "pos/posinaudio/posinaudiorange.h"

/*______________________________________________________________________________

        PosInAudioRange::PosInAudioRange : constructor from a QString.

        Initialize pair, (int)_internal_state and (bool)_well_initialized.

        If an error occurs, _well_initialized is set to false and
        _internal_state explains the error.
______________________________________________________________________________*/
PosInAudioRange::PosInAudioRange(const QString& src_qstring) {
  this->pair = PairOfPosInAudio();
  this->_well_initialized = true;
  this->_internal_state = PosInAudioRange::INTERNALSTATE::OK;

  // error : if src_qstring is empty, the initialisation can't be correct :
  if (src_qstring.size() == 0) {
    this->_well_initialized = false;
    this->_internal_state = PosInAudioRange::INTERNALSTATE::EMPTY;
    return;
  }

  // let's initialize this object from src_qstring :
  QStringList splitted_strings = src_qstring.split(this->MAIN_SEPARATOR);
  if (splitted_strings.length() != 2) {
    // error : ill-formed src_qstring (ill formed source string)
    this->_well_initialized = false;
    this->_internal_state = PosInAudioRange::INTERNALSTATE::ILL_FORMED_SRC_STRING;
    return;
  }

  QString x0 = splitted_strings[0];
  QString x1 = splitted_strings[1];

  // error : no empty number.
  if ( (x0.length() == 0) || (x1.length() == 0) ) {
    this->_well_initialized = false;
    this->_internal_state = PosInAudioRange::INTERNALSTATE::ILL_FORMED_SRC_STRING;
    return;
  }

  this->pair.first = x0.toInt();
  this->pair.second = x1.toInt();

  // last checks :
  this->checks();
}

/*______________________________________________________________________________

        PosInAudioRange::checks() : do some tests and modified _well_initialized
                                    and _internal_state if something's wrong.

        tests :
            o if x0 >= x1 -> error, INTERNALSTATE::X0X1
______________________________________________________________________________*/
void PosInAudioRange::checks(void) {
  /*
        X0X1 test :
  */
  if (this->pair.first >= this->pair.second) {
       this->_well_initialized = false;
       this->_internal_state = PosInAudioRange::INTERNALSTATE::X0X1;
  }
}

/*______________________________________________________________________________

        PosInAudioRange::to_str() : return a QString representing the object
                                    according to the POSINAUDIORANGE_STR format.
______________________________________________________________________________*/
QString PosInAudioRange::to_str(void) const {
  QString res("");

  res = QString().number(this->pair.first) + \
        this->MAIN_SEPARATOR + QString().number(this->pair.second);

  return res;
}

/*##############################################################################

        PosInAudioRangeHasher

 ##############################################################################*/

/*______________________________________________________________________________

        PosInAudioRangeHasher::operator()

        from a David Schwartz idea (http://stackoverflow.com/questions/23859844)

______________________________________________________________________________*/
std::size_t PosInAudioRangeHasher::operator()(const PosInAudioRange& k) const {
  return k.get_hash();
}
