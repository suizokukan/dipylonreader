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

    ❏Dipylon❏ : pos/posintext2posinaudio.h

    PosInText2PosInAudio class.

    HOW TO USE :

    PosInText2PosInAudio text2audio = {
        { {{ {1,2}, {3,4} },},  {1500, 1598} },
        { {{ {5,6}, {9,12} },},  {1750, 1790} },
      };
    qDebug() << text2audio[{{ {1,2}, {3,4} },}].first << text2audio[{{ {1,2}, {3,4} },}].second;
    qDebug() << text2audio.contains(6).to_str();

*******************************************************************************/

#ifndef POSINTEXT2POSINAUDIO_H
#define POSINTEXT2POSINAUDIO_H

#include "pos/posintext/posintextranges.h"
#include "pos/posintext/vectorposintextranges.h"
#include "pos/posinaudio/posinaudio.h"

#include <unordered_map>

/*______________________________________________________________________________

  Structure used to easily initialize PosInText2PosInAudio objects. E.g. :

      PosInText2PosInAudio text2audio = {
        { {{ {1,2}, {3,4} },},  {1500, 1598} },
      };
________________________________________________________________________________*/
struct PosInTextAndAudio
{
  VPairOfPosInText integers_text;
  PairOfPosInAudio integers_audio;
};

/*______________________________________________________________________________

  PosInText2PosInAudio class : basically, a map PosInTextRanges -> PairOfPosInAudio

________________________________________________________________________________*/
class PosInText2PosInAudio {

  friend class PosInAudio2PosInText;

 private:

  std::unordered_map<PosInTextRanges, PairOfPosInAudio, PosInTextRangesHasher> map;
  int                   _internal_state;
  bool                  _well_initialized;

  void                  checks(void);

 public:

                        PosInText2PosInAudio(void);
                        PosInText2PosInAudio(const PosInText2PosInAudio&);
                        PosInText2PosInAudio(std::initializer_list< PosInTextAndAudio >);
                        ~PosInText2PosInAudio(void);

  PairOfPosInAudio&     operator[]( VPairOfPosInText key );
  PosInText2PosInAudio& operator=(const PosInText2PosInAudio&);

  size_t                size(void) const;
  int                   internal_state(void) const;
  PosInTextRanges       contains(PosInText) const;
  VectorPosInTextRanges contains(PosInText, PosInText) const;
  bool                  well_initialized(void) const;

  // constants used to define the internal_state attribute :
  const int             INTERNALSTATE_OK = 0;
  const int             INTERNALSTATE_BADPOSINTEXTRANGES = 1;
};

inline PosInText2PosInAudio::PosInText2PosInAudio( void ) {
  this->_well_initialized = true;
  this->_internal_state = INTERNALSTATE_OK;
}

inline PosInText2PosInAudio::PosInText2PosInAudio( const PosInText2PosInAudio& other )  : \
                  map(other.map), \
                  _internal_state(other._internal_state), \
                  _well_initialized(other._well_initialized)
{}

inline PosInText2PosInAudio::PosInText2PosInAudio( std::initializer_list< PosInTextAndAudio > values)
{
  this->_well_initialized = true;
  this->_internal_state = INTERNALSTATE_OK;

  // i : iterator over this->values :
  for(auto &i : values) {

    this->map.insert( std::pair<PosInTextRanges, PairOfPosInAudio>( PosInTextRanges(i.integers_text),
                                                                                    i.integers_audio)
                    );
  }

  // is everything ok ?
  this->checks();
}

inline PosInText2PosInAudio::~PosInText2PosInAudio( void )
{}

inline PosInText2PosInAudio& PosInText2PosInAudio::operator=(const PosInText2PosInAudio& other) {

  if( this != &other) {
    this->map = other.map;
    this->_well_initialized = other._well_initialized;
    this->_internal_state = other._internal_state;
  }
  return *this;
}

inline PairOfPosInAudio& PosInText2PosInAudio::operator[]( VPairOfPosInText key) {
  return this->map[key];
}

inline int PosInText2PosInAudio::internal_state(void) const {
  return this->_internal_state;
}

inline size_t PosInText2PosInAudio::size(void) const {
  return this->map.size();
}

inline bool PosInText2PosInAudio::well_initialized(void) const {
  return this->_well_initialized;
}

#endif
