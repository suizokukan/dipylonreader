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

    ❏Dipylon❏ : languages/languagefromto.h

    LanguageFromTo class, simple wrapper aroung strings like "fra->lat".

    ____________________________________________________________________________

    HOW TO USE :
    LanguageFromTo ll("fra->lat");
    QString from = ll.from();
    qDebug() << from;
    QString from_longname = ll.from_longname();
    qDebug() << from_longname;
    ____________________________________________________________________________

    LANGUAGEFROMTO_FORMAT :

        o XXX + SEPARATOR + YYY, e.g. "fra->lat"
        o the source string can't be empty
        o the two languages must be defined : no language can be an empty string
        o the languages follow the ISO 639-3 format (e.g. "eng", NOT "en")
        o the two languages must be defined by "known_languages" (see languages.h)

*******************************************************************************/

#ifndef LANGUAGEFROMTO_H
#define LANGUAGEFROMTO_H

#include <QString>
#include <QStringList>

#include "languages.h"

/*______________________________________________________________________________

  LanguageFromTo class : simple wrapper around "from" and "to" QStrings.

______________________________________________________________________________*/
class LanguageFromTo {

public:
  int             internal_state(void) const;
  bool            well_initialized(void) const;
                  LanguageFromTo(void);
                  LanguageFromTo(const QString&);
  const QString&  from(void) const;
  const QString&  from_longname(void) const;
  const QString&  to(void) const;
  const QString&  to_longname(void) const;

  /*
     INTERNALSTATE

     constants used to define the internal_state attribute.

     o OK
     o NOT_YET_DEFINED : the object has not been initialized and is in an
                         undefined state.
     o ILLFORMED_SOURCE_STRING : the source string doesn't match the
                                 LANGUAGEFROMTO_FORMAT defined above.
     o UNDEFINED_FROMLANGUAGE : the "from" language is not known by "known_languages".
     o UNDEFINED_TOLANGUAGE : the "to" language is not known by "known_languages".
  */
  enum INTERNALSTATE : int {
    OK = 0,
    NOT_YET_DEFINED = -1,
    ILLFORMED_SOURCE_STRING = -2,
    UNDEFINED_FROMLANGUAGE = -3,
    UNDEFINED_TOLANGUAGE = -4,
  };

private:
  int     _internal_state;
  bool    _well_initialized;
  QString _from;
  QString _to;

  constexpr static const char* SEPARATOR = "->";
};

inline LanguageFromTo::LanguageFromTo(void) : \
                  _internal_state(NOT_YET_DEFINED), \
                  _well_initialized(false), \
                  _from(""), \
                  _to("")
{}

inline int LanguageFromTo::internal_state(void) const {
  return this->_internal_state;
}

inline bool LanguageFromTo::well_initialized(void) const {
  return this->_well_initialized;
}

inline const QString& LanguageFromTo::from(void) const {
    return this->_from;
}

inline const QString& LanguageFromTo::from_longname(void) const {
  return known_languages.at(this->_from);
}

inline const QString& LanguageFromTo::to(void) const {
  return this->_to;
}

inline const QString& LanguageFromTo::to_longname(void) const {
  return known_languages.at(this->_to);
}

#endif
