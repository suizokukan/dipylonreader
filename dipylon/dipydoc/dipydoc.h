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

    ❏Dipylon❏ : dipydoc/dipydoc.h

    A "Dipylon document" is a text, its translation and its annotations.

*******************************************************************************/

#ifndef DIPYDOC_H
#define DIPYDOC_H

#include "../posintxt/pos2str.h"

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QTextStream>

/*______________________________________________________________________________

  DipyDoc class

______________________________________________________________________________*/
class DipyDoc {

friend class DipylonUI;

private:

  bool    _well_initialized;
  int     _internal_state;
  Pos2Str translation;
  QString source_text;

  void    check_path(QString path);

public:
          DipyDoc(void);
          DipyDoc(QString);
  int     internal_state(void) const;
  bool    well_initialized(void) const;

  // constants used to define the internal_state attribute :
  const int INTERNALSTATE_OK = 0;
  const int INTERNALSTATE_UNKNOWNPATH = 1;
  const int INTERNALSTATE_PATHISAFILE = 2;
  const int INTERNALSTATE_MISSINGTEXT = 3;
  // name of the files in a dipydoc directory :
  const QString TEXTFILE_NAME = "text";
};

inline DipyDoc::DipyDoc(void) {
  this->_well_initialized = true;
  this->_internal_state = this->INTERNALSTATE_OK;
  this->source_text = QString("");
  this->translation = Pos2Str();
}

inline int DipyDoc::internal_state(void) const {
  return this->_internal_state;
}

inline bool DipyDoc::well_initialized(void) const {
  return this->_well_initialized;
}

#endif
