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

#ifndef CPPDIPYLON_DIPYDOC_DIPYDOC_H_
#define CPPDIPYLON_DIPYDOC_DIPYDOC_H_

#include <QDebug>

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QObject>
#include <QTextCharFormat>

#include <map>

#include "./fixedparameters.h"
#include "pos/posintext/posintext2str.h"
#include "pos/posintext2posinaudio.h"
#include "pos/posinaudio2posintext.h"
#include "languages/languagefromto.h"
#include "qt/textformat.h"
#include "qt/blockformat.h"
#include "qt/posintextframeformat.h"

/*
  divisions inside a DipyDoc file :

  o DIPYDOCDIV_INSIDE_ARROW            : inside <arrow>
  o DIPYDOCDIV_INSIDE_AUDIORECORD      : inside <audiorecord>
  o DIPYDOCDIV_INSIDE_COMMENTARYEDITOR : inside <commentaryeditor>
  o DIPYDOCDIV_INSIDE_LEVEL            : inside <level>
  o DIPYDOCDIV_INSIDE_SOURCEEDITOR     : inside <sourceeditor>
  o DIPYDOCDIV_INSIDE_TEXT             : inside <text>
  o DIPYDOCDIV_INSIDE_TEXTFORMATS      : inside <textformats>
  o DIPYDOCDIV_INSIDE_TRANSLATION      : inside <translation>

  o DIPYDOCDIV_UNDEFINED : everything but the other constants.
*/
enum DipyDocDiv : int {
    DIPYDOCDIV_INSIDE_ARROW = 1,
    DIPYDOCDIV_INSIDE_AUDIORECORD = 2,
    DIPYDOCDIV_INSIDE_COMMENTARYEDITOR = 3,
    DIPYDOCDIV_INSIDE_LEVEL = 4,
    DIPYDOCDIV_INSIDE_SOURCEEDITOR = 5,
    DIPYDOCDIV_INSIDE_TEXT = 6,
    DIPYDOCDIV_INSIDE_TEXTFORMATS = 7,
    DIPYDOCDIV_INSIDE_TITLE = 8,
    DIPYDOCDIV_INSIDE_TRANSLATION = 9,

    DIPYDOCDIV_UNDEFINED = 99,
};

/*______________________________________________________________________________

  DipyDocAudioRecord class

  This class is used to create an attribute of DipyDoc.

______________________________________________________________________________*/
struct DipyDocAudioRecord {
  bool                 available;
  QString              name;
  QString              filename;    // with full path
  QString              informations;
  PosInText2PosInAudio text2audio;
  PosInAudio2PosInText audio2text;

  void                 clear(void);
};
inline void DipyDocAudioRecord::clear(void) {
  this->available = false;
  this->name = "";
  this->filename = "";
  this->informations = "";
  this->text2audio.clear();
  this->audio2text.clear();
}

/*______________________________________________________________________________

  DipyDocIntroduction class

  This class is used to create an attribute of DipyDoc.

______________________________________________________________________________*/
struct DipyDocIntroduction {
  bool        available;
  QString     text;
  TextFormat  textformat;
  BlockFormat blockformat;

  void        clear(void);
};
inline void DipyDocIntroduction::clear(void) {
  this->available = false;
  this->text = "";
  this->textformat = TextFormat();
  this->blockformat = BlockFormat();
}

/*______________________________________________________________________________

  DipyDocSourceText class

  This class is used to create an attribute of DipyDoc.

______________________________________________________________________________*/
struct DipyDocSourceText {
  /*
    Before the source text, the title and the introduction may be inserted.
    In this attribute is stored the number of characters appearing before
    the source text.
  */
  int         number_of_chars_before_source_text;

  QString     text;
  QString     name;
  QString     filename;    // with full path
  QString     informations;
  BlockFormat blockformat;

  void    clear(void);
};
inline void DipyDocSourceText::clear(void) {
  this->number_of_chars_before_source_text = 0;
  this->text = "";
  this->name = "";
  this->filename = "";
  this->informations = "";
  this->blockformat = BlockFormat();
}

/*______________________________________________________________________________

  DipyDocTitle class

  This class is used to create an attribute of DipyDoc.

______________________________________________________________________________*/
struct DipyDocTitle {
  bool        available;
  QString     text;
  TextFormat  textformat;
  BlockFormat blockformat;

  void        clear(void);
};
inline void DipyDocTitle::clear(void) {
  this->available = false;
  this->text = "";
  this->textformat = TextFormat();
  this->blockformat = BlockFormat();
}

/*______________________________________________________________________________

  DipyDocTranslation class

  This class is used to create an attribute of DipyDoc.

______________________________________________________________________________*/
struct DipyDocTranslation {
  QString       name;
  QString       informations;
  PosInText2Str translations;

  void          clear(void);
};
inline void DipyDocTranslation::clear(void) {
  this->name = "";
  this->informations = "";
  this->translations.clear();
}

/*______________________________________________________________________________

  DipyDocNotes class

  This class is used to create an attribute of DipyDoc.

______________________________________________________________________________*/
struct NoteSegment {
  QString textformatname = "";
  std::map< PosInTextRanges, QString > arrows;
};

struct Note {
  QString textformatname = "";
  QString text = "";
  std::map<PosInTextRanges, NoteSegment> segments;
};

struct DipyDocNotes {
  std::map<int,  std::map<PosInTextRanges, Note> > notes;
  void clear(void);
};
inline void DipyDocNotes::clear(void) {
  this->notes.clear();
}

/*______________________________________________________________________________

  LevelDetails class

  This class is used to create the "levels" attribute of DipyDoc.

______________________________________________________________________________*/
struct LevelDetails {
  bool       well_initialized = false;

  QString    name;
  TextFormat textformat;

             // default constructor :
             LevelDetails(void);

             // constructor from a QString describing the level's details :
             LevelDetails(QString&, QString&);
};
inline LevelDetails::LevelDetails(void) {
  this->well_initialized = false;
  this->name = QString("");
  this->textformat = TextFormat();
}
inline LevelDetails::LevelDetails(QString& _name, QString& _strtextformat) : name(_name), textformat(_strtextformat) {
  this->well_initialized = this->textformat.well_initialized();
}

/*______________________________________________________________________________

  ArrowDetails class

  This class is used to create the "arrows" attribute of DipyDoc.

______________________________________________________________________________*/
struct ArrowDetails {
  // the same informations are kept twice : as a QString and as serial attributes.
  QString straspect;

  // int    thickness;
  QColor main_color;
  // QColor startingpoint_color;
  // QColor endpoint_color;

  // default constructor :
  ArrowDetails(void);
  // constructor from a QString describing the arrow's aspect :
  explicit ArrowDetails(QString&);
};
inline ArrowDetails::ArrowDetails(void) {
  this->straspect = QString("");
  this->main_color = QColor();
}
inline ArrowDetails::ArrowDetails(QString& _straspect) : straspect(_straspect) {
}

/*______________________________________________________________________________

  DipyDocLettrine class

  This class is used to create the "lettrine" attribute of DipyDoc.

______________________________________________________________________________*/
struct DipyDocLettrine {
  bool                 well_initialized;
  bool                 available;
  QString              filename;
  QImage               image;
  PosInTextFrameFormat position_in_text_frame;
  int                  aspectratio;

       DipyDocLettrine(void);
       DipyDocLettrine(bool _available,
                       const QString& _filename,
                       const QImage& _image,
                       const PosInTextFrameFormat& _position_in_text_frame,
                       int _aspectratio);
  void clear(void);
};
inline DipyDocLettrine::DipyDocLettrine(void) {
  this->well_initialized = false;
  this->available = false;
  this->filename = QString("");
  this->image = QImage();
  this->position_in_text_frame = PosInTextFrameFormat();
  this->aspectratio = 0;
}
inline DipyDocLettrine::DipyDocLettrine(bool _available,
                                        const QString& _filename,
                                        const QImage& _image,
                                        const PosInTextFrameFormat& _position_in_text_frame,
                                        int _aspectratio) : \
available(_available),
filename(_filename),
image(_image),
position_in_text_frame(_position_in_text_frame),
aspectratio(_aspectratio) {
  this->well_initialized = true;
}
inline void DipyDocLettrine::clear(void) {
  this->well_initialized = true;
  this->available = false;
  this->filename = QString("");
  this->image = QImage();
  this->position_in_text_frame = PosInTextFrameFormat();
  this->aspectratio = 1;
}

/*______________________________________________________________________________

  DipyDoc class

______________________________________________________________________________*/
class DipyDoc {
friend class DipylonUI;
friend class MainWindow;
friend class SourceEditor;
friend class CommentaryEditor;

 private:
  bool                 _well_initialized;
  int                  _internal_state;
  QString              doctype;

  QString              main_filename_with_fullpath;

  // general informations :
  int                  dipydoc_version;
  LanguageFromTo       languagefromto;
  // sourceeditor.aspect :
  QString              sourceeditor_stylesheet;
  TextFormat           sourceeditor_default_textformat;
  TextFormat           sourceeditor_karaoke_textformat;
  // commentaryeditor.aspect :
  QString              commentaryeditor_stylesheet;
  TextFormat           commentaryeditor_textformat;
  // title :
  DipyDocTitle         title;
  // introduction :
  DipyDocIntroduction  introduction;
  // lettrine :
  DipyDocLettrine      lettrine;
  // source text :
  DipyDocSourceText    source_text;
  // audiorecord data :
  DipyDocAudioRecord   audiorecord;
  // translation data :
  DipyDocTranslation   translation;
  // text formats :
  std::map<QString, QString> textformats;
  // levels :
  std::map<int, LevelDetails> levels;
  // notes :
  DipyDocNotes         notes;
  // arrows :
  std::map<QString, ArrowDetails> arrows;

  bool                 check_path(const QString&);
  void                 init_from_xml(const QString&);

  QStringList          errors;

 public:
                       DipyDoc(void);
              explicit DipyDoc(const QString&);
  void                 clear(void);
  QString              diagnosis(void) const;
  void                 error__misplaced_content(const QString& element,
                                                const QString& where);
  bool                 error__wrong_content(const LanguageFromTo& src, const QString& where);
  bool                 error__wrong_content(const BlockFormat& src, const QString& where);
  bool                 error__wrong_content(const PosInTextFrameFormat& src, const QString& where);
  bool                 error__wrong_content(const TextFormat& src, const QString& where);
  QString              get_condensed_extracts_from_the_source_text(PosInTextRanges, int) const;
  QString              get_xml_repr(void) const;
  int                  internal_state(void) const;
  bool                 well_initialized(void) const;

  static const int     minimal_dipydoc_version = 24;
  static const int     maximal_dipydoc_version = 24;

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
     o OUTDATED_DIPYDOC_VERSION : the version of the DipyDoc is outdated.
     o DIPYDOC_VERSION_TOO_RECENT : the version of the DipyDoc is too recent.
     o WRONG_VALUE_FOR_LETTRINE_ASPECTRATIO : the lettrine's aspect ratio isn't correct.
     o LETTRINE_FILE_DECLARED_BUT_MISSING : the expected file doesn't exist in "path"
     o WRONG_AUDIORECORD_TEXT2AUDIO : "audiorecord.text2audio" isn't correctly initialized
     o WRONG_AUDIORECORD_AUDIO2TEXT : "audiorecord.audio2text" isn't correctly initialized
     o WRONG_TRANSLATION : the "translations" object isn't correctly initialized.
     o WRONG_DOCTYPE : the document's type is unknown.

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
    MISSING_SOURCE_TEXT_FILE = -8,
    OUTDATED_DIPYDOC_VERSION = -9,
    DIPYDOC_VERSION_TOO_RECENT = -10,
    WRONG_VALUE_FOR_LETTRINE_ASPECTRATIO = 11,
    LETTRINE_FILE_DECLARED_BUT_MISSING = -12,
    WRONG_AUDIORECORD_TEXT2AUDIO = -13,
    WRONG_AUDIORECORD_AUDIO2TEXT = -14,
    WRONG_TRANSLATION = -15,
    WRONG_DOCTYPE = -16,
  };

  // name of the main file in a dipydoc directory :
  constexpr static const char*   MAIN_FILENAME = "main.xml";
};

inline DipyDoc::DipyDoc(void) {
  this->clear();
}

inline int DipyDoc::internal_state(void) const {
  return this->_internal_state;
}

inline bool DipyDoc::well_initialized(void) const {
  return this->_well_initialized;
}

inline PosInTextRanges DipyDoc::audio2text_contains(PosInAudio pos) const {
  return this->audiorecord.audio2text.contains(pos);
}

#endif  // CPPDIPYLON_DIPYDOC_DIPYDOC_H_
