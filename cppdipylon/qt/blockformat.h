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

    ❏Dipylon❏ : qt/blockformat.h

    Blockformat class, simple wrapper around QTextBlockFormat allowing the object
    to be initialized from a string (see BLOCKFORMAT_SRCSTRING_FORMAT below).

	____________________________________________________________________________

	BLOCKFORMAT_SRCSTRING_FORMAT :
		"xxx;yyy" or "xxx;yyy;zzz;"

                in a keyword, spaces are ignored.

		known keywords :

		o "alignement:xxx" with xxx = "left", "right", "hcenter", "justify"

*******************************************************************************/

#ifndef BLOCKFORMAT_H
#define BLOCKFORMAT_H

#include <QTextBlockFormat>
#include <QString>
#include <QStringList>

/*______________________________________________________________________________

  Blockformat class : a simple wrapper around the QTextBlockFormat object
                     named "qtextblockformat".

______________________________________________________________________________*/
class BlockFormat {

private:

  QTextBlockFormat     _qtextblockformat;
  bool                 _well_initialized;
  int                  _internal_state;

  constexpr static const char* SEPARATOR = ";";

public:
                       BlockFormat(void);
                       BlockFormat(const QString&);

  int                  init_from_string(const QString&);
  int                  internal_state(void) const;
  QTextBlockFormat     qtextblockformat(void) const;
  bool                 well_initialized(void) const;

  /*
     INTERNALSTATE

     constants used to define the internal_state attribute.

     o OK
     o NOT_YET_INITIALIZED : the object has not yet been initialized
     o BADSRCSTRING_UNKNOWNKEYWORD : unknown keyword present in the source string.
  */
  enum INTERNALSTATE : int {
    OK = 0,
    NOT_YET_INITIALIZED = -1,
    BADSRCSTRING_UNKNOWNKEYWORD = -2,
  };

};

inline Blockformat::Blockformat(void) {
  this->_well_initialized = false;
  this->_internal_state = this->INTERNALSTATE::NOT_YET_INITIALIZED;
  this->_qtextblockformat = QTextBlockFormat();
}

inline int Blockformat::internal_state(void) const {
  return this->_internal_state;
}

inline bool Blockformat::well_initialized(void) const {
  return this->_well_initialized;
}

#endif
