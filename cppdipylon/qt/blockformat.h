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

    ❏DipylonReader❏ : qt/blockformat.h

    BlockFormat class, simple wrapper around QTextBlockFormat allowing the object
    to be initialized from a string (see BLOCKFORMAT_SRCSTRING_FORMAT below).

	____________________________________________________________________________

	BLOCKFORMAT_SRCSTRING_FORMAT :
		"xxx;yyy" or "xxx;yyy;zzz;"

                in a keyword, spaces are ignored.

		known keywords :

		o "alignment:xxx" with xxx = "left", "right", "hcenter", "justify"
                o "line-height:xxx%" where xxx is an integer (0<=integer)

*******************************************************************************/

#ifndef CPPDIPYLON_QT_BLOCKFORMAT_H_
#define CPPDIPYLON_QT_BLOCKFORMAT_H_

#include <QString>
#include <QStringList>
#include <QTextBlockFormat>

/*______________________________________________________________________________

  BlockFormat class : a simple wrapper around the QTextBlockFormat object
                     named "qtextblockformat".

______________________________________________________________________________*/
class BlockFormat {
 private:
  QTextBlockFormat        _qtextblockformat;
  QString                 _repr;
  bool                    _well_initialized;
  int                     _internal_state;

  static const QString    SEPARATOR;

 public:
                          BlockFormat(void);
                 explicit BlockFormat(const QString&);

  int                     init_from_string(const QString&);
  int                     internal_state(void) const;
  const QString&          repr(void) const;
  const QTextBlockFormat& qtextblockformat(void) const;
  bool                    well_initialized(void) const;

  /*
     INTERNALSTATE

     constants used to define the internal_state attribute.

     o OK
     o NOT_YET_INITIALIZED : the object has not yet been initialized
     o BADSRCSTRING_UNKNOWNKEYWORD : unknown keyword present in the source string.
     o LINE_HEIGHT_IS_NOT_A_PERCENTAGE : line-height expects a percentage.
     o LINE_HEIGHT_IS_NOT_A_VALID_PERCENTAGE : line-height expects a percentage which is
                                               an integer greater or equal to 0.
  */
  enum INTERNALSTATE : int {
    OK = 0,
    NOT_YET_INITIALIZED = -1,
    BADSRCSTRING_UNKNOWNKEYWORD = -2,
    LINE_HEIGHT_IS_NOT_A_PERCENTAGE = -3,
    LINE_HEIGHT_IS_NOT_A_VALID_PERCENTAGE = -3,
  };
};

inline BlockFormat::BlockFormat(void) {
  this->_well_initialized = false;
  this->_internal_state = this->INTERNALSTATE::NOT_YET_INITIALIZED;
  this->_repr = QString("");
  this->_qtextblockformat = QTextBlockFormat();
}

inline int BlockFormat::internal_state(void) const {
  return this->_internal_state;
}

inline const QTextBlockFormat& BlockFormat::qtextblockformat(void) const {
  return this->_qtextblockformat;
}

inline const QString& BlockFormat::repr(void) const {
  return this->_repr;
}

inline bool BlockFormat::well_initialized(void) const {
  return this->_well_initialized;
}

#endif  // CPPDIPYLON_QT_BLOCKFORMAT_H_
