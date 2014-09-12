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

    ❏DipylonReader❏ : pos/posinaudio2posintext.h

    PosInAudio2PostInText class.

    HOW TO USE :

    PosInText2PosInAudio text2audio = {
        { {{ {1,2}, {3,4} },},  {1500, 1598} },
        { {{ {5,6}, {9,12} },},  {1750, 1790} },
      };

    PosInAudio2PosInText audio2text = PosInAudio2PosInText(text2audio);

    qDebug() << audio2text.size();
    qDebug() << audio2text[{1500, 1598}].repr();


*******************************************************************************/

#ifndef CPPDIPYLON_POS_POSINAUDIO2POSINTEXT_H_
#define CPPDIPYLON_POS_POSINAUDIO2POSINTEXT_H_

#include <unordered_map>

#include "pos/posinaudio/posinaudio.h"
#include "pos/posinaudio/posinaudiorange.h"
#include "pos/posintext2posinaudio.h"

/*______________________________________________________________________________

  PosInAudio2PosInText class : basically, a map PosInAudioRange -> PosInTextRanges

  A PosInAudio2PosInText object can be initialized from a PosInText2PosInAudio
  object by reversing the keys and the values.

________________________________________________________________________________*/
class PosInAudio2PosInText {
 private:
  std::unordered_map<PosInAudioRange, PosInTextRanges, PosInAudioRangeHasher> map;
  int                     _internal_state;
  bool                    _well_initialized;

 public:
                          PosInAudio2PosInText(void);
                 explicit PosInAudio2PosInText(const PosInAudio2PosInText&);
                 explicit PosInAudio2PosInText(const PosInText2PosInAudio&);      // "inverse" constructor
                          ~PosInAudio2PosInText(void);

  PosInTextRanges&        operator[](PosInAudioRange key);
  const PosInTextRanges&  operator[](const PosInAudioRange key) const;
  PosInAudio2PosInText&   operator=(const PosInAudio2PosInText&);

  void                    clear(void);
  PosInTextRanges         contains(PosInAudio) const;
  int                     internal_state(void) const;
  size_t                  size(void) const;
  bool                    well_initialized(void) const;

  /*
     INTERNALSTATE

     constants used to define the internal_state attribute.

     o OK
     o WRONG_INITIALIZATION : a source object used to initialize "this" wasn't
                              correctly initialized.
  */
  enum INTERNALSTATE : int {
    OK = 0,
    WRONG_INITIALIZATION = -2,
  };
};

inline PosInAudio2PosInText::PosInAudio2PosInText(void) {
  this->_well_initialized = true;
  this->_internal_state = this->INTERNALSTATE::OK;
}

inline PosInAudio2PosInText::PosInAudio2PosInText(const PosInAudio2PosInText& other)  : \
                  map(other.map), \
                  _internal_state(other._internal_state), \
                  _well_initialized(other._well_initialized)
{}

inline PosInAudio2PosInText::~PosInAudio2PosInText(void)
{}

inline PosInAudio2PosInText& PosInAudio2PosInText::operator=(const PosInAudio2PosInText& other) {
  if (this != &other) {
    this->map = other.map;
    this->_well_initialized = other._well_initialized;
    this->_internal_state = other._internal_state;
  }
  return *this;
}

inline PosInTextRanges& PosInAudio2PosInText::operator[](PosInAudioRange key) {
  return this->map[key.pair];
}

inline const PosInTextRanges& PosInAudio2PosInText::operator[](const PosInAudioRange key) const {
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

#endif  // CPPDIPYLON_POS_POSINAUDIO2POSINTEXT_H_
