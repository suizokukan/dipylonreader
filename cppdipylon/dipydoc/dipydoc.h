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

    ❏DipylonReader❏ : dipydoc/dipydoc.h

    A "Dipylon document" is a text, its translation and its annotations.

*******************************************************************************/

#ifndef CPPDIPYLON_DIPYDOC_DIPYDOC_H_
#define CPPDIPYLON_DIPYDOC_DIPYDOC_H_

#include <QCryptographicHash>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QObject>
#include <QString>
#include <QTextCharFormat>
#include <QTextStream>
#include <QXmlStreamReader>

#include <cstring>
#include <map>
#include <memory>
#include <utility>

#include "./fixedparameters.h"
#include "debugmsg/debugmsg.h"
#include "dipydoc/menunames.h"
#include "dipydoc/notes.h"
#include "dipydoc/syntagmas.h"
#include "languages/languagefromto.h"
#include "pos/posintext/posintext2str.h"
#include "pos/posintext2posinaudio.h"
#include "pos/posinaudio2posintext.h"
#include "qt/arrowformat.h"
#include "qt/blockformat.h"
#include "qt/posintextframeformat.h"
#include "qt/textformat.h"

/*______________________________________________________________________________

  DipyDocAudioRecord class

  This class is used to create an attribute of DipyDoc.

______________________________________________________________________________*/
struct DipyDocAudioRecord {
  bool                 found;
  QString              description;
  QString              filename;    // with full path
  QString              informations;
  PosInText2PosInAudio text2audio;
  PosInAudio2PosInText audio2text;

  void                 clear(void);
};
inline void DipyDocAudioRecord::clear(void) {
  this->found = false;
  this->description = "";
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
  bool        found;
  QString     text;
  TextFormat  textformat;
  BlockFormat blockformat;

  void        clear(void);
};
inline void DipyDocIntroduction::clear(void) {
  this->found = false;
  this->text = "";
  this->textformat = TextFormat();
  this->blockformat = BlockFormat();
}

/*______________________________________________________________________________

  DipyDocLettrine class

  This class is used to create the "lettrine" attribute of DipyDoc.

______________________________________________________________________________*/
struct DipyDocLettrine {
  bool                 found;
  QString              filename_with_fullpath;
  QImage               image;
  PosInTextFrameFormat position_in_text_frame;
  int                  aspectratio;

       DipyDocLettrine(void);
       DipyDocLettrine(bool _found,
                       const QString& _filename_with_fullpath,
                       const QImage& _image,
                       const PosInTextFrameFormat& _position_in_text_frame,
                       int _aspectratio);
  void clear(void);
};
inline DipyDocLettrine::DipyDocLettrine(void) {
  this->found = false;
  this->filename_with_fullpath = QString("");
  this->image = QImage();
  this->position_in_text_frame = PosInTextFrameFormat();
  this->aspectratio = 0;
}
inline DipyDocLettrine::DipyDocLettrine(bool _found,
                                        const QString& _filename_with_fullpath,
                                        const QImage& _image,
                                        const PosInTextFrameFormat& _position_in_text_frame,
                                        int _aspectratio) : \
found(_found),
filename_with_fullpath(_filename_with_fullpath),
image(_image),
position_in_text_frame(_position_in_text_frame),
aspectratio(_aspectratio) {
}
inline void DipyDocLettrine::clear(void) {
  this->found = false;
  this->filename_with_fullpath = QString("");
  this->image = QImage();
  this->position_in_text_frame = PosInTextFrameFormat();
  this->aspectratio = 1;
}

/*______________________________________________________________________________

  DipyDocSourceText class

  This class is used to create an attribute of DipyDoc; see DipyDoc class
  to see how this class is used.

______________________________________________________________________________*/
struct DipyDocSourceText {
  QString     text;
  QString     description;
  QString     filename;    // with full path
  QString     informations;
  BlockFormat blockformat;

  void    clear(void);
};
inline void DipyDocSourceText::clear(void) {
  this->text = "";
  this->description = "";
  this->filename = "";
  this->informations = "";
  this->blockformat = BlockFormat();
}

/*______________________________________________________________________________

  DipyDocTitle class

  This class is used to create an attribute of DipyDoc.

______________________________________________________________________________*/
struct DipyDocTitle {
  bool        found;
  QString     text;
  TextFormat  textformat;
  BlockFormat blockformat;

  void        clear(void);
};
inline void DipyDocTitle::clear(void) {
  this->found = false;
  this->text = "";
  this->textformat = TextFormat();
  this->blockformat = BlockFormat();
}

/*______________________________________________________________________________

  DipyDocTranslation class

  This class is used to create an attribute of DipyDoc.

______________________________________________________________________________*/
struct DipyDocTranslation {
  bool          found;
  QString       description;
  QString       informations;
  PosInText2Str translations;

  void          clear(void);
};
inline void DipyDocTranslation::clear(void) {
  this->found = false;
  this->description = "";
  this->informations = "";
  this->translations.clear();
}

/*______________________________________________________________________________

  LevelDetails class

  This class is used to create the "levels" attribute of DipyDoc.

______________________________________________________________________________*/
struct LevelDetails {
  QString    name;
  TextFormat textformat;

             // default constructor :
             LevelDetails(void);

             // constructor from a QString describing the level's details :
             LevelDetails(QString&, QString&);
};
inline LevelDetails::LevelDetails(void) {
  this->name = QString("");
  this->textformat = TextFormat();
}
inline LevelDetails::LevelDetails(QString& _name, QString& _strtextformat) : name(_name), textformat(_strtextformat) {}

class CommentaryTempData;
/*______________________________________________________________________________

  DipyDoc class

______________________________________________________________________________*/
typedef std::pair<PosInTextRanges, PairOfPosInAudio> PTRangesAND2PosAudio;

class DipyDoc {
friend class CommentaryEditor;
friend class CommentaryTempData;
friend class MainWindow;
friend class SourceEditor;
friend class SCSplitter;
friend class SourceZone;
friend class UI;

 private:
  bool                 _well_initialized;
  int                  _internal_state;
  /*
    "unspecified" or one of the strings defined in fixedparameters::known_doctypes.
  */
  QString              doctype;

  QString              path;
  QString              main_filename_with_fullpath;

  QXmlStreamReader*    xmlreader = nullptr;

  /*
     general informations :
  */
  // name(s) displayed in the File>Open menu :
  // initialized by ::read_menu_name()
  QString              menu_name;
  // name used in the qsettings file :
  // initialized by ::set_qsettings_name()
  QString              qsettings_name;
  // name used internally
  // initialized by ::set_internal_name()
  QString              internal_name;

  QString              id;
  int                  version;
  int                  dipydocformat_version;
  LanguageFromTo       languagefromto;
  // sourceeditor.aspect :
  QString              sourceeditor_stylesheet;
  TextFormat           sourceeditor_default_textformat;
  TextFormat           sourceeditor_rmode_textformat;
  TextFormat           sourceeditor_lmode_textformat;
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
  // syntagmas added as notes :
  Notes                notes;

  QStringList          err_messages;

  // private methods ...........................................................
  bool                   check_path(const QString&);
  void                   clear(void);
  bool                   error(const QString& msg);
  bool                   error(const QString& msg, const QString& error_string);
  template<class T> bool error(const T& object, const QString& _error_string, const QString& where);
  QString                error_string(void);
  QString                get_condensed_extracts_from_the_source_text(PosInTextRanges, int) const;
  QString                get_tab_name(void);
  QString                get_translations_for(PosInText x0, PosInText x1) const;
  bool                   read_mainfile__first_token(void);
  bool                   read_mainfile__doctype_text(void);
  bool                   read_mainfile__doctype_text__init_and_check(void);
  bool                   read_mainfile__doctype_text__syntagma(Syntagma * father);
  void                   read_menu_name(const QString& _path);
  void                   set_internal_name(void);
  void                   set_qsettings_name(void);

  // public methods .............................................................
 public:
                       DipyDoc(void);
                      ~DipyDoc(void);
              explicit DipyDoc(const QString&);
  PosInTextRanges      audio2text_contains(PosInAudio x0) const;
  PTRangesAND2PosAudio text2audio_contains(PosInText x0) const;
  PosInTextRanges      translation_contains(PosInText x0) const;
  PosInTextRanges      translation_contains(PosInText x0, PosInText x1) const;
  QString              diagnosis(void) const;
  QString              get_xml_repr(void) const;
  void                 read_mainfile(const QString&);
  int                  internal_state(void) const;
  bool                 well_initialized(void) const;
  QString              syntagmas_repr(void) const;

  // public constants ...........................................................
  static const int     min_dipydocformat_version;
  static const int     max_dipydocformat_version;
  // for the following constants, see
  // the get_condensed_extracts_from_the_source_text() method :
  static const int     condensed_extracts_length;
  static const QString condensed_extracts_separator;

  /*
     INTERNALSTATE

     constants used to define the internal_state attribute.

     o OK :  the object has been correctly initialized.
     o NOT_YET_INITIALIZED : the object has not been initialized and is in an undefined state.
     o NOT_CORRECTLY_INITIALIZED : a problem occurs during the initialization.
     o INCORRECT_VERSION_OF_THE_DIPYDOC : version too high or too low.
     o THE_GIVENPATH_DOES_NOT_EXIST : wrong path to the DipyDoc
     o THE_GIVENPATH_IS_NOT_A_DIRECTORY
  */
  enum INTERNALSTATE : int {
    OK = 0,
    NOT_YET_INITIALIZED = -1,
    NOT_CORRECTLY_INITIALIZED = -2,
    INCORRECT_VERSION_OF_THE_DIPYDOC = -3,
    THE_GIVENPATH_DOES_NOT_EXIST = -4,
    THE_GIVENPATH_IS_NOT_A_DIRECTORY = -5,
  };
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
