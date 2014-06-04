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

    ❏Dipylon❏ : posintxt/pos2str.h

    A Pos2Str object is a map linking (key)PosRanges to (value)QString.

*******************************************************************************/

#ifndef POS2STR_H
#define POS2STR_H

#include "posintxt/posintxt.h"
#include "posintxt/posranges.h"
#include "posintxt/vectorposranges.h"

#include <unordered_map>

#include <QString>

/*______________________________________________________________________________

  Structure used to easily initialize Pos2Str objects. E.g. :

      Pos2Str pos2str = {
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

  Pos2Str class

________________________________________________________________________________*/
class Pos2Str {

 private:

  std::unordered_map<PosRanges, QString, PosRangesHasher> map;
  int  _internal_state;
  bool _well_initialized;

  void            checks(void);

 public:

                  Pos2Str(void);
                  Pos2Str(const Pos2Str&);
                  Pos2Str(std::initializer_list< IntegersAndAString >);
                  ~Pos2Str(void);

  QString&        operator[]( VPairOfPosInText key );
  Pos2Str&        operator=(const Pos2Str&);

  size_t          size(void) const;
  int             internal_state(void) const;
  PosRanges       contains(PosInText) const;
  VectorPosRanges contains(PosInText, PosInText) const;
  bool            well_initialized(void) const;

  // constants used to define the internal_state attribute :
  const int INTERNALSTATE_OK = 0;
  const int INTERNALSTATE_BADPOSRANGES = 1;
};

inline Pos2Str::Pos2Str( void ) {
  this->_well_initialized = true;
  this->_internal_state = INTERNALSTATE_OK;
}

inline Pos2Str::Pos2Str( const Pos2Str& other )  : \
                  map(other.map), \
                  _internal_state(other._internal_state), \
                  _well_initialized(other._well_initialized)
{}

inline Pos2Str::Pos2Str( std::initializer_list< IntegersAndAString > values)
{
  this->_well_initialized = true;
  this->_internal_state = INTERNALSTATE_OK;

  // i : iterator over this->values :
  for(auto &i : values) {

    this->map.insert( std::pair<PosRanges, QString>( PosRanges(i.integers), 
                                                               i.string)
                    );
  }

  // is everything ok ?
  this->checks();
}

inline Pos2Str::~Pos2Str( void ) 
{}

inline Pos2Str& Pos2Str::operator=(const Pos2Str& other) {

  if( this != &other) {
    this->map = other.map;
    this->_well_initialized = other._well_initialized;
    this->_internal_state = other._internal_state;
  }
  return *this;
}

QString& Pos2Str::operator[]( VPairOfPosInText key) {
  return this->map[key];
}

inline int Pos2Str::internal_state(void) const {
  return this->_internal_state;
}

size_t Pos2Str::size(void) const {
  return this->map.size();
}

bool Pos2Str::well_initialized(void) const {
  return this->_well_initialized;
}



#endif
