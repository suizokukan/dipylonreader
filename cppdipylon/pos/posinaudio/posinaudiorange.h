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

    ❏Dipylon❏ : pos/posinaudio/posinaudiorange.h

    Wrapper around the PairOfPosInAudio type.

    ____________________________________________________________________________

    POSINAUDIORANGE_STR format :

     o "123-456", confer MAIN_SEPARATOR
     o "123-" : error, the number can't be an empty string.

*******************************************************************************/

#ifndef CPPDIPYLON_POS_POSINAUDIO_POSINAUDIORANGE_H_
#define CPPDIPYLON_POS_POSINAUDIO_POSINAUDIORANGE_H_

#include <QString>
#include <QStringList>

#include <utility>

#include "pos/posinaudio/posinaudio.h"
/*______________________________________________________________________________

  PosInAudioRange class

  wrapper around "pair", a PairOfPosInAudio object.
______________________________________________________________________________*/
class PosInAudioRange {
    friend class PosInText2PosInAudio;
    friend class PosInAudio2PosInText;

 public:
                     PosInAudioRange(void);
            explicit PosInAudioRange(const PosInAudioRange&);
            explicit PosInAudioRange(const QString&);
                     PosInAudioRange(PosInAudio, PosInAudio);
                     PosInAudioRange(std::pair<PosInAudio, PosInAudio>);
                     ~PosInAudioRange(void);
                     PosInAudioRange& operator=(const PosInAudioRange&);
  bool               operator==(const PosInAudioRange& other) const;
  bool               operator!=(const PosInAudioRange& other) const;

  PosInAudio         first(void) const;
  std::size_t        get_hash(void) const;
  int                internal_state(void) const;
  PosInAudio         second(void) const;
  QString            to_str(void) const;
  bool               well_initialized(void) const;

  /*
     INTERNALSTATE

     constants used to define the internal_state attribute.

     o OK
     o ILL_FORMED_SRC_STRING : problem with the number of MAIN_SEPARATOR.
                               see the POSINAUDIORANGE_STR defined above.
     o X0X1 : x0 > x1
     o EMPTY : empty string given to initialize the object.
  */
  enum INTERNALSTATE : int {
    OK = 0,
    ILL_FORMED_SRC_STRING = -1,
    X0X1 = -2,
    EMPTY = -3,
  };

 private:
  // for more details, see the POSINAUDIORANGE_STR format :
  constexpr static const char* MAIN_SEPARATOR = "-";

  PairOfPosInAudio   pair;
  int                _internal_state;
  bool               _well_initialized;

  void               checks(void);
};

inline PosInAudioRange::PosInAudioRange(void) : \
                  pair(PairOfPosInAudio()), \
                  _internal_state(this->INTERNALSTATE::EMPTY), \
                  _well_initialized(false) {
}

inline PosInAudioRange::PosInAudioRange(const PosInAudioRange& other)  : \
                  pair(other.pair), \
                  _internal_state(other._internal_state), \
                  _well_initialized(other._well_initialized) {
}

inline PosInAudioRange::PosInAudioRange(PosInAudio x0, PosInAudio x1) : \
pair(x0, x1) {
  this->_internal_state = this->INTERNALSTATE::OK;
  this->_well_initialized = true;

  // checks :
  this->checks();
}

inline PosInAudioRange::PosInAudioRange(std::pair<PosInAudio, PosInAudio> x0x1) : \
pair(x0x1.first, x0x1.second) {
  this->_internal_state = this->INTERNALSTATE::OK;
  this->_well_initialized = true;

  // checks :
  this->checks();
}

inline PosInAudioRange::~PosInAudioRange(void) {
}

inline PosInAudioRange& PosInAudioRange::operator=(const PosInAudioRange& other) {
  if (this != &other) {
    this->pair = other.pair;
    this->_internal_state = other._internal_state;
    this->_well_initialized = other._well_initialized;
  }
  return *this;
}

inline bool PosInAudioRange::operator==(const PosInAudioRange& other) const {
  return (this->_well_initialized == other._well_initialized) && (this->pair == other.pair);
}

inline bool PosInAudioRange::operator!=(const PosInAudioRange& other) const {
  return !(this->operator==(other));
}

inline PosInAudio PosInAudioRange::first(void) const {
  return this->pair.first;
}

/*
  I thought it would be a good idea not to choose the generic hash function (hash_combine)
  juste to hash two integers.

  o solutions like (a << 16) + b do not work since a size_t can be 16 bits
  o Cantor pairing function seems too slow : (a + b) * (a + b + 1) / 2 + a; where a, b >= 0
  o the following solution (Szudzik's function, http://szudzik.com/ElegantPairing.pdf) seems very good.
    see by example http://stackoverflow.com/questions/919612
*/
inline std::size_t PosInAudioRange::get_hash(void) const {
  std::size_t a = static_cast<std::size_t>(this->pair.first);
  std::size_t b = static_cast<std::size_t>(this->pair.second);
  return a >= b ? (a * a) + a + b : a + (b * b);
}

inline int PosInAudioRange::internal_state(void) const {
  return this->_internal_state;
}

inline PosInAudio PosInAudioRange::second(void) const {
  return this->pair.second;
}

inline bool PosInAudioRange::well_initialized(void) const {
  return this->_well_initialized;
}

/*______________________________________________________________________________

  PosInAudioRangeHasher
________________________________________________________________________________*/
struct PosInAudioRangeHasher {
  std::size_t operator()(const PosInAudioRange& k) const;
};

#endif  // CPPDIPYLON_POS_POSINAUDIO_POSINAUDIORANGE_H_
