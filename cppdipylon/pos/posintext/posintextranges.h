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

    ❏Dipylon❏ : pos/posintext/posintextranges.h

    ⇨ Use PosInTextRanges objects to store a list of (PosInText)integers.
      A PosInTextRanges object can be initialized from a QString (see POSINTEXTRANGES_STR infra).
      After beeing initialized, check the (bool)well_initialized attribute.

    ⇨ about the implementation : std::vector<std::pair<int,int> > has not been
      derived to get the PosInTextRanges class. Deriving std containers isn't a good
      idea since these classes have no virtual destructor, hence no real
      polymorphic abilities.
      E.g. see discussion here : http://stackoverflow.com/questions/4353203

    ⇨ about the implementation : no virtual destructor has been added : PosInTextRanges
      objects can't be safely used to create subclasses.
      E.g. see discussion here : http://stackoverflow.com/questions/461203

    ⇨ overlapping is forbidden : "0-1+1-2" is ok, not "0-1+0-2", not "46-49+48-52"

    ⇨ POSINTEXTRANGES_STR format : "45-97", "45-97+123-136+999-1001", ...
        o no spaces allowed
        o overlapping is forbidden (vide  supra)
        o MAIN_SEPARATOR, SECONDARY_SEPARATOR : only one character.
        o at least one range must be defined (no empty string)
        o x0 must be < x1 (no "45-22", no "45-45")

*******************************************************************************/

#ifndef CPPDIPYLON_POS_POSINTEXT_POSINTEXTRANGES_H_
#define CPPDIPYLON_POS_POSINTEXT_POSINTEXTRANGES_H_

#include <QString>
#include <QStringList>

#include <algorithm>
#include <utility>
#include <vector>

#include "pos/posintext/posintext.h"
#include "misc/hash.h"

/*______________________________________________________________________________

  PosInTextRanges class

  wrapper around "vec", a vector of pair of <PosInText, PosInText>
________________________________________________________________________________*/
class PosInTextRanges {
    friend class PosInTextRangesHasher;
    friend class PosInText2Str;
    friend class PosInText2PosInAudio;

 public:
                     PosInTextRanges(void);
                     PosInTextRanges(const PosInTextRanges&);
                     PosInTextRanges(const QString&);
                     PosInTextRanges(std::initializer_list< std::pair<PosInText, PosInText> >);
                     PosInTextRanges(std::vector< std::pair<PosInText, PosInText> >);
                     ~PosInTextRanges(void);
                     PosInTextRanges& operator=(const PosInTextRanges&);
  bool               operator==(const PosInTextRanges& other) const;
  bool               operator!=(const PosInTextRanges& other) const;

  VPairOfPosInTextCI begin(void);
  bool               contains(PosInText) const;
  bool               contains(PosInText, PosInText) const;
  VPairOfPosInTextCI end(void);
  std::size_t        get_hash(void);
  int                internal_state(void) const;
  PosInText          max(void) const;
  PosInText          min(void) const;
  size_t             size(void) const;
  QString            repr(void) const;
  bool               well_initialized(void) const;

  /*
     INTERNALSTATE

     constants used to define the internal_state attribute.

     o OK
     o EMPTY_STRING_FOR_NUMBER : a string with a number was expected but the
                                 string is empty. ("" instead of "12")
     o NO_MAIN_SEPARATOR : missing main separator in a string. (e.g. "9-3 11-12" instead of "9-3+11-12")
     o PROBLEM_WITH_SECOND_SEPARATOR : missing secondary separator in a string. (e.g. "11 12"
                                       instead of "11-12") or more than one secondary separator.
     o X0X1 : x0 > x1
     o EMPTY : empty string given to initialize the object.
     o OVERLAPPING : e.g. "100-150+125-175"
  */
  enum INTERNALSTATE : int {
    OK = 0,
    EMPTY_STRING_FOR_NUMBER = -1,
    NO_MAIN_SEPARATOR = -2,
    PROBLEM_WITH_SECOND_SEPARATOR = -3,
    X0X1 = -4,
    EMPTY = -5,
    OVERLAPPING = -6,
  };

 private:
  // for more details, see the POSINTEXTRANGES_STR format :
  constexpr static const char* MAIN_SEPARATOR = "+";
  constexpr static const char* SECONDARY_SEPARATOR = "-";

  VPairOfPosInText   vec;
  int                _internal_state;
  bool               _well_initialized;

  void               checks(void);
};

inline PosInTextRanges::PosInTextRanges(void) : \
                  vec(VPairOfPosInText()), \
                  _internal_state(this->INTERNALSTATE::EMPTY),     \
                  _well_initialized(false)
{}

inline PosInTextRanges::PosInTextRanges(const PosInTextRanges& other)  : \
                  vec(other.vec), \
                  _internal_state(other._internal_state), \
                  _well_initialized(other._well_initialized)
{}

inline PosInTextRanges::PosInTextRanges(std::initializer_list<std::pair<PosInText, PosInText> > values) : \
vec(values) {
  this->_internal_state = this->INTERNALSTATE::OK;

  // error : if "values" is empty, the initialisation can't be correct :
  this->_well_initialized = (values.size() > 0);

  // shall we go further ?
  if (this->_well_initialized == false) {
    // ... no.
    this->_internal_state = this->INTERNALSTATE::EMPTY;
    return;
  }

  // last checks :
  this->checks();
}

inline PosInTextRanges::PosInTextRanges(std::vector< std::pair<PosInText, PosInText> > values) : \
vec(values) {
  this->_internal_state = this->INTERNALSTATE::OK;

  // error : if values is empty, the initialisation can't be correct :
  this->_well_initialized = (values.size() > 0);

  // shall we go further ?
  if (this->_well_initialized == false) {
    // ... no.
    this->_internal_state = this->INTERNALSTATE::EMPTY;
    return;
  }

  // last checks :
  this->checks();
}

inline PosInTextRanges::~PosInTextRanges(void) {}

inline PosInTextRanges& PosInTextRanges::operator=(const PosInTextRanges& other) {
  if (this != &other) {
    this->vec = other.vec;
    this->_internal_state = other._internal_state;
    this->_well_initialized = other._well_initialized;
  }
  return *this;
}

inline bool PosInTextRanges::operator==(const PosInTextRanges& other) const {
  return (this->_well_initialized == other._well_initialized) && (this->vec == other.vec);
}

inline bool PosInTextRanges::operator!=(const PosInTextRanges& other) const {
  return !(this->operator==(other));
}

inline VPairOfPosInTextCI PosInTextRanges::begin(void) {
  return this->vec.begin();
}

inline VPairOfPosInTextCI PosInTextRanges::end(void) {
  return this->vec.end();
}

inline std::size_t PosInTextRanges::get_hash(void) {
  std::size_t hash = 0;

  for (auto &i : vec) {
    hash_combine(hash, i.first);
    hash_combine(hash, i.second);
  }
  return hash;
}

inline int PosInTextRanges::internal_state(void) const {
  return this->_internal_state;
}

inline size_t PosInTextRanges::size(void) const { return this->vec.size(); }

inline bool PosInTextRanges::well_initialized(void) const {
  return this->_well_initialized;
}

/*______________________________________________________________________________

  PosInTextRangesHasher
________________________________________________________________________________*/
struct PosInTextRangesHasher {
  std::size_t operator()(const PosInTextRanges& k) const;
};

#endif  // CPPDIPYLON_POS_POSINTEXT_POSINTEXTRANGES_H_
