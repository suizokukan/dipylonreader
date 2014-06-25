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

    ❏Dipylon❏ : misc/languagefromto.cpp

    See languagefromto.h for the documentation

*******************************************************************************/

#include "languagefromto.h"

/*______________________________________________________________________________

  LanguangeFromTo::constructor from a "src" QString.

  see the LANGUAGEFROMTO_FORMAT defined in languagefromto.h
________________________________________________________________________________*/
LanguageFromTo::LanguageFromTo(const QString& src) {

  this->_well_initialized = true;

  QStringList splitted_strings = src.split(this->SEPARATOR);

  if( splitted_strings.length() == 0 ) {
    // error : ill-formed src (no SEPARATOR)
    this->_well_initialized = false;
    return;
  }

  // ok, we have the "from" and the "to" languages :
  this->_from = splitted_strings[0];
  this->_to = splitted_strings[1];

  /*............................................................................
    tests
  ............................................................................*/
  if( this->_from.length() == 0 ) {
    this->_well_initialized = false;
  }

  if( this->_to.length() == 0 ) {
    this->_well_initialized = false;
  }
}
