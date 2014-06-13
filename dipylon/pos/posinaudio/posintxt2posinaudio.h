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

    ❏Dipylon❏ : posintxt2posinaudio.h

*******************************************************************************/

#ifndef POSINTXT2POSINAUDIO_H
#define POSINTXT2POSINAUDIO_H

#include "posintxt/posranges.h"

#include <unordered_map>

/*______________________________________________________________________________

  Structure used to easily initialize Pos2Str objects. E.g. :

      Pos2Str pos2str = {
        { {{ {1,2}, {3,4} },}, "example1"},
        { {{ {1,2}, {3,5} },}, "example2"},
        { {{ {1,2}, {3,8} },}, "example3"},
      };
________________________________________________________________________________*/
struct PosInTxtIntAndAudioInt
{
  VPairOfPosInText integers1;
  VPairOfPosInAudio integers2;
};

/*______________________________________________________________________________

  Pos2Str class : basically, a map PosRanges -> VPairOfPosInAudio

________________________________________________________________________________*/
class PosInTxt2PosInAudio {

 private:

  std::unordered_map<PosRanges, VPairOfPosInAudio, PosRangesHasher> map;
  int  _internal_state;
  bool _well_initialized;

  void            checks(void);

 public:

                  PosInTxt2PosInAudio(void);
                  PosInTxt2PosInAudio(const PosInTxt2PosInAudio&);
                  PosInTxt2PosInAudio(std::initializer_list< PosInTxtIntAndAudioInt >);
                  ~PosInTxt2PosInAudio(void);

  QString&        operator[]( VPairOfPosInText key );
  PosInTxt2PosInAudio&        operator=(const PosInTxt2PosInAudio&);

  size_t          size(void) const;
  int             internal_state(void) const;
  PosRanges       contains(PosInText) const;
  VectorPosRanges contains(PosInText, PosInText) const;
  bool            well_initialized(void) const;

  // constants used to define the internal_state attribute :
  const int INTERNALSTATE_OK = 0;
  const int INTERNALSTATE_BADPOSRANGES = 1;
};

inline PosInTxt2PosInAudio::PosInTxt2PosInAudio( void ) {
  this->_well_initialized = true;
  this->_internal_state = INTERNALSTATE_OK;
}

inline PosInTxt2PosInAudio::PosInTxt2PosInAudio( const PosInTxt2PosInAudio& other )  : \
                  map(other.map), \
                  _internal_state(other._internal_state), \
                  _well_initialized(other._well_initialized)
{}

inline PosInTxt2PosInAudio::PosInTxt2PosInAudio( std::initializer_list< PosInTxtIntAndAudioInt > values)
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

inline PosInTxt2PosInAudio::~PosInTxt2PosInAudio( void ) 
{}

inline PosInTxt2PosInAudio& PosInTxt2PosInAudio::operator=(const PosInTxt2PosInAudio& other) {

  if( this != &other) {
    this->map = other.map;
    this->_well_initialized = other._well_initialized;
    this->_internal_state = other._internal_state;
  }
  return *this;
}

inline QString& PosInTxt2PosInAudio::operator[]( VPairOfPosInText key) {
  return this->map[key];
}

inline int PosInTxt2PosInAudio::internal_state(void) const {
  return this->_internal_state;
}

inline size_t PosInTxt2PosInAudio::size(void) const {
  return this->map.size();
}

inline bool PosInTxt2PosInAudio::well_initialized(void) const {
  return this->_well_initialized;
}

#endif
