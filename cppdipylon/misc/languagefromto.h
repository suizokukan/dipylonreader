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

    ❏Dipylon❏ : misc/languagefromto.h

    LanguageFromTo class, simple wrapper aroung strings like "fra->lat".

    ____________________________________________________________________________

    LANGUAGEFROMTO_FORMAT :

        o XXX + SEPARATOR + YYY, e.g. "fra->lat"
        o the source string can't be empty
        o the two languages must be defined : no language can be an empty string
        o the languages follow the ISO 639-3 format (e.g. "eng", NOT "en")

*******************************************************************************/

#ifndef LANGUAGEFROMTO_H
#define LANGUAGEFROMTO_H

#include <QString>
#include <QStringList>

/*______________________________________________________________________________

  LanguageFromTo class : simple wrapper around "from" and "to" QStrings.

______________________________________________________________________________*/
class LanguageFromTo {

public:
  bool      well_initialized(void) const;
            LanguageFromTo(void);
            LanguageFromTo(const QString&);
  const QString&  from(void) const;
  const QString&  to(void) const;

private:
  bool    _well_initialized;
  QString _from;
  QString _to;


  constexpr static const char* SEPARATOR = "->";
};

inline LanguageFromTo::LanguageFromTo(void) : \
                  _well_initialized(false), \
                  _from(""), \
                  _to("")
{}

inline bool LanguageFromTo::well_initialized(void) const {
  return this->_well_initialized;
}

inline const QString& LanguageFromTo::from(void) const {
  return this->_from;
}

inline const QString& LanguageFromTo::to(void) const {
  return this->_to;
}

#endif
