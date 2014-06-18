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
        no spaces allowed
        overlapping is forbidden (vide  supra)
        MAIN_SEPARATOR, SECONDARY_SEPARATOR : only one character.
        at least one gap must be defined (no empty string)
        x0 must be < x1 (no "45-22", no "45-45")

*******************************************************************************/

#ifndef POSINTEXTRANGES_H
#define POSINTEXTRANGES_H

#include "pos/posintext/posintext.h"
#include "misc/hash.h"

#include <vector>

#include <QString>
#include <QStringList>

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
  int                internal_state(void) const;
  size_t             size(void) const;
  QString            to_str(void) const;
  bool               well_initialized(void) const;

  // constants used to define the internal_state attribute :
  static const int   INTERNALSTATE_OK = 0;
  static const int   INTERNALSTATE_NOMAINSEP = 1;
  static const int   INTERNALSTATE_SECONDSEP = 2;
  static const int   INTERNALSTATE_X0X1 = 3;
  static const int   INTERNALSTATE_EMPTY = 4;
  static const int   INTERNALSTATE_OVERLAPPING = 5;

 private:

  // for more details, see the POSINTEXTRANGES_STR format :
  const QString    MAIN_SEPARATOR = "+";
  const QString    SECONDARY_SEPARATOR = "-";

  VPairOfPosInText vec;
  int              _internal_state;
  bool             _well_initialized;

  void             checks(void);
};

inline PosInTextRanges::PosInTextRanges(void) : \
                  vec(VPairOfPosInText()), \
                  _internal_state(this->INTERNALSTATE_EMPTY), \
                  _well_initialized(false)
{}

inline PosInTextRanges::PosInTextRanges( const PosInTextRanges& other )  : \
                  vec(other.vec), \
                  _internal_state(other._internal_state), \
                  _well_initialized(other._well_initialized)
{}

inline PosInTextRanges::PosInTextRanges(std::initializer_list<std::pair<PosInText, PosInText> > values) : \
vec(values) {

  this->_internal_state = this->INTERNALSTATE_OK;

  // error : if "values" is empty, the initialisation can't be correct :
  this->_well_initialized = (values.size() > 0);

  // shall we go further ?
  if( this->_well_initialized == false ) {
    // ... no.
    this->_internal_state = this->INTERNALSTATE_EMPTY;
    return;
  }

  // last checks :
  this->checks();
}

inline PosInTextRanges::PosInTextRanges(std::vector< std::pair<PosInText, PosInText> > values) : \
vec(values) {

  this->_internal_state = this->INTERNALSTATE_OK;

  // error : if values is empty, the initialisation can't be correct :
  this->_well_initialized = (values.size() > 0);

  // shall we go further ?
  if( this->_well_initialized == false ) {
    // ... no.
    this->_internal_state = this->INTERNALSTATE_EMPTY;
    return;
  }

  // last checks :
  this->checks();
}

inline PosInTextRanges::~PosInTextRanges(void) {}

inline PosInTextRanges& PosInTextRanges::operator=(const PosInTextRanges& other) {

  if( this != &other) {
    this->vec = other.vec;
    this->_internal_state = other._internal_state;
    this->_well_initialized = other._well_initialized;
  }
  return *this;
}

inline size_t PosInTextRanges::size(void) const { return this->vec.size(); }

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

inline int PosInTextRanges::internal_state(void) const {
  return this->_internal_state;
}

inline bool PosInTextRanges::well_initialized(void) const {
  return this->_well_initialized;
}

/*______________________________________________________________________________

  PosInTextRangesHasher
________________________________________________________________________________*/
struct PosInTextRangesHasher {
  std::size_t operator()(const PosInTextRanges& k) const;
};

#endif
