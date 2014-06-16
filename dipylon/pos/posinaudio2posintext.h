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

    ❏Dipylon❏ : pos/posinaudio2posintext.h

    PosInAudio2PostInText class.

    HOW TO USE :

    PosInText2PosInAudio text2audio = {
        { {{ {1,2}, {3,4} },},  {1500, 1598} },
        { {{ {5,6}, {9,12} },},  {1750, 1790} },
      };

    PosInText2PosInAudio& text2audio_ref = text2audio;
    PosInAudio2PosInText audio2text = PosInAudio2PosInText(text2audio_ref);

    qDebug() << audio2text.size();
    qDebug() << audio2text[{1500, 1598}].to_str();


*******************************************************************************/

#ifndef POSINAUDIO2POSINTEXT_H
#define POSINAUDIO2POSINTEXT_H

#include "pos/posinaudio/posinaudio.h"
#include "pos/posintext2posinaudio.h"

#include <unordered_map>

/*______________________________________________________________________________

  PosInAudio2PosInText class : basically, a map PairOfPosInAudio -> PosInTextRanges

  A PosInAudio2PosInText object can be initialized from a PosInText2PosInAudio
  object by reversing the keys and the values.

________________________________________________________________________________*/
class PosInAudio2PosInText {

 private:

  std::unordered_map<PairOfPosInAudio, PosInTextRanges, PairOfPosInAudioHasher> map;
  int                   _internal_state;
  bool                  _well_initialized;

 public:

                        PosInAudio2PosInText(void);
                        PosInAudio2PosInText(const PosInAudio2PosInText&);
                        PosInAudio2PosInText(const PosInText2PosInAudio&);
                        ~PosInAudio2PosInText(void);

  PosInTextRanges&       operator[]( PairOfPosInAudio key );
  const PosInTextRanges& operator[]( const PairOfPosInAudio key ) const;
  PosInAudio2PosInText&  operator=(const PosInAudio2PosInText&);

  size_t                size(void) const;
  int                   internal_state(void) const;
  PosInTextRanges       contains(PosInAudio) const;
  bool                  well_initialized(void) const;

  // constants used to define the internal_state attribute :
  const int             INTERNALSTATE_OK = 0;
  const int             INTERNALSTATE_WRONGINITIALIZATION = 1;
};

inline PosInAudio2PosInText::PosInAudio2PosInText( void ) {
  this->_well_initialized = true;
  this->_internal_state = INTERNALSTATE_OK;
}

inline PosInAudio2PosInText::PosInAudio2PosInText( const PosInAudio2PosInText& other )  : \
                  map(other.map), \
                  _internal_state(other._internal_state), \
                  _well_initialized(other._well_initialized)
{}

inline PosInAudio2PosInText::~PosInAudio2PosInText( void )
{}

inline PosInAudio2PosInText& PosInAudio2PosInText::operator=(const PosInAudio2PosInText& other) {

  if( this != &other) {
    this->map = other.map;
    this->_well_initialized = other._well_initialized;
    this->_internal_state = other._internal_state;
  }
  return *this;
}

inline PosInTextRanges& PosInAudio2PosInText::operator[]( PairOfPosInAudio key) {
  return this->map[key];
}
inline const PosInTextRanges& PosInAudio2PosInText::operator[]( const PairOfPosInAudio key ) const {
  return this->map.at(key);
}

inline int PosInAudio2PosInText::internal_state(void) const {
  return this->_internal_state;
}

inline size_t PosInAudio2PosInText::size(void) const {
  return this->map.size();
}

inline bool PosInAudio2PosInText::well_initialized(void) const {
  return this->_well_initialized;
}

#endif
