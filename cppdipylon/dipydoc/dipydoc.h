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
#include <QObject>

/*
  divisions inside a DipyDoc file :

  o DIPYDOCDIV_UNDEFINED : everything but the other constants.
  o DIPYDOCDIV_INSIDE_AUDIORECORD : inside <audiorecord></audiorecord>
  o DIPYDOCDIV_INSIDE_TRANSLATION : inside <translation></translation>
*/
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
friend class MainWindow;

private:

  bool                 _well_initialized;
  int                  _internal_state;

  // general informations :
  int                  dipydoc_version;
  LanguageFromTo       languagefromto;
  // source text :
  QString              source_text;
  // audiorecord data :
  QString              audiorecord_name;
  QString              audiorecord_filename;    // with full path
  PosInText2PosInAudio text2audio;
  PosInAudio2PosInText audio2text;
  // translation data :
  QString              translation_name;
  PosInText2Str        translation;

  bool                 check_path(const QString&);
  void                 init_from_xml(const QString&);

  QStringList          errors;

public:
                       DipyDoc(void);
                       DipyDoc(const QString&);
  void                 clear(void);
  QString              diagnosis(void) const;
  QString              get_condensed_extracts_from_the_source_text(PosInTextRanges, int) const;
  QString              get_xml_repr(void) const;
  int                  internal_state(void) const;
  bool                 well_initialized(void) const;

  static const int     minimal_dipydoc_version = 11;

  // public access to audio2text.contains() :
  PosInTextRanges      audio2text_contains(PosInAudio) const;

  /*
     INTERNALSTATE

     constants used to define the internal_state attribute.

     o OK
     o NOT_YET_INITIALIZED : the object has not been initialized and is in an
                             undefined state.
     o BAD_INITIALIZATION : a problem occurs during the initialization.
     o UNKNOWN_PATH : the source string "path" doesn't exist.
     o PATH_IS_A_FILE : the source string "path" is a file (a directory is expected)
     o MISSING_MAIN_FILE : the main file doesn't exist in "path".
     o MISSING_TEXT_FILE : the text file doesn't exist in "path".
     o MISSING_AUDIO_FILE : the expected audio file is missing.

     please update DipyDoc::diagnosis() if you modify this constants.
  */
  enum INTERNALSTATE : int {
    OK = 0,
    NOT_YET_INITIALIZED = -1,
    BAD_INITIALIZATION = -2,
    UNKNOWN_PATH = -3,
    PATH_IS_A_FILE = -4,
    MISSING_MAIN_FILE = -5,
    MISSING_TEXT_FILE = -6,
    MISSING_AUDIO_FILE = -7,
  };

  // name of the files in a dipydoc directory :
  constexpr static const char*   MAIN_FILENAME = "main.xml";
  constexpr static const char*   TEXT_FILENAME = "text";
};

inline DipyDoc::DipyDoc(void) {
  this->_well_initialized = false;
  this->_internal_state = this->INTERNALSTATE::NOT_YET_INITIALIZED;
  this->source_text = QString("");
  this->translation = PosInText2Str();
  this->dipydoc_version = -1;
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
