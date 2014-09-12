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

    ❏DipylonReader❏ : qt/posintextframeformat.h

    PosInTextFrameFormat class, used to describe how an illustration is inserted
    in a DipyDoc text.

    ____________________________________________________________________________

	POSINTEXTFRAMEFORMAT_SRCSTRING_FORMAT :

		known keywords :

                "inflow", "floatleft", "floatright"

*******************************************************************************/

#ifndef CPPDIPYLON_QT_POSINTEXTFRAMEFORMAT_H_
#define CPPDIPYLON_QT_POSINTEXTFRAMEFORMAT_H_

#include <QString>
#include <QStringList>
#include <QTextFrameFormat>

/*______________________________________________________________________________

  PosInTextFrameFormat class
______________________________________________________________________________*/
class PosInTextFrameFormat {
 private:
  QTextFrameFormat::Position  _position;

  QString                     _repr;

  bool                        _well_initialized;
  int                         _internal_state;

  constexpr static const char* SEPARATOR = ";";

 public:
                            PosInTextFrameFormat(void);
                   explicit PosInTextFrameFormat(const QString&);

  int                       init_from_string(const QString&);
  int                       internal_state(void) const;
  QTextFrameFormat::Position position(void) const;
  const QString&            repr(void) const;
  bool                      well_initialized(void) const;

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

inline PosInTextFrameFormat::PosInTextFrameFormat(void) {
  this->_well_initialized = false;
  this->_internal_state = this->INTERNALSTATE::NOT_YET_INITIALIZED;
  this->_repr = QString("");
  this->_position = QTextFrameFormat::InFlow;
}

inline int PosInTextFrameFormat::internal_state(void) const {
  return this->_internal_state;
}

inline QTextFrameFormat::Position PosInTextFrameFormat::position(void) const {
  return this->_position;
}

inline const QString& PosInTextFrameFormat::repr(void) const {
  return this->_repr;
}

inline bool PosInTextFrameFormat::well_initialized(void) const {
  return this->_well_initialized;
}

#endif  // CPPDIPYLON_QT_POSINTEXTFRAMEFORMAT_H_
