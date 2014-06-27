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

#include "pos/posintext/posintext2str.h"
#include "pos/posintext2posinaudio.h"
#include "pos/posinaudio2posintext.h"
#include "languages/languagefromto.h"

// $$$
#include <QDebug>

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QTextStream>
#include <QXmlStreamReader>

// divisions inside a DipyDoc file :
enum DipyDocDiv : int {
    DIPYDOCDIV_UNDEFINED = 0,
    DIPYDOCDIV_INSIDE_AUDIORECORD = 1,
    DIPYDOCDIV_INSIDE_TRANSLATION = 2,
};

/*______________________________________________________________________________

  DipyDoc class

______________________________________________________________________________*/
class DipyDoc {

friend class DipylonUI;

private:

  bool          _well_initialized;
  int           _internal_state;
  PosInText2Str translation;
  QString       source_text;
  PosInText2PosInAudio text2audio;
  PosInAudio2PosInText audio2text;

  int            dipydoc_version;
  LanguageFromTo languagefromto;

  void          check_path(QString&);
  void          init_from_xml(QString&);

public:
                DipyDoc(void);
                DipyDoc(QString&);
  int           internal_state(void) const;
  bool          well_initialized(void) const;

  // public access to audio2text.contains() :
  PosInTextRanges audio2text_contains(PosInAudio) const;

  // constants used to define the internal_state attribute :
  enum INTERNALSTATE : int {
    OK = 0,
    UNKNOWNPATH = 1,
    PATHISAFILE = 2,
    MISSINGTEXT = 3,
  };

  // name of the files in a dipydoc directory :
  constexpr static const char*   TEXTFILE_NAME = "text";
};

inline DipyDoc::DipyDoc(void) {
  this->_well_initialized = true;
  this->_internal_state = this->INTERNALSTATE::OK;
  this->source_text = QString("");
  this->translation = PosInText2Str();
}

inline int DipyDoc::internal_state(void) const {
  return this->_internal_state;
}

inline bool DipyDoc::well_initialized(void) const {
  return this->_well_initialized;
}

inline PosInTextRanges DipyDoc::audio2text_contains(PosInAudio pos) const {
  return this->audio2text.contains(pos);
}

#endif
