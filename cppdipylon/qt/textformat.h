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

    ❏Dipylon❏ : qt/textformat.h

    TextFormat class, simple wrapper around QTextCharFormat allowing the object
    to be initialized from a string (see TEXTFORMAT_SRCSTRING_FORMAT below).

	____________________________________________________________________________

	TEXTFORMAT_SRCSTRING_FORMAT :
		"xxx;yyy" or "xxx;yyy;zzz;"

                in a keyword, spaces are ignored.

		known keywords :

		o "bold"
		o "background-color:xxx" with "xxx"=black/blue/cyan/gray/green/magenta/red/white/yellow
		o "color:xxx"            with "xxx"=black/blue/cyan/gray/green/magenta/red/white/yellow
		o "italic"
		o "underlinecolor:xxx" with "xxx"=black/blue/cyan/gray/green/magenta/red/white/yellow
		o "underlinestyle:xxx" with "xxx"=dashline, dotline, singleline, waveline

*******************************************************************************/

#ifndef TEXTFORMAT_H
#define TEXTFORMAT_H

#include <QTextCharFormat>
#include <QString>
#include <QStringList>

/*______________________________________________________________________________

  TextFormat class : a simple wrapper around the QTextCharFormat object
                     named "qtextcharformat".

______________________________________________________________________________*/
class TextFormat {

private:

  QTextCharFormat      _qtextcharformat;
  QString              _strtextcharformat;
  bool                 _well_initialized;
  int                  _internal_state;

  constexpr static const char* SEPARATOR = ";";

public:
                         TextFormat(void);
                         TextFormat(const QString&);

  int                    init_from_string(const QString&);
  int                    internal_state(void) const;
  const QTextCharFormat& qtextcharformat(void) const;
  const QString&         strtextcharformat(void) const;
  bool                   well_initialized(void) const;

  /*
     INTERNALSTATE

     constants used to define the internal_state attribute.

     o OK
	 o NOT_YET_INITIALIZED : the object has not yet been initialized
	 o BADSRCSTRING_UNKNOWNKEYWORD : unknown keyword present in the source
	                                 string.
  */
  enum INTERNALSTATE : int {
    OK = 0,
    NOT_YET_INITIALIZED = -1,
    BADSRCSTRING_UNKNOWNKEYWORD = -2,
  };

};

inline TextFormat::TextFormat(void) {
  this->_well_initialized = false;
  this->_internal_state = this->INTERNALSTATE::NOT_YET_INITIALIZED;
  this->_qtextcharformat = QTextCharFormat();
  this->_strtextcharformat = QString("");
}

inline int TextFormat::internal_state(void) const {
  return this->_internal_state;
}

inline const QTextCharFormat& TextFormat::qtextcharformat(void) const {
  return this->_qtextcharformat;
}

inline const QString& TextFormat::strtextcharformat(void) const {
  return this->_strtextcharformat;
}

inline bool TextFormat::well_initialized(void) const {
  return this->_well_initialized;
}

#endif
