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

    A PosInText2Str object is a map linking (key)PosInTextRanges to (value)QString.

*******************************************************************************/

#ifndef POSINTEXT2STR_H
#define POSINTEXT2STR_H

#include "pos/posintext/posintext.h"
#include "pos/posintext/posintextranges.h"
#include "pos/posintext/vectorposintextranges.h"

#include <unordered_map>

#include <QString>

/*______________________________________________________________________________

  Structure used to easily initialize PosInText2Str objects. E.g. :

      PosInText2Str posintext2str = {
        { {{ {1,2}, {3,4} },}, "example1"},
        { {{ {1,2}, {3,5} },}, "example2"},
        { {{ {1,2}, {3,8} },}, "example3"},
      };
________________________________________________________________________________*/
struct IntegersAndAString
{
  VPairOfPosInText integers;
  QString string;
};

/*______________________________________________________________________________

  PosInText2Str class : basically, a map PosInTextRanges -> QString .

________________________________________________________________________________*/
class PosInText2Str {

 private:

  std::unordered_map<PosInTextRanges, QString, PosInTextRangesHasher> map;
  int  _internal_state;
  bool _well_initialized;

  void            checks(void);

 public:

                         PosInText2Str(void);
                         PosInText2Str(const PosInText2Str&);
                         PosInText2Str(std::initializer_list< IntegersAndAString >);
                        ~PosInText2Str(void);

  QString&              operator[]( PosInTextRanges key );
  const QString &       operator[]( const PosInTextRanges key ) const;
  PosInText2Str&        operator=(const PosInText2Str&);

  size_t                size(void) const;
  int                   internal_state(void) const;
  PosInTextRanges       contains(PosInText) const;
  VectorPosInTextRanges contains(PosInText, PosInText) const;
  bool                  well_initialized(void) const;

  /*
     INTERNALSTATE

     constants used to define the internal_state attribute.

     o OK
     o BAD_POS_IN_TEXTRANGES : a PosInTextRanges object isn't correctly initialized.
  */
  enum INTERNALSTATE : int {
    OK = 0,
    BAD_POS_IN_TEXTRANGES = -1,
  };
};

inline PosInText2Str::PosInText2Str( void ) {
  this->_well_initialized = true;
  this->_internal_state = this->INTERNALSTATE::OK;
}

inline PosInText2Str::PosInText2Str( const PosInText2Str& other )  : \
                  map(other.map), \
                  _internal_state(other._internal_state), \
                  _well_initialized(other._well_initialized)
{}

inline PosInText2Str::PosInText2Str( std::initializer_list< IntegersAndAString > values)
{
  this->_well_initialized = true;
  this->_internal_state = this->INTERNALSTATE::OK;

  // i : iterator over this->values :
  for(auto &i : values) {

    this->map.insert( std::pair<PosInTextRanges, QString>( PosInTextRanges(i.integers),
                                                                           i.string)
                    );
  }

  // is everything ok ?
  this->checks();
}

inline PosInText2Str::~PosInText2Str( void )
{}

inline PosInText2Str& PosInText2Str::operator=(const PosInText2Str& other) {

  if( this != &other) {
    this->map = other.map;
    this->_well_initialized = other._well_initialized;
    this->_internal_state = other._internal_state;
  }
  return *this;
}

inline QString& PosInText2Str::operator[]( PosInTextRanges key) {
  return this->map[key];
}
inline const QString& PosInText2Str::operator[]( const PosInTextRanges key ) const {
  return this->map.at(key);
}

inline int PosInText2Str::internal_state(void) const {
  return this->_internal_state;
}

inline size_t PosInText2Str::size(void) const {
  return this->map.size();
}

inline bool PosInText2Str::well_initialized(void) const {
  return this->_well_initialized;
}

#endif
