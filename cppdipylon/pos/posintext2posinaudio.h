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

    ❏DipylonReader❏ : pos/posintext2posinaudio.h

    PosInText2PosInAudio class.

    HOW TO USE :

    PosInText2PosInAudio text2audio = {
        { {{ {1,2}, {3,4} },},  {1500, 1598} },
        { {{ {5,6}, {9,12} },},  {1750, 1790} },
      };
    qDebug() << text2audio[{{ {1,2}, {3,4} },}].first << text2audio[{{ {1,2}, {3,4} },}].second;
    qDebug() << text2audio.contains(6).repr();

*******************************************************************************/

#ifndef CPPDIPYLON_POS_POSINTEXT2POSINAUDIO_H_
#define CPPDIPYLON_POS_POSINTEXT2POSINAUDIO_H_

#include <utility>
#include <map>

#include "pos/posintext/posintextranges.h"
#include "pos/posintext/vectorposintextranges.h"
#include "pos/posinaudio/posinaudio.h"

/* type of the map used by the PosInText2PosInAudio class :

   PosInTextRanges -> PairOfPosInAudio
*/
typedef std::map<PosInTextRanges, PairOfPosInAudio> MAP_Text2Audio;
typedef MAP_Text2Audio::const_iterator MAP_Text2AudioCI;

/*______________________________________________________________________________

  Structure used to easily initialize PosInText2PosInAudio objects. E.g. :

      PosInText2PosInAudio text2audio = {
        { {{ {1,2}, {3,4} },},  {1500, 1598} },
      };
________________________________________________________________________________*/
struct PosInTextAndAudio {
  VPairOfPosInText integers_text;
  PairOfPosInAudio integers_audio;
};

/*______________________________________________________________________________

  PosInText2PosInAudio class : basically, a map PosInTextRanges -> PairOfPosInAudio

________________________________________________________________________________*/
class PosInText2PosInAudio {
  friend class PosInAudio2PosInText;

 private:
  MAP_Text2Audio          map;
  int                     _internal_state;
  bool                    _well_initialized;

  void                    checks(void);

 public:
                          PosInText2PosInAudio(void);
                          PosInText2PosInAudio(const PosInText2PosInAudio&);
                          PosInText2PosInAudio(std::initializer_list< PosInTextAndAudio >);
                          ~PosInText2PosInAudio(void);

  PairOfPosInAudio&       operator[](PosInTextRanges key);
  const PairOfPosInAudio& operator[](const PosInTextRanges key) const;
  PosInText2PosInAudio&   operator=(const PosInText2PosInAudio&);

  MAP_Text2AudioCI        begin(void) const;
  PosInTextRanges         contains(PosInText x0) const;
  VectorPosInTextRanges   contains(PosInText x0, PosInText x1) const;
  void                    clear(void);
  MAP_Text2AudioCI        end(void) const;
  int                     internal_state(void) const;
  size_t                  size(void) const;
  bool                    well_initialized(void) const;

  /*
     INTERNALSTATE

     constants used to define the internal_state attribute.

     o OK
     o BAD_POS_IN_TEXTRANGES : a PosInTextRanges object isn't correctly initialized.
     o BAD_POS_IN_AUDIO_X0X1 : a pair of PosInAudio <x0, x1> has x0 > x1.
  */
  enum INTERNALSTATE : int {
    OK = 0,
    BAD_POS_IN_TEXTRANGES = -1,
    BAD_POS_IN_AUDIO_X0X1 = -2,
    };
};

inline PosInText2PosInAudio::PosInText2PosInAudio(void) {
  this->_well_initialized = true;
  this->_internal_state = this->INTERNALSTATE::OK;
}

inline PosInText2PosInAudio::PosInText2PosInAudio(const PosInText2PosInAudio& other)  : \
                  map(other.map), \
                  _internal_state(other._internal_state), \
                  _well_initialized(other._well_initialized)
{}

inline PosInText2PosInAudio::PosInText2PosInAudio(std::initializer_list< PosInTextAndAudio > values) {
  this->_well_initialized = true;
  this->_internal_state = this->INTERNALSTATE::OK;

  // i : iterator over this->values :
  for (auto &i : values) {
    this->map.insert(std::pair<PosInTextRanges, PairOfPosInAudio>(PosInTextRanges(i.integers_text),
                                                                                  i.integers_audio) );
  }

  // is everything ok ?
  this->checks();
}

inline PosInText2PosInAudio::~PosInText2PosInAudio(void) {
}

inline PosInText2PosInAudio& PosInText2PosInAudio::operator=(const PosInText2PosInAudio& other) {
  if (this != &other) {
    this->map = other.map;
    this->_well_initialized = other._well_initialized;
    this->_internal_state = other._internal_state;
  }
  return *this;
}

inline PairOfPosInAudio& PosInText2PosInAudio::operator[](PosInTextRanges key) {
  return this->map[key];
}
inline const PairOfPosInAudio& PosInText2PosInAudio::operator[](const PosInTextRanges key) const {
  return this->map.at(key);
}

inline MAP_Text2AudioCI PosInText2PosInAudio::begin(void) const {
  return this->map.begin();
}

inline MAP_Text2AudioCI PosInText2PosInAudio::end(void) const {
  return this->map.end();
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

#endif  // CPPDIPYLON_POS_POSINTEXT2POSINAUDIO_H_
