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

    ❏Dipylon❏ : pos/posintext/posintextranges.cpp

    See posintextranges.h for the documentation.

*******************************************************************************/

#include "pos/posintext/posintextranges.h"

/*______________________________________________________________________________

        PosInTextRanges::PosInTextRanges : constructor from a QString.

        Initialize vec, (int)_internal_state and (bool)_well_initialized.

        If an error occurs, _well_initialized is set to false and
        _internal_state explains the error.
______________________________________________________________________________*/
PosInTextRanges::PosInTextRanges(const QString& src_qstring) {
  this->vec = VPairOfPosInText();
  this->_well_initialized = true;
  this->_internal_state = PosInTextRanges::INTERNALSTATE::OK;

  // error : if src_qstring is empty, the initialisation can't be correct :
  if( src_qstring.size() == 0 ) {
    this->_well_initialized = false;
    this->_internal_state = PosInTextRanges::INTERNALSTATE::EMPTY;
    return;
  }

  // let's initialize this vector from src_qstring :
  QStringList splitted_strings = src_qstring.split(this->MAIN_SEPARATOR);
  if( splitted_strings.length() == 0 ) {
    // error : ill-formed src_qstring (no MAIN_SEPARATOR)
    this->_well_initialized = false;
    this->_internal_state = PosInTextRanges::INTERNALSTATE::NO_MAIN_SEPARATOR;
    return;
  }

  for( auto &qstringlist_iterator : splitted_strings ) {
    QStringList x0x1 = qstringlist_iterator.split(this->SECONDARY_SEPARATOR);

    if( x0x1.length() != 2 ) {
       // error : ill-formed src_qstring :
       this->_well_initialized = false;
       this->_internal_state = PosInTextRanges::INTERNALSTATE::PROBLEM_WITH_SECOND_SEPARATOR;
       break;
    }
    else {
      // int(egers) become PosInText objects :

      QString x0_str = x0x1[0];
      QString x1_str = x0x1[1];

      if( (x0_str.length() == 0) || (x1_str.length() == 0) ) {
        this->_well_initialized = false;
        this->_internal_state = PosInTextRanges::INTERNALSTATE::EMPTY_STRING_FOR_NUMBER;
        break;
      }

      PosInText x0 = static_cast<PosInText>( x0_str.toInt() );
      PosInText x1 = static_cast<PosInText>( x1_str.toInt() );
      this->vec.push_back( std::make_pair(x0,x1) );
    }
  }

  // see POSINTEXTRANGES_STR format : at least one range must be defined.
  if( this->_well_initialized == true && this->vec.size() == 0 ) {
      this->_well_initialized = false;
      this->_internal_state = PosInTextRanges::INTERNALSTATE::EMPTY;
      return;
  }

  // last checks :
  this->checks();
}

/*______________________________________________________________________________

        PosInTextRanges::checks() : do some tests and modified _well_initialized and
                              _internal_state if something's wrong.

        tests :
            o if x0 >= x1 -> error, INTERNALSTATE::X0X1
            o if one range overlaps another one, error -> INTERNALSTATE::OVERLAPPING
______________________________________________________________________________*/
void PosInTextRanges::checks(void) {
  /*
        X0X1 test :
  */
  // i is a std::vector < std::pair<PosInText, PosInText> >
  for( auto &i : vec ) {
     if (i.first >= i.second) {
       this->_well_initialized = false;
       this->_internal_state = PosInTextRanges::INTERNALSTATE::X0X1;
       return;
     }
  }

  /*
         overlapping test :
  */
  // i, j are std::vector < std::pair<PosInText, PosInText> >
  for( auto &i : vec ) {
    for( auto &j : vec ) {
      if( i != j ) {
        if( ((i.first < j.first) && (j.first < i.second)) ||
            ((i.first < j.second) && (j.second < i.second)) ) {
          this->_well_initialized = false;
          this->_internal_state = PosInTextRanges::INTERNALSTATE::OVERLAPPING;
          return;
        }
      }
    }
  }
}

/*______________________________________________________________________________

        PosInTextRanges::contains() : return either true if (PosInText)x0 is inside
                                      a range of the object, either false.
______________________________________________________________________________*/
bool PosInTextRanges::contains(PosInText x0) const
{
  bool res = false;

  // i is a std::vector < std::pair<PosInText, PosInText> > iterator.
  for (auto &i : vec) {
    if( (i.first <= x0) && (x0 <= i.second) ) {
      res = true;
      break;
    }
  }

  return res;
}

/*______________________________________________________________________________

        PosInTextRanges::contains() : return either true if at least one index between
                                 (PosInText)x0 and (PosInText)x1 is inside one range
                                 of the object, either false.
______________________________________________________________________________*/
bool PosInTextRanges::contains(PosInText x0, PosInText x1) const
{
  bool res = false;

  // i is a std::vector < std::pair<PosInText, PosInText> > iterator.
  for (auto &i : vec) {
    if( ((i.first <= x0) && (x0 <= i.second)) ||
        ((i.first <= x1) && (x1 <= i.second)) ||
        ((i.first > x0) && (x1 > i.second))
        ) {
      res = true;
      break;
    }
  }

  return res;
}

/*______________________________________________________________________________

        PosInTextRanges::to_str() : return a QString representing the object
                                    according to the POSINTEXTRANGES_STR format
                                    (see posintextranges.h)
______________________________________________________________________________*/
QString PosInTextRanges::to_str(void) const {
  QString res("");

  // empty vector ? nothing to do.
  if( this->vec.empty() ) {
    return res;
  }

  // we go through the object with an iterator :
  // i is a std::vector < std::pair<PosInText, PosInText> > iterator
  for (auto &i : vec) {
      res += QString().number( i.first );
      res += this->SECONDARY_SEPARATOR;
      res += QString().number( i.second );
      res += this->MAIN_SEPARATOR;
    }

  // removing the last SECONDARY_SEPARATOR character :
  res.chop(1);

  return res;
}

/*##############################################################################

        PosInTextRangesHasher

 ##############################################################################*/

/*______________________________________________________________________________

        PosInTextRangesHasher::operator()

        from a David Schwartz idea (http://stackoverflow.com/questions/23859844)

______________________________________________________________________________*/
std::size_t PosInTextRangesHasher::operator()(const PosInTextRanges& k) const {

  std::size_t hash = 0;

  for (auto &i : k.vec) {
    hash_combine( hash, i.first);
    hash_combine( hash, i.second);
  }

  return hash;
}
