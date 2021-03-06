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

    ❏DipylonReader❏ : pos/posintext/posintext2str.h

    A PosInText2Str object is a map linking (key)PosInTextRanges to (value)QString.

*******************************************************************************/

#ifndef CPPDIPYLON_POS_POSINTEXT_POSINTEXT2STR_H_
#define CPPDIPYLON_POS_POSINTEXT_POSINTEXT2STR_H_

#include <QString>

#include <map>
#include <utility>

#include "pos/posintext/posintext.h"
#include "pos/posintext/posintextranges.h"
#include "pos/posintext/vectorposintextranges.h"

/*______________________________________________________________________________

  Structure used to easily initialize PosInText2Str objects. E.g. :

      PosInText2Str posintext2str = {
        { {{ {1,2}, {3,4} },}, "example1"},
        { {{ {1,2}, {3,5} },}, "example2"},
        { {{ {1,2}, {3,8} },}, "example3"},
      };
________________________________________________________________________________*/
struct IntegersAndAString {
  VPairOfPosInText integers;
  QString str;
};

/*______________________________________________________________________________

  PosInText2Str class : basically, a map PosInTextRanges -> QString .

________________________________________________________________________________*/
typedef std::map<PosInTextRanges, QString> MAP_PosText2QString;
typedef MAP_PosText2QString::const_iterator MAP_PosText2QStringCI;

class PosInText2Str {
    friend class DipyDoc;

 private:
  MAP_PosText2QString    map;
  int                    _internal_state;
  bool                   _well_initialized;

  void                   checks(void);

 public:
                         PosInText2Str(void);
                         PosInText2Str(const PosInText2Str&);
                         PosInText2Str(std::initializer_list< IntegersAndAString >);
                        ~PosInText2Str(void);

  QString&              operator[](PosInTextRanges key);
  const QString &       operator[](const PosInTextRanges key) const;
  PosInText2Str&        operator=(const PosInText2Str&);

  MAP_PosText2QStringCI begin(void) const;
  void                  clear(void);
  PosInTextRanges       contains(PosInText x0) const;
  VectorPosInTextRanges contains(PosInText x0, PosInText x1) const;
  MAP_PosText2QStringCI end(void) const;
  int                   internal_state(void) const;
  size_t                size(void) const;
  bool                  well_initialized(void) const;

  /*
     INTERNALSTATE

     constants used to define the internal_state attribute.

     o OK
     o NOT_YET_INITIALIZED : the object has not yet been initialized.
     o BAD_POS_IN_TEXTRANGES : a PosInTextRanges object isn't correctly initialized.
  */
  enum INTERNALSTATE : int {
    OK = 0,
    NOT_YET_INITIALIZED = -1,
    BAD_POS_IN_TEXTRANGES = -2,
  };
};

inline PosInText2Str::PosInText2Str(void) {
  this->_well_initialized = false;
  this->_internal_state = this->INTERNALSTATE::NOT_YET_INITIALIZED;
}

inline PosInText2Str::PosInText2Str(const PosInText2Str& other)  : \
                  map(other.map), \
                  _internal_state(other._internal_state), \
                  _well_initialized(other._well_initialized)
{}

inline PosInText2Str::PosInText2Str(std::initializer_list< IntegersAndAString > values) {
  this->_well_initialized = true;
  this->_internal_state = this->INTERNALSTATE::OK;

  // i : iterator over this->values :
  for (auto &i : values) {
    this->map.insert(std::pair<PosInTextRanges, QString>(PosInTextRanges(i.integers), i.str) );
  }

  // is everything ok ?
  this->checks();
}

inline PosInText2Str::~PosInText2Str(void) {
}

inline PosInText2Str& PosInText2Str::operator=(const PosInText2Str& other) {
  if (this != &other) {
    this->map = other.map;
    this->_well_initialized = other._well_initialized;
    this->_internal_state = other._internal_state;
  }
  return *this;
}

inline QString& PosInText2Str::operator[](PosInTextRanges key) {
  return this->map[key];
}
inline const QString& PosInText2Str::operator[](const PosInTextRanges key) const {
  return this->map.at(key);
}

inline MAP_PosText2QStringCI PosInText2Str::begin(void) const {
  return this->map.begin();
}

inline MAP_PosText2QStringCI PosInText2Str::end(void) const {
  return this->map.end();
}

inline int PosInText2Str::internal_state(void) const {
  return this->_internal_state;
}

inline size_t PosInText2Str::size(void) const {
  return this->map.size();
}

inline bool PosInText2Str::well_initialized(void) const {
  return this->_well_initialized;
}

#endif  // CPPDIPYLON_POS_POSINTEXT_POSINTEXT2STR_H_
