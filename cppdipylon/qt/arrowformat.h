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

    ❏DipylonReader❏ : qt/arrowformat.h

    ArrowFormat class, simple wrapper around QTextArrowFormat allowing the object
    to be initialized from a string (see ARROWFORMAT_SRCSTRING_FORMAT below).

	____________________________________________________________________________

	ARROWFORMAT_SRCSTRING_FORMAT :
		"xxx;yyy" or "xxx;yyy;zzz;"

                in a keyword, spaces are ignored.

		known keywords :

                o "thickness:xxx" where xxx is an integer
                o "main-color:xxx" with "xxx"=black/blue/cyan/gray/green/magenta/red/white/yellow or #RRGGBB
                o "start-olor:xxx" with "xxx"=black/blue/cyan/gray/green/magenta/red/white/yellow or #RRGGBB
                o "end-color:xxx" with "xxx"=black/blue/cyan/gray/green/magenta/red/white/yellow or #RRGGBB

*******************************************************************************/

#ifndef CPPDIPYLON_QT_ARROWFORMAT_H_
#define CPPDIPYLON_QT_ARROWFORMAT_H_

#include <QDebug>
#include <QColor>
#include <QString>
#include <QStringList>

/*______________________________________________________________________________

  ArrowFormat class : details used to draw an arrow.

______________________________________________________________________________*/
class ArrowFormat {
 private:
  QColor               _endcolor;
  int                  _internal_state;
  QColor               _maincolor;
  QString              _repr;
  QColor               _startcolor;
  int                  _thickness;
  bool                 _well_initialized;

  constexpr static const char* SEPARATOR = ";";

 public:
                          ArrowFormat(void);
                 explicit ArrowFormat(const QString&);

  QColor                  endcolor(void) const;
  int                     init_from_string(const QString&);
  int                     internal_state(void) const;
  QColor                  maincolor(void) const;
  const QString&          repr(void) const;
  QColor                  startcolor(void) const;
  int                     thickness(void) const;
  bool                    well_initialized(void) const;

  /*
     INTERNALSTATE

     constants used to define the internal_state attribute.

     o OK
     o NOT_YET_INITIALIZED : the object has not yet been initialized
     o BADSRCSTRING_UNKNOWNKEYWORD : unknown keyword in the init string.
     o WRONG_DECIMAL_VALUE_FOR_THICKNESS : the value must be an integer greater than 0.
     o WRONG_HEX_VALUE_FOR_MAIN_COLOR : must be between #000000 and #FFFFFF.
     o WRONG_HEX_VALUE_FOR_START_COLOR : must be between #000000 and #FFFFFF.
     o WRONG_HEX_VALUE_FOR_END_COLOR : must be between #000000 and #FFFFFF.
  */
  enum INTERNALSTATE : int {
    OK = 0,
    NOT_YET_INITIALIZED = -1,
    BADSRCSTRING_UNKNOWNKEYWORD = -2,
    WRONG_DECIMAL_VALUE_FOR_THICKNESS = -3,
    WRONG_HEX_VALUE_FOR_MAIN_COLOR = -4,
    WRONG_HEX_VALUE_FOR_START_COLOR = -5,
    WRONG_HEX_VALUE_FOR_END_COLOR = -6,
  };
};

inline ArrowFormat::ArrowFormat(void) {
  this->_well_initialized = false;
  this->_internal_state = this->INTERNALSTATE::NOT_YET_INITIALIZED;
  this->_repr = QString("");

  this->_thickness = 1;
  this->_maincolor = QColor();
  this->_startcolor = QColor();
  this->_endcolor = QColor();
}

inline QColor ArrowFormat::endcolor(void) const {
  return this->_endcolor;
}

inline int ArrowFormat::internal_state(void) const {
  return this->_internal_state;
}

inline QColor ArrowFormat::maincolor(void) const {
  return this->_maincolor;
}

inline const QString& ArrowFormat::repr(void) const {
  return this->_repr;
}

inline QColor ArrowFormat::startcolor(void) const {
  return this->_startcolor;
}

inline int ArrowFormat::thickness(void) const {
  return this->_thickness;
}

inline bool ArrowFormat::well_initialized(void) const {
  return this->_well_initialized;
}

#endif  // CPPDIPYLON_QT_ARROWFORMAT_H_
