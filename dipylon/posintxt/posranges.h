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

    ❏Dipylon❏ : posintxt/posranges.h

    ⇨ Use PosRanges objects to store a list of (TextPos)integers.
      A PosRanges object can be initialized from a QString (see POSRANGES_STR infra).
      After beeing initialized, check the (bool)well_initialized attribute.

    ⇨ about the implementation : std::vector<std::pair<int,int> > has not been
      derived to get the PosRanges class. Deriving std containers isn't a good
      idea since these classes have no virtual destructor, hence no real
      polymorphic abilities.
      E.g. see discussion here : http://stackoverflow.com/questions/4353203

    ⇨ about the implementation : no virtual destructor has been added : PosRanges
      objects can't be safely used to create subclasses.
      E.g. see discussion here : http://stackoverflow.com/questions/461203

    ⇨ overlapping is forbidden : "0-1+1-2" is ok, not "0-1+0-2", not "46-49+48-52"

    ⇨ POSRANGES_STR format : "45-97", "45-97+123-136+999-1001", ...
        no spaces allowed 
        overlapping is forbidden (vide  supra) 
        MAIN_SEPARATOR, SECONDARY_SEPARATOR : only one character.
        at least one gap must be defined (no empty string)
        x0 must be < x1 (no "45-22", no "45-45")

*******************************************************************************/

#ifndef POSRANGES_H
#define POSRANGES_H

#include "posintxt/posintxt.h"
#include "misc/hash.h"

#include <QString>
#include <QStringList>

/*______________________________________________________________________________

  PosRanges class

  wrapper around "vec", a vector of pair of <PosInText, PosInText>
________________________________________________________________________________*/
class PosRanges {

 friend class PosRangesHasher;

 public:

          PosRanges(void);
          PosRanges(const PosRanges&);
          PosRanges(const QString&);
          ~PosRanges(void);
          PosRanges& operator=(const PosRanges&);
  bool    operator==(const PosRanges& other) const;
  bool    operator!=(const PosRanges& other) const;

  bool    contains(PosInText) const;
  bool    contains(PosInText, PosInText) const;
  size_t  size(void) const;
  QString to_str(void) const;

  // constants used to define the internal_state attribute :
  const int        INTERNALSTATE_OK = 0;
  const int        INTERNALSTATE_NOMAINSEP = 1;
  const int        INTERNALSTATE_SECONDSEP = 2;
  const int        INTERNALSTATE_X0X1 = 3;
  const int        INTERNALSTATE_EMPTY = 4;
  const int        INTERNALSTATE_OVERLAPPING = 5;

 private:

  // for more details, see the POSRANGES_STR format :
  const QString    MAIN_SEPARATOR = "+";
  const QString    SECONDARY_SEPARATOR = "-";

  VPairOfPosInText vec;
  int              _internal_state;
  bool             _well_initialized;

  void             checks(void);
};

inline PosRanges::PosRanges(void) : \
                  vec(VPairOfPosInText()), \
                  _internal_state(this->INTERNALSTATE_EMPTY), \
                  _well_initialized(false)
{}

inline PosRanges::PosRanges( const PosRanges& other )  : \
                  vec(other.vec), \
                  _internal_state(other._internal_state), \
                  _well_initialized(other._well_initialized)
{}

inline PosRanges::~PosRanges(void) {}

inline PosRanges& PosRanges::operator=(const PosRanges& other) {

  if( this != &other) {
    this->vec = other.vec;
    this->_internal_state = other._internal_state;
    this->_well_initialized = other._well_initialized;
  }
  return *this;
}

inline size_t PosRanges::size(void) const { return this->vec.size(); }

inline bool PosRanges::operator==(const PosRanges& other) const {
  return (this->_well_initialized == other._well_initialized) && (this->vec == other.vec); 
}

inline bool PosRanges::operator!=(const PosRanges& other) const {
  return !(this->operator==(other));
}

/*______________________________________________________________________________

  PosRangesHasher
________________________________________________________________________________*/
struct PosRangesHasher {
  std::size_t operator()(const PosRanges& k) const;
};

#endif
