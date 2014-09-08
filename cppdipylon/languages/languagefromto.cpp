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

    ❏Dipylon❏ : languages/languagefromto.cpp

    See languagefromto.h for the documentation

*******************************************************************************/

#include "languages/languagefromto.h"

/*______________________________________________________________________________

  LanguageFromTo::constructor from a "src" QString.

  see the LANGUAGEFROMTO_FORMAT defined in languagefromto.h
________________________________________________________________________________*/
LanguageFromTo::LanguageFromTo(const QString& src) {
  this->_well_initialized = true;
  this->_internal_state = OK;

  QStringList splitted_strings = src.split(this->SEPARATOR);

  if ( splitted_strings.length() != 2 ) {
    // error : ill-formed src (no SEPARATOR or more than one SEPARATOR)
    this->_well_initialized = false;
    this->_internal_state = ILLFORMED_SOURCE_STRING;
    return;
  }

  // ok, we have the "from" and the "to" languages :
  this->_from = splitted_strings[0];
  this->_to = splitted_strings[1];

  /*............................................................................

    tests :

    o _from, _to must be defined in "known_languages" (see languages.h)

  ............................................................................*/
  auto known_languages_end = languages::known_languages.end();

  if ( languages::known_languages.find(this->_from) == known_languages_end ) {
    this->_well_initialized = false;
    this->_internal_state = UNDEFINED_FROMLANGUAGE;
    qDebug() << "LanguageFromTo::LanguageFromTo() : unknown 'from' language = " << this->_from;
  }

  if (languages::known_languages.find(this->_to) == known_languages_end) {
    this->_well_initialized = false;
    this->_internal_state = UNDEFINED_TOLANGUAGE;
    qDebug() << "LanguageFromTo::LanguageFromTo() : unknown 'to' language = " << this->_to;
  }
}

/*______________________________________________________________________________

  LanguageFromTo::clear()
________________________________________________________________________________*/
void LanguageFromTo::clear(void) {
  this->_well_initialized = false;
  this->_internal_state = NOT_YET_INITIALIZED;
  this->_from = QString("");
  this->_to = QString("");
}

/*______________________________________________________________________________

  LanguageFromTo::repr()

  Return a QString representation of this.
________________________________________________________________________________*/
const QString LanguageFromTo::repr(void) const {
  QString res;

  res += this->from();
  res += this->SEPARATOR;
  res += this->to();

  return res;
}
