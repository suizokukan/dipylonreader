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

    ❏DipylonReader❏ : dipydoc/dipydoc.cpp

    See dipydoc.h for the documentation

*******************************************************************************/

#include "dipydoc/dipydoc.h"
#include <map>

const int     DipyDoc::min_dipydocformat_version    = fixedparameters::min_dipydocformat_version;
const int     DipyDoc::max_dipydocformat_version    = fixedparameters::min_dipydocformat_version;
const int     DipyDoc::condensed_extracts_length    = 30;
const QString DipyDoc::condensed_extracts_separator = "//";

/*______________________________________________________________________________

        DipyDoc::constructor from a "_path" : initialize "this" from the files
                                              stored in "_path/0"

        See above for a description of the expected files.

        Fill "err_messages" with human-readable messages.

______________________________________________________________________________*/
DipyDoc::DipyDoc(const QString& _path) {
  // DEBUG1 DebugMsg() << "DipyDoc::DipyDoc from " << _path;

  this->clear();

  this->_well_initialized = true;
  this->_internal_state = DipyDoc::INTERNALSTATE::OK;

  // does the path leads to the expected files ?
  if (this->check_path(_path) == false) {
    // DEBUG1 DebugMsg() << "DipyDoc::DipyDoc" << "problem with the path =" << _path;
    this->_well_initialized = false;
    this->_internal_state = DipyDoc::INTERNALSTATE::NOT_CORRECTLY_INITIALIZED;
    return;
  }

  // let's read this->number_of_textversions :
  if (this->set_number_of_textversions(_path) == false) {
    // DEBUG1 DebugMsg() << "DipyDoc::DipyDoc" << "problem with the path =" << _path;
    // DEBUG1 DebugMsg() << "the number of versions of the available text isn't in the [1-10] range.";
    this->_well_initialized = false;
    this->_internal_state = DipyDoc::INTERNALSTATE::NOT_CORRECTLY_INITIALIZED;
    return;
  }

  // let's read the 'menuname' file :
  this->read_menu_name(_path);

  // let's initialize the qsettings' name :
  this->set_qsettings_name();
  // let's initialize the internal name :
  this->set_internal_name();

  /*
    Let's load the textversion #0 in the "_path/0" directory :
  */
  this->load_a_textversion(_path, 0);

  // DEBUG1 DebugMsg() << "(DipyDoc::DipyDoc) exit point";
}

/*______________________________________________________________________________

        DipyDoc::~DipyDoc()

        DipyDoc destructor
______________________________________________________________________________*/
DipyDoc::~DipyDoc(void) {
  // DEBUG1 DebugMsg() << "DipyDoc::~DipyDoc : entry point; menu_name=" << this->menu_name;

  /* deleting notes._syntagmas :
  */
  this->clean_syntagmas();

  // DEBUG1 DebugMsg() << "DipyDoc::~DipyDoc : exit point";
}

/*______________________________________________________________________________

        DipyDoc::check_path() : check if "_path" and "_path/0" leads to the expected files.

        Return false if an error occurs, or true if everything's ok.

        tests :

        o (1) does "_path" exist ?
        o (2) is "_path" a directory ?
        o (3) does the menuname file exist ?
        o (4) does "_path/0" exist ?
        o (5) is "_path/0" a directory ?
        o (6) does the main file exist in "_path/0" ?
______________________________________________________________________________*/
bool DipyDoc::check_path(const QString& _path) {
  // (1) does "_path" exists ?
  QFileInfo path_info = QFileInfo(_path);
  if (path_info.exists() == false) {
    QString msg(QString("An error occured while opening a DipyDoc : the path '%1' doesn't exist").arg(_path));
    this->_internal_state = DipyDoc::INTERNALSTATE::THE_GIVENPATH_DOES_NOT_EXIST;
    this->error(msg);
    return false;
  }

  // (2) is "_path" a directory ?
  if (path_info.isFile() == true) {
    QString msg(QString("An error occured while opening a DipyDoc : the path '%1' is not a directory.").arg(_path));
    this->_internal_state = DipyDoc::INTERNALSTATE::THE_GIVENPATH_IS_NOT_A_DIRECTORY;
    this->error(msg);
    return false;
  }

  // (3) does the menuname file exist ?
  QFileInfo menuname_info = QFileInfo(_path + "/" + fixedparameters::DIPYDOC__MENUNAME_FILENAME);
  if (menuname_info.exists() == false) {
    QString msg(QString("An error occured while opening a DipyDoc : "
                        "the menu name file %1 "
                        "doesn't exist in %2.").arg(fixedparameters::DIPYDOC__MENUNAME_FILENAME,
                                                    _path));
    this->error(msg);
    return false;
  }

  // (4) does "_path/0" exists ?
  QString path0 = _path + "/0";
  QFileInfo path_info0 = QFileInfo(_path + "/0");

  if (path_info0.exists() == false) {
    QString msg(QString("An error occured while opening a DipyDoc : the path '%1' doesn't exist").arg(path0));
    this->_internal_state = DipyDoc::INTERNALSTATE::THE_GIVENPATH_DOES_NOT_EXIST;
    this->error(msg);
    return false;
  }

  // (5) is "_path/0" a directory ?
  if (path_info0.isFile() == true) {
    QString msg(QString("An error occured while opening a DipyDoc : the path '%1' is not a directory.").arg(_path));
    this->_internal_state = DipyDoc::INTERNALSTATE::THE_GIVENPATH_IS_NOT_A_DIRECTORY;
    this->error(msg);
    return false;
  }

  // (6) does the main file exist in "_path/0" ?
  QFileInfo main_info = QFileInfo(path0 + "/" + fixedparameters::DIPYDOC__MAIN_FILENAME);
  if (main_info.exists() == false) {
    QString msg(QString("An error occured while opening a DipyDoc : "
                        "the main file %1 "
                        "doesn't exist in %2.").arg(fixedparameters::DIPYDOC__MAIN_FILENAME,
                                                    _path));
    this->error(msg);
    return false;
  }

  return true;
}

/*______________________________________________________________________________

    DipyDoc::clean_before_loading_a_new_textversion()

    The method cleans what can't be kept since a new text level is about to be
    loaded.

______________________________________________________________________________*/
void DipyDoc::clean_before_loading_a_new_textversion(void) {
  this->clean_syntagmas();
}

/*______________________________________________________________________________

    DipyDoc::clean_syntagmas()

       this->notes._syntagmas being filled with pointers, we have to clean up 
     their content manually.

______________________________________________________________________________*/
void DipyDoc::clean_syntagmas(void) {
  // DEBUG1 DebugMsg() << "DipyDoc::clean_syntagmas : entry point";

  while (!this->notes._syntagmas.empty()) {
    this->notes._syntagmas.front().reset();
    this->notes._syntagmas.pop_front();
  }

  // DEBUG1 DebugMsg() << "DipyDoc::clean_syntagmas : exit point";
}

/*______________________________________________________________________________

        DipyDoc::clear()

______________________________________________________________________________*/
void DipyDoc::clear(void) {
  this->_well_initialized = false;
  this->_internal_state = DipyDoc::INTERNALSTATE::NOT_YET_INITIALIZED;

  this->id = QString("default id");
  this->version = 0;

  this->number_of_textversions = 0;
  this->current_textversion = 0;
  this->textversion_description = QString("unspecified textversion");

  this->doctype = QString("unspecified");

  this->path = QString("");
  this->main_filename_with_fullpath = QString("");

  this->err_messages.clear();

  this->title.clear();
  this->introduction.clear();
  this->lettrine.clear();

  this->sourceeditor_stylesheet = fixedparameters::default__sourceeditor_stylesheet;
  this->commentaryeditor_stylesheet = fixedparameters::default__commentaryeditor_stylesheet;

  this->dipydocformat_version = -1;
  this->languagefromto.clear();

  this->notes.found = false;
  this->notes.syntagmas_aspects.clear();
  this->notes.syntagmas_levels.clear();
  this->notes.arrows_types.clear();

  this->source_text.clear();
  this->audiorecord.clear();
  this->translation.clear();
}

/*______________________________________________________________________________

        DipyDoc::diagnosis()

        Return a human-readable QString explaining the internal state of the
        program.

______________________________________________________________________________*/
QString DipyDoc::diagnosis(void) const {
  switch (this->_internal_state) {
    case DipyDoc::INTERNALSTATE::OK : {
      return QObject::tr("No problem has been detected.");
    }

    case DipyDoc::INTERNALSTATE::NOT_YET_INITIALIZED : {
      return QObject::tr("corrupted DipyDoc : the document could not be read. "
                         "Please replace this Dipydoc by another one.");
    }

    case DipyDoc::INTERNALSTATE::NOT_CORRECTLY_INITIALIZED : {
      return QObject::tr("corrupted DipyDoc : the document could not be read. "
                         "Please replace this Dipydoc by another one.");
    }

    case DipyDoc::INTERNALSTATE::INCORRECT_VERSION_OF_THE_DIPYDOC : {
      return QObject::tr("The DipyDoc could not be read since its version is either too old"
                         "or too recent. See the details for more informations."
                         "Please update your Dipydoc application.");
    }

    case DipyDoc::INTERNALSTATE::THE_GIVENPATH_DOES_NOT_EXIST : {
      return QObject::tr("This DipyDoc could not be read since the given path doesn't exist."
                         "Please give another path.");
    }

    case DipyDoc::INTERNALSTATE::THE_GIVENPATH_IS_NOT_A_DIRECTORY : {
      return QObject::tr("This DipyDoc could not be read since the given path is"
                         "not a directory (perhaps did you give a file instead ?)"
                         "Please give a directory and not a file to load.");
    }

    default : {
      return QObject::tr("anomaly : unknown internal state.");
    }
  }
}

/*______________________________________________________________________________

  DipyDoc::error() functions

  fill err_messages if an error is detected in the object given as a parameter.

  all these functions return a bool : if an error has been detected, return true.

________________________________________________________________________________*/
// minimal functions :
bool DipyDoc::error(const QString& _msg) {
  QString msg(QString("#ERROR# An error occured by reading the main file : msg=\"%1\";.").arg(_msg));
  this->err_messages.append(msg);
  // DEBUG1 DebugMsg() << msg;

  return true;  // since this function has been called, there must be an error !
}
bool DipyDoc::error(const QString& _msg, const QString& _error_string) {
  QString msg(QString("#ERROR# An error occured by reading the main file : "
                      "msg=\"%1\"; error_string()=\"%2\".").arg(_msg, _error_string));
  this->err_messages.append(msg);
  // DEBUG1 DebugMsg() << msg;

  return true;  // since this function has been called, there must be an error !
}
// full function, for any object :
template<class T> bool DipyDoc::error(const T& object, const QString& _error_string, const QString& where) {
  // is there an error in "object" ?
  bool error_detected = !object.well_initialized();

  if (error_detected == true) {
    QString msg(QString("#ERROR# An error occured by reading the main file : "
                        "error_string=\"%1\"; where=\"%2\".").arg(_error_string, where));
    this->err_messages.append(msg);
    // DEBUG1 DebugMsg() << msg;
  }

  return error_detected;
}

/*______________________________________________________________________________

  DipyDoc::error_string()

______________________________________________________________________________*/
QString DipyDoc::error_string(void) {
  return QString("%1\nLine %2, column %3").arg(this->xmlreader->errorString(),
                                               QString().setNum(this->xmlreader->lineNumber()),
                                               QString().setNum(this->xmlreader->columnNumber()));
}

/*______________________________________________________________________________

        DipyDoc::get_condensed_extracts_from_the_source_text

        Return from this->source_text the extracts whose position is given
        in "positions".

        o "maxlength" is the maximal length of the whole string returned.
______________________________________________________________________________*/
QString DipyDoc::get_condensed_extracts_from_the_source_text(PosInTextRanges positions, int maxlength) const {
  QString res;

  for (auto &textrange : positions) {
    QString substring = this->source_text.text.mid(static_cast<int>(textrange.first),
                                                   static_cast<int>(textrange.second - textrange.first));
    res += substring;
    res += condensed_extracts_separator;
  }

  // removing the last '//', if necessary :
  if (positions.size() != 0) {
    res.chop(condensed_extracts_separator.size());
  }

  if (res.length() > maxlength) {
      int left_length = (maxlength / 2)-3;
      int right_length = maxlength - left_length;
      res = res.left(left_length) + "[…]" + res.right(right_length);
  }

  return res;
}

/*______________________________________________________________________________

   DipyDoc::get_tab_name()

   Return a name convenient to tabs' display.
________________________________________________________________________________*/
QString DipyDoc::get_tab_name(void) {
  if (this->menu_name.size() <= fixedparameters::maxlen_in_tab_name) {
    return this->menu_name;
  } else {
    return "…" + this->menu_name.right(fixedparameters::maxlen_in_tab_name-1);
  }
}

/*______________________________________________________________________________

  DipyDoc::get_translations_for() : return a QString with the translations
                                    matching the positions x0 to x1 in the
                                    source text.
______________________________________________________________________________*/
QString DipyDoc::get_translations_for(PosInText x0, PosInText x1) const {
  VectorPosInTextRanges vector_posintextranges = this->translation.translations.contains(x0, x1);

  QStringList strlist_of_translations;

  for (auto &posintextranges : vector_posintextranges) {
    strlist_of_translations.append(this->translation.translations[posintextranges]);
  }

  return strlist_of_translations.join(" ");
}

/*______________________________________________________________________________

        DipyDoc::get_xml_repr

        Return an xml-string describing the current state of "this" and add :

        o a note about the file being automatically generated.
        o the extracts corresponding to the 'srctext' token.

______________________________________________________________________________*/
QString DipyDoc::get_xml_repr(void) const {
  QString res;

  /*............................................................................
    header
  ............................................................................*/
  res += "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";

  res += "\n";

  res += "<!--\n";
  res += "  This file was automatically generated by a call "
         "to DipyDoc::get_xml_repr()\n";
  res += "-->\n";

  res += "\n";

  res += "<dipydoc dipydoc_version=\"$DIPYDOCVERSION$\" "
         "languages=\"$LANGUAGEFROMTO$\" "
         "type=\"$DOCTYPE$\" "
         ">\n";

  res += "\n";

  /*............................................................................
    title :
  ............................................................................*/
  if (this->title.found == true) {
    res += "  <title "
           "textformat=\"$TITLETEXTFORMAT$\" "
           "blockformat=\"$TITLEBLOCKFORMAT$\" "
           ">"
           "$TITLETEXT$"
           "</title>\n\n";
  }

  /*............................................................................
    introduction :
  ............................................................................*/
  if (this->introduction.found == true) {
    res += "  <introduction textformat=\"$INTRODUCTIONTEXTFORMAT$\" "
           "blockformat=\"$INTRODUCTIONBLOCKFORMAT$\">"
           "$INTRODUCTIONTEXT$"
           "</introduction>\n\n";
  }

  /*............................................................................
    lettrine :
  ............................................................................*/
  if (this->lettrine.found == true) {
    res += "  <lettrine filename=\"$LETTRINEFILENAME$\" "
           "positionintextframe=\"$LETTRINEPOSITIONINTEXTFRAME$\" "
           "aspectratio=\"$LETTRINEASPECTRATIO$\"/>\n\n";
  }

  /*............................................................................
    text : no sub-elements.
  ............................................................................*/
  res += "  <text \n"
         "        description=\"$TEXTNAME$\" \n"
         "        filename=\"$TEXTFILENAME$\" \n"
         "        informations=\"$TEXTINFORMATIONS$\" \n"
         "        blockformat=\"$TEXTBLOCKFORMAT$\" \n"
         "  />\n";

  /*............................................................................
    aspect :
  ............................................................................*/
  res += "\n";
  res += "  <aspect>\n";

  res += "    <sourceeditor>\n";
  res += "      <stylesheet>$SOURCEEDITOR_STYLESHEET$</stylesheet>\n";
  res += "      <default_textformat>$SOURCEEDITOR_DEFAULTTEXTFORMAT$"
         "</default_textformat>\n";
  res += "      <rmode_textformat>$SOURCEEDITOR_RMODETEXTFORMAT$"
         "</rmode_textformat>\n";
  res += "      <lmode_textformat>$SOURCEEDITOR_LMODETEXTFORMAT$"
         "</lmode_textformat>\n";
  res += "    </sourceeditor>\n";

  res += "    <commentaryeditor>\n";
  res += "      <stylesheet>$COMMENTARYEDITOR_STYLESHEET$"
         "</stylesheet>\n";
  res += "      <textformat>$COMMENTARYEDITOR_DEFAULTTEXTFORMAT$"
         "</textformat>\n";
  res += "    </commentaryeditor>\n";

  res += "  </aspect>\n";

  /*............................................................................
    audiorecord : the functions reads through this->audiorecord.text2audio with sorted keys.
  ............................................................................*/
  if (this->audiorecord.found == true) {
    res += "\n";

    res += "  <audiorecord \n"
           "        description=\"$AUDIORECORDNAME$\" \n"
           "        filename=\"$AUDIORECORDFILENAME$\" \n"
           "        informations=\"$AUDIORECORDINFORMATIONS$\" \n"
           "  >\n";

    for (auto &textranges_and_pairofposinaudio : this->audiorecord.text2audio) {
      PosInTextRanges textranges = textranges_and_pairofposinaudio.first;

      QString new_line("    <segment "
                       "textranges=\"$TEXTRANGE$\" "
                       "audiorange=\"$AUDIORANGE$\" "
                       "srctext=\"$TEXT$\" "
                       "/>\n");
      new_line.replace("$TEXTRANGE$", textranges.repr());
      PosInAudioRange posinaudiorange(this->audiorecord.text2audio[textranges]);
      new_line.replace("$AUDIORANGE$", posinaudiorange.repr());
      new_line.replace("$TEXT$",
                       this->get_condensed_extracts_from_the_source_text(textranges,
                                                                         DipyDoc::condensed_extracts_length));
      res += new_line;
    }
    res += "  </audiorecord>\n";
  }

  /*............................................................................
     translation : the functions reads through this->translation.translations with sorted keys.
  ............................................................................*/
  res += "\n";

  res += "  <translation \n"
         "        description=\"$TRANSLATIONNAME$\" \n"
         "        informations=\"$TRANSLATIONINFORMATIONS$\" \n"
         "  >\n";

  for (auto &textranges_and_qstring : this->translation.translations) {
    PosInTextRanges textranges = textranges_and_qstring.first;

    QString new_line("    <segment "
                     "textranges=\"$TEXTRANGE$\" "
                     "srctext=\"$TEXT$\""
                     ">");

    new_line.replace("$TEXTRANGE$",
                      textranges.repr());
    new_line.replace("$TEXT$",
                      this->get_condensed_extracts_from_the_source_text(textranges,
                                                                        DipyDoc::condensed_extracts_length));
    res += new_line;
    res += this->translation.translations[ textranges ];
    res += "</segment>\n";
  }
  res += "  </translation>\n";

  /*............................................................................
    notes.syntagmas_aspects

$$$
  ............................................................................*/
  /*
  res += "\n";
  res += "  <syntagmas_aspects>\n";
  for (auto &syntagma_name : this->notes.syntagmas_aspects) {
    QString new_line("    <syntagma_name name=\"$NAME$\" aspect=\"$ASPECT$\" />\n");
    new_line.replace("$NAME$", syntagma_name.first);
    new_line.replace("$ASPECT$",  syntagma_name.second);
    res += new_line;
  }
  res += "  </syntagmas_aspects>\n";
  */

  /*............................................................................
    levels $$$$
  ............................................................................*/
  /*
  res += "\n";
  res += "  <levels>\n";
  for (auto &level : this->levels) {
    QString new_line("    <level number=\"$NUMBER$\" "
                     "name=\"$NAME$\" "
                     "textformat=\"$TEXTFORMAT$\" "
                     "/>\n");
    new_line.replace("$NUMBER$", QString().setNum(level.first));
    new_line.replace("$NAME$", level.second.name);
    new_line.replace("$TEXTFORMAT$", level.second.textformat.repr());
    res += new_line;
  }
  res += "  </levels>\n";
  */

  /*............................................................................
    arrows_types
  ............................................................................*/
  res += "\n";
  res += "  <arrows_types>\n";
  for (auto &arrow : this->notes.arrows_types) {
    QString new_line("    <arrow_type name=\"$NAME$\" "
                     "arrowformat=\"$ARROWFORMAT$\" "
                     "/>\n");
    new_line.replace("$NAME$", arrow.first);
    new_line.replace("$ARROWFORMAT$",  arrow.second.repr());
    res += new_line;
  }
  res += "  </arrows_types>\n";

  /*............................................................................
    notes $$$
  ............................................................................*/
  /*
  res += "\n";
  res += "  <notes>\n";

  for (auto &note_by_level : this->notes) {
    // note_by_level.first : (int)level
    // note_by_level.second : std::map<PosInTextRanges, DipyDocNote>
    for (auto &pos_and_note : note_by_level.second) {
      // pos_and_note.first : PosInTextRanges
      // pos_and_note.second : DipyDocNote
      QString new_line;
      // we simplify the output string if no 'textformatname' is defined :
      if (pos_and_note.second.textformatname.size() > 0) {
        new_line = QString("    <note level=\"$LEVEL$\" "
                           "textranges=\"$TEXTRANGES$\" "
                           "srctext=\"$SRCTEXT$\" "
                           "textformatname=\"$TEXTFORMATNAME$\" "
                           ">\n");
      } else {
        new_line = QString("    <note level=\"$LEVEL$\" "
                           "textranges=\"$TEXTRANGES$\" "
                           "srctext=\"$SRCTEXT$\" "
                           ">\n");
      }
      new_line.replace("$LEVEL$", QString().setNum(pos_and_note.second.level));
      new_line.replace("$TEXTRANGES$", pos_and_note.first.repr());
      new_line.replace("$SRCTEXT$",
                       this->get_condensed_extracts_from_the_source_text(pos_and_note.first,
                                                                         DipyDoc::condensed_extracts_length));
      new_line.replace("$TEXTFORMATNAME$", pos_and_note.second.textformatname);
      res += new_line;

      res += "      <text>" + pos_and_note.second.text + "</text>\n";

      for (auto &arrow : pos_and_note.second.arrows) {
        QString arrow_str("      <arrow target=\"$TARGET$\" srctext=\"$SRCTEXT$\">$TYPE$</arrow>\n");
        arrow_str.replace("$TYPE$", arrow.type);
        arrow_str.replace("$TARGET$", arrow.final_position.repr());
        arrow_str.replace("$SRCTEXT$",
                          this->get_condensed_extracts_from_the_source_text(arrow.final_position,
                                                                            DipyDoc::condensed_extracts_length));
        res += arrow_str;
      }

      res += "    </note>\n";
    }
  }
  res += "  </notes>\n";
  */

  /*............................................................................
    final line
  ............................................................................*/
  res += "\n";
  res += "</dipydoc>\n";

  /*............................................................................
    various replacements
  ............................................................................*/
  res.replace("$DIPYDOCVERSION$",
               QString().setNum(this->dipydocformat_version));
  res.replace("$LANGUAGEFROMTO$",
               this->languagefromto.repr());
  res.replace("$DOCTYPE$",
               this->doctype);

  res.replace("$TITLETEXT$",
               this->title.text);
  res.replace("$TITLETEXTFORMAT$",
               this->title.textformat.repr());
  res.replace("$TITLEBLOCKFORMAT$",
               this->title.blockformat.repr());

  res.replace("$INTRODUCTIONTEXT$",
               this->introduction.text);
  res.replace("$INTRODUCTIONTEXTFORMAT$",
               this->introduction.textformat.repr());
  res.replace("$INTRODUCTIONBLOCKFORMAT$",
               this->introduction.blockformat.repr());

  res.replace("$LETTRINEFILENAME$",
               this->lettrine.filename_with_fullpath);
  res.replace("$LETTRINEASPECTRATIO$",
               QString().setNum(this->lettrine.aspectratio));
  res.replace("$LETTRINEPOSITIONINTEXTFRAME$",
               this->lettrine.position_in_text_frame.repr());

  res.replace("$SOURCEEDITOR_STYLESHEET$",
               this->sourceeditor_stylesheet);
  res.replace("$SOURCEEDITOR_DEFAULTTEXTFORMAT$",
               this->sourceeditor_default_textformat.repr());
  res.replace("$SOURCEEDITOR_RMODETEXTFORMAT$",
               this->sourceeditor_rmode_textformat.repr());
  res.replace("$SOURCEEDITOR_LMODETEXTFORMAT$",
               this->sourceeditor_lmode_textformat.repr());
  res.replace("$COMMENTARYEDITOR_STYLESHEET$",
               this->commentaryeditor_stylesheet);
  res.replace("$COMMENTARYEDITOR_DEFAULTTEXTFORMAT$",
               this->commentaryeditor_textformat.repr());

  res.replace("$AUDIORECORDNAME$",
               this->audiorecord.description);
  res.replace("$AUDIORECORDINFORMATIONS$",
               this->audiorecord.informations);
  // just the filename, not the path :
  res.replace("$AUDIORECORDFILENAME$",
               QFileInfo(this->audiorecord.filename).fileName());

  res.replace("$TEXTNAME$",
               this->source_text.description);
  res.replace("$TEXTINFORMATIONS$",
               this->source_text.informations);
  res.replace("$TEXTBLOCKFORMAT$",
               this->source_text.blockformat.repr());
  // just the filename, not the path :
  res.replace("$TEXTFILENAME$",
               QFileInfo(this->source_text.filename).fileName());

  res.replace("$TRANSLATIONNAME$",
               this->translation.description);
  res.replace("$TRANSLATIONINFORMATIONS$",
               this->translation.informations);

  return res;
}

/*______________________________________________________________________________

        DipyDoc::load_a_textversion()

        This method loads the main file and the document placed in the 
        "_path/_textversion" directory.

        Beware, this method DOES NOT CHECK if the textversion really exists.
______________________________________________________________________________*/
void DipyDoc::load_a_textversion(const QString& _path,
                               unsigned int _textversion) {
  // DEBUG1 DebugMsg() << "DipyDoc::load_a_textversion() _textversion=" << _textversion;

  this->current_textversion = _textversion;

  this->clean_before_loading_a_new_textversion();

  // let's open the main file :
  this->read_mainfile(_path, _textversion);

  // text document ? let's open the text file :
  if (this->well_initialized() == true && this->doctype == QString("text")) {
    // DEBUG1 DebugMsg() << "(DipyDoc::DipyDoc) let's open" << this->source_text.filename;
    QFile src_file(this->source_text.filename);
    src_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream src_file_stream(&src_file);
    src_file_stream.setCodec("UTF-8");
    this->source_text.text = src_file_stream.readAll();
  }
}

/*______________________________________________________________________________

        DipyDoc::read_mainfile()

        Initialize "this" from the main xml file stored in "_path/X" where X
        is an integer equal to _textversion

        This method doesn't check if "path" is valid : see the ::check_path()
        method for this.

        Initialize this->_well_initialized, this->_internal_state if an error
        occurs.

        Fill "err_messages" with human-readable messages.

        (1) main file opening
        (2) xml reading : main file reading
        (3) initialization and checking
______________________________________________________________________________*/
void DipyDoc::read_mainfile(const QString& _path, unsigned int _textversion) {
  // DEBUG1 DebugMsg() << "DipyDoc::read_mainfile() : entry point;";
  // DEBUG1 DebugMsg() << " path=" << _path << " textversion=" << _textversion;

  QString msg_error;

  // DEBUG1 DebugMsg() << "DipyDoc::read_mainfile" << "path=" << _path;

  /*............................................................................
    (1) main file opening
  ............................................................................*/
  // DEBUG1 DebugMsg() << "(DipyDoc::read_mainfile) #1";
  this->path = _path;
  this->main_filename_with_fullpath = _path + \
                                      "/" + \
                                      QString::number(_textversion) + \
                                      "/" + \
                                      fixedparameters::DIPYDOC__MAIN_FILENAME;
  QFile dipydoc_main_xml_file(this->main_filename_with_fullpath);

  if (!dipydoc_main_xml_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QString msg("An error occurs while opening the main file, named '%1'");

    this->error(msg.arg(this->main_filename_with_fullpath));

    this->_well_initialized = false;
    this->_internal_state = DipyDoc::INTERNALSTATE::NOT_CORRECTLY_INITIALIZED;
    return;
  }

  /*............................................................................
    (2) xml reading : main file reading

    If an error occurs, set "xml_reading_is_ok" to false and fills "err_messages".
  ............................................................................*/
  // DEBUG1 DebugMsg() << "(DipyDoc::read_mainfile) #2";
  this->xmlreader = new QXmlStreamReader();
  this->xmlreader->setDevice(&dipydoc_main_xml_file);

  bool ok = false;

  if (this->xmlreader->readNextStartElement()) {
    if (this->xmlreader->name() == "dipydoc") {
      /*
         ok, it's a DipyDoc file : let's read and check its first token
      */
      if (this->read_mainfile__first_token() == true) {
        // ok, let's read the rest of the file :
        if (this->doctype == QString("text")) {
            ok = this->read_mainfile__doctype_text(_textversion);
        }
      }
    } else {
      /*
         not a DipyDoc file  :
      */
      this->error("This isn't a DipyDoc file : incorrect first token.", this->error_string());
      ok = false;
    }
  } else {
    /*
       not a DipyDoc file :
    */
    this->error("This isn't a DipyDoc file : nothing to read.", this->error_string());
    ok = false;
  }

  if (ok == false) {
    // DEBUG1 DebugMsg() << "DipyDoc::read_mainfile() : exit #1";
    this->_well_initialized = false;
    this->_internal_state = DipyDoc::INTERNALSTATE::NOT_CORRECTLY_INITIALIZED;

    delete this->xmlreader;
    return;
  }

  /*............................................................................
    (3) initialization and checking
  ............................................................................*/
  if (this->doctype == QString("text")) {
    ok &= this->read_mainfile__doctype_text__init_and_check();
  }

  delete this->xmlreader;

  // DEBUG1 DebugMsg() << "DipyDoc::read_mainfile" <<
  // DEBUG1               "this->_well_initialized = " << this->_well_initialized;
}

/*______________________________________________________________________________

  DipyDoc::read_mainfile__first_token()

  read the first token and initializes the object.

  return a bool (=success)
______________________________________________________________________________*/
bool DipyDoc::read_mainfile__first_token(void) {
  bool ok = true;

  /*
    let's read and check the version :
  */
  this->dipydocformat_version = this->xmlreader->attributes().value("dipydoc_version").toString().toInt();

  bool dipydoc_version_ok = (this->dipydocformat_version >= this->min_dipydocformat_version) && \
                            (this->dipydocformat_version <= this->max_dipydocformat_version);

  if (dipydoc_version_ok == false) {
    QString msg("wrong version's format : "
                "we should have %1 <= %2 <= %3, i.e. "
                "(min. version <= current version <= max. version)");
    this->_internal_state = DipyDoc::INTERNALSTATE::INCORRECT_VERSION_OF_THE_DIPYDOC;
    this->error(msg.arg(QString().setNum(this->min_dipydocformat_version),
                        QString().setNum(this->dipydocformat_version),
                        QString().setNum(this->max_dipydocformat_version)),
                 this->error_string());

    ok &= dipydoc_version_ok;
  }

  /*
    let's read and check the languages :
  */
  this->languagefromto = LanguageFromTo(this->xmlreader->attributes().value("languages").toString());
  bool languagesfromto_ok = !this->error(this->languagefromto,
                                         this->error_string(),
                                         "dipydoc:first token");
  ok &= languagesfromto_ok;

  /*
    let's read and check the doctype :
  */
  this->doctype = this->xmlreader->attributes().value("type").toString();
  bool doctype_is_ok = (fixedparameters::known_doctypes.indexOf(this->doctype) != -1);

  if (doctype_is_ok == false) {
    QString msg("incorrect document's type : accepted document's types are : %1");
    this->error(msg.arg(fixedparameters::known_doctypes.join(";")),
                this->error_string());
  }
  ok &= doctype_is_ok;
  return ok;
}

/*______________________________________________________________________________

  DipyDoc::read_mainfile__doctype_text()

    for doctype='text', read everything but the first token and initialize the
  object.

  return a bool (=success)
______________________________________________________________________________*/
bool DipyDoc::read_mainfile__doctype_text(unsigned int _textversion) {
  // DEBUG1 DebugMsg() << "(DipyDoc::read_mainfile__doctype_text) : entry point";
  bool ok = true;

  while (this->xmlreader->readNextStartElement()) {
    QString tokenname = this->xmlreader->name().toString();

    /*
      id
    */
    if (this->xmlreader->name() == "id") {
      // id's text
      this->id = this->xmlreader->readElementText();
      this->id = this->id.trimmed();
      // DEBUG1 DebugMsg() << "... id = " << this->id;
      continue;
    }

    /*
      version

      = document's version [nothing to do with the format of the dipydoc file]
    */
    if (this->xmlreader->name() == "version") {
      // version's text
      this->version = this->xmlreader->readElementText().toInt();
      // DEBUG1 DebugMsg() << "... version = " << this->version;
      continue;
    }

    /*
      textversion_description

      = string giving an idea of the level required to read the text : e.g. "C3"
    */
    if (this->xmlreader->name() == "textversion") {
      this->textversion_description = this->xmlreader->readElementText();
      // DEBUG1 DebugMsg() << "... textversion_description = " << this->textversion_description;
      continue;
    }

    /*
      title
    */
    if (this->xmlreader->name() == "title") {
      this->title.found = true;

      // title::textformat
      this->title.textformat = TextFormat(this->xmlreader->attributes().value("textformat").toString());
      ok &= !this->error(this->title.textformat, this->error_string(), QString("title:textformat"));

      // title::blockformat
      this->title.blockformat = BlockFormat(this->xmlreader->attributes().value("blockformat").toString());
      ok &= !this->error(this->title.blockformat, this->error_string(), QString("title:blockformat"));

      // title's text
      this->title.text = this->xmlreader->readElementText();
      this->title.text = this->title.text.trimmed();
      // DEBUG1 DebugMsg() << "... title = " << this->title.text;
      continue;
    }

    /*
      introduction
    */
    if (tokenname == "introduction") {
      this->introduction.found = true;

      // introduction::textformat
      this->introduction.textformat = TextFormat(this->xmlreader->attributes().value("textformat").toString());
      ok &= !this->error(this->introduction.textformat, this->error_string(),
                         QString("introduction:textformat"));

      // introduction::blockformat
      this->introduction.blockformat = BlockFormat(this->xmlreader->attributes().value("blockformat").toString());
      ok &= !this->error(this->introduction.blockformat, this->error_string(),
                         QString("introduction:blockformat"));

      // introduction's text
      this->introduction.text = this->xmlreader->readElementText();
      this->introduction.text = this->introduction.text.trimmed();
      // DEBUG1 DebugMsg() << "... introduction.text = " << this->introduction.text;
      continue;
    }

    /*
      lettrine
    */
    if (tokenname == "lettrine") {
      // DEBUG1 DebugMsg() << "... found 'lettrine' token";

      this->lettrine.found = true;

      // lettrine::positionintextframe
      QString str_pos = this->xmlreader->attributes().value("positionintextframe").toString();
      this->lettrine.position_in_text_frame = PosInTextFrameFormat(str_pos);
      ok &= !this->error(this->lettrine.position_in_text_frame, this->error_string(),
                         QString("lettrine:posintextframe"));

      // lettrine::filename
      this->lettrine.filename_with_fullpath = this->path + "/" + QString::number(_textversion) + "/" + \
                                              this->xmlreader->attributes().value("filename").toString();
      QFile lettrinefile(this->lettrine.filename_with_fullpath);
      if (!lettrinefile.open(QFile::ReadOnly)) {
        QString msg("An error occurs while reading the lettrine's file; "
                    "is the file missing ? "
                    "filename='%1'");
        ok &= !this->error(msg.arg(this->lettrine.filename_with_fullpath), this->error_string());
        this->lettrine.found = false;
      } else {
        this->lettrine.image = QImage(this->lettrine.filename_with_fullpath);
      }

      // lettrine::aspectratio
      this->lettrine.aspectratio = this->xmlreader->attributes().value("aspectratio").toInt();
      if (this->lettrine.aspectratio <= 0) {
        QString msg("the aspect ratio found for the lettrine isn't correct; "
                    "accepted values are integers greater than 0."
                    "given aspectratio = %1.");
        ok &= !this->error(msg.arg(QString().setNum(this->lettrine.aspectratio)), error_string());
      }

      this->xmlreader->skipCurrentElement();
      continue;
    }

    /*
      text
    */
    if (tokenname == "text") {
      // text::blockformat
      this->source_text.blockformat = BlockFormat(this->xmlreader->attributes().value("blockformat").toString());
      ok &= !this->error(this->source_text.blockformat, this->error_string(), QString("text:blockformat"));

      // text::description
      this->source_text.description = this->xmlreader->attributes().value("description").toString();

      // text::filename
      this->source_text.filename = this->path + \
                                   "/" + \
                                   QString::number(_textversion) + \
                                   "/" + \
                                   this->xmlreader->attributes().value("filename").toString();

      QFile textfile(this->source_text.filename);
      if (!textfile.open(QFile::ReadOnly)) {
        ok &= !this->error(QString("Missing text file named '%1'.").arg(this->source_text.filename),
                           error_string());
      }

      // text::informations
      this->source_text.informations = this->xmlreader->attributes().value("informations").toString();

      this->xmlreader->skipCurrentElement();
      // DEBUG1 DebugMsg() << "... source_text.filename = " << this->source_text.filename;
      // DEBUG1 DebugMsg() << "... source_text.description = " << this->source_text.description;
      continue;
    }

    /*
      aspect
    */
    if (tokenname == "aspect") {
      // DEBUG1 DebugMsg() << "... found 'aspect' token";

      while (this->xmlreader->readNextStartElement()) {
        // aspect::sourceeditor
        if (this->xmlreader->name() == "sourceeditor") {
          while (this->xmlreader->readNextStartElement()) {
            // aspect::sourceeditor's stylesheet
            if (this->xmlreader->name() == "stylesheet") {
              this->sourceeditor_stylesheet = this->xmlreader->readElementText();
              this->sourceeditor_stylesheet = this->sourceeditor_stylesheet.trimmed();
              continue;
            }
            // aspect::sourceeditor's default_textformat
            if (this->xmlreader->name() == "default_textformat") {
              this->sourceeditor_default_textformat = TextFormat(this->xmlreader->readElementText());
              ok &= !this->error(this->sourceeditor_default_textformat, this->error_string(),
                                 QString("aspect::sourceeditor::default_textformat"));
              continue;
            }
            // aspect::sourceeditor's rmode_textformat
            if (this->xmlreader->name() == "rmode_textformat") {
              this->sourceeditor_rmode_textformat = TextFormat(this->xmlreader->readElementText());
              ok &= !this->error(this->sourceeditor_rmode_textformat, this->error_string(),
                                 QString("aspect::sourceeditor::rmode_textformat"));
              continue;
            }
            // aspect::sourceeditor's lmode_textformat
            if (this->xmlreader->name() == "lmode_textformat") {
              this->sourceeditor_lmode_textformat = TextFormat(this->xmlreader->readElementText());
              ok &= !this->error(this->sourceeditor_lmode_textformat, this->error_string(),
                                 QString("aspect::sourceeditor::lmode_textformat"));
              continue;
            }
          }
        }

        // aspect::commentaryeditor
        if (this->xmlreader->name() == "commentaryeditor") {
          while (this->xmlreader->readNextStartElement()) {
            // aspect::commentaryeditor's stylesheet
            if (this->xmlreader->name() == "stylesheet") {
              this->commentaryeditor_stylesheet = this->xmlreader->readElementText();
              this->commentaryeditor_stylesheet = this->commentaryeditor_stylesheet.trimmed();
              continue;
            }
            // aspect::commentaryeditor's textformat
            if (this->xmlreader->name() == "textformat") {
              this->commentaryeditor_textformat = TextFormat(this->xmlreader->readElementText());
              ok &= !this->error(this->commentaryeditor_textformat, this->error_string(),
                                 QString("aspect::commentaryeditor::textformat"));
              continue;
            }
          }
        }
      }

      continue;
    }

    /*
      audiorecord
    */
    if (tokenname == "audiorecord") {
      // DEBUG1 DebugMsg() << "... found 'audiorecord' token";

      this->audiorecord.found = true;
      // audiorecord::description
      this->audiorecord.description = this->xmlreader->attributes().value("description").toString();

      // audiorecord::filename
      this->audiorecord.filename = this->path + \
                                   "/" + \
                                   QString::number(_textversion) + \
                                   "/" + \
                                   this->xmlreader->attributes().value("filename").toString();

      QFile audiofile(this->audiorecord.filename);
      if (!audiofile.open(QFile::ReadOnly)) {
        ok &= !this->error(QString("Can't open the audio record file named '%1'").arg(this->audiorecord.filename),
                           error_string());
      }

      // audiorecord::informations
      this->audiorecord.informations = this->xmlreader->attributes().value("informations").toString();

      while (this->xmlreader->readNextStartElement()) {
        // audiorecord::segment
        if (this->xmlreader->name() == "segment") {
          // audiorecord::segment::textranges
          PosInTextRanges textranges(this->xmlreader->attributes().value("textranges").toString());
          ok &= !this->error(textranges, this->error_string(),
                             QString("audiorecord::segment::textranges"));

          // audiorecord::segment::audiorange
          PosInAudioRange audiorange(this->xmlreader->attributes().value("audiorange").toString());
          ok &= !this->error(audiorange, this->error_string(),
                             QString("audiorecord::segment::audiorange"));

          this->audiorecord.text2audio[ textranges ] = PairOfPosInAudio(audiorange.first(), audiorange.second());

          this->xmlreader->skipCurrentElement();
          continue;
        }
      }
      // DEBUG1 DebugMsg() << "audiorecord.informations = " << this->audiorecord.informations;
      continue;
    }

    /*
      translation
    */
    if (tokenname == "translation") {
      // DEBUG1 DebugMsg() << "found 'translation' token";

      this->translation.found = true;
      // translation::informations
      this->translation.informations = this->xmlreader->attributes().value("informations").toString();
      // translation::description
      this->translation.description = this->xmlreader->attributes().value("description").toString();

      while (this->xmlreader->readNextStartElement()) {
        // translation::segment
        if (this->xmlreader->name() == "segment") {
          // translation::segment::textranges
          PosInTextRanges textranges(this->xmlreader->attributes().value("textranges").toString());
          ok &= !this->error(textranges, this->error_string(),
                             QString("translation::segment::textranges"));

          // translation's text
          QString text(this->xmlreader->readElementText());
          text = text.trimmed();

          this->translation.translations[ textranges ] = text;

          continue;
        }
      }
      continue;
    }

    /*
      notes.syntagmas_aspects, notes.syntagmas_levels
    */
    if (tokenname == "syntagmas_levels") {
      // DEBUG1 DebugMsg() << "... found 'syntagmas_levels' token";

      while (this->xmlreader->readNextStartElement()) {
        // syntagmas_aspects::syntagma_name
        if (this->xmlreader->name() == "syntagma_level") {
          // syntagmas_aspects::syntagma_name::name
          QString name = this->xmlreader->attributes().value("name").toString();

          // syntagmas_aspects::syntagma_name::aspect
          QString txt_aspect = this->xmlreader->attributes().value("aspect").toString();
          // syntagmas_aspects::syntagma_name::level
          int level = this->xmlreader->attributes().value("level").toString().toInt();

          // notes.syntagmas_levels[ name ]
          this->notes.syntagmas_levels[ name ] = level;

          // notes.syntagmas_aspects[ name ]
          this->notes.syntagmas_aspects[ name ] = TextFormat(txt_aspect);

          this->notes.syntagmas_aspects[ name+"+bro" ] = TextFormat(txt_aspect);

          TextFormat textformat_focused = TextFormat(txt_aspect);
          textformat_focused.modify_for_focused_appearance();
          this->notes.syntagmas_aspects[ name+"+foc" ] = textformat_focused;

          TextFormat textformat_family = TextFormat(txt_aspect);
          textformat_family.modify_for_family_appearance();
          this->notes.syntagmas_aspects[ name+"+fam" ] = textformat_family;

          TextFormat textformat_distant = TextFormat(txt_aspect);
          textformat_distant.modify_for_distant_appearance();
          this->notes.syntagmas_aspects[ name+"+distant" ] = textformat_distant;

          this->xmlreader->skipCurrentElement();
          continue;
        }
      }

      continue;
    }

    /*
      notes.syntagmas_types
    */
    if (tokenname == "syntagmas_types") {
      // DEBUG1 DebugMsg() << "... found 'syntagmas_types' token";

      while (this->xmlreader->readNextStartElement()) {
        // syntagmas_types::syntagmas_type
        if (this->xmlreader->name() == "syntagma_type") {
          // syntagmas_types::syntagmas_type::type
          QString type = this->xmlreader->attributes().value("type").toString();

          // syntagmas_types::syntagmas_type::aspect
          QString txt_aspect = this->xmlreader->attributes().value("aspect").toString();

          this->notes.syntagmas_types[ type ] = TextFormat(txt_aspect);

          this->xmlreader->skipCurrentElement();
          continue;
        }
      }

      continue;
    }

    /*
      arrows_types
    */
    if (tokenname == "arrows_types") {
      // DEBUG1 DebugMsg() << "... found 'arrows_types' token";

      while (this->xmlreader->readNextStartElement()) {
        // arrows_types::arrow_type
        if (this->xmlreader->name() == "arrow_type") {
          // arrows_types::arrow_type::name
          QString name = this->xmlreader->attributes().value("name").toString();

          // arrows_types::arrow_type::arrowformat
          ArrowFormat arrowformat(this->xmlreader->attributes().value("arrowformat").toString());
          ok &= !this->error(arrowformat,
                             this->error_string(),
                             QString("arrows_types::arrow_type::arrowformat"));

          this->notes.arrows_types[ name ] = arrowformat;

          this->xmlreader->skipCurrentElement();
          continue;
        }
      }

      continue;
    }

    /*
      notes
    */
    if (tokenname == "notes") {
      // DEBUG1 DebugMsg() << "... found 'notes' token";

      ok &= this->read_mainfile__doctype_text__syntagma(nullptr);
      if (ok == true) {
        this->notes.found = true;
      }
    }
  }  // ... while (this->xmlreader->readNextStartElement())

  // DEBUG1 DebugMsg() << "(DipyDoc::read_mainfile__doctype_text) : exit point; ok=" << ok;
  return ok;
}

/*______________________________________________________________________________

  DipyDoc::read_mainfile__doctype_text__syntagma

  Read the syntagmas' definitions inside <notes></notes>.

  Recursive function able to read every token inside <notes></notes>.
______________________________________________________________________________*/
bool DipyDoc::read_mainfile__doctype_text__syntagma(Syntagma * father) {
  Syntagma* current_father = father;
  bool ok = true;

  while (this->xmlreader->readNextStartElement()) {
    QString tag_name = this->xmlreader->name().toString();

    if (this->notes.syntagmas_levels.find(tag_name) != this->notes.syntagmas_levels.end()) {
      PosInTextRanges textranges(this->xmlreader->attributes().value("textranges").toString());
      ok &= !this->error(textranges,
                         this->error_string(),
                         QString("notes::note::textranges =%1;"
                                 "internalstate=%2").arg(textranges.repr(),
                                                         QString().setNum(textranges.internal_state())));

      QString type(this->xmlreader->attributes().value("type").toString());

      // let's insert a new syntagma object in this->notes.syntagmas;
      // 'textnote', 'highest_ancestor' and 'ancestors' will be defined later.
      Syntagma* new_syntagma = new Syntagma(current_father,
                                            nullptr,
                                            QList<Syntagma*>(),
                                            textranges,
                                            tag_name,
                                            type,
                                            QString(""));
      int level = this->notes.syntagmas_levels.at(tag_name);

      this->notes._syntagmas.push_back(std::shared_ptr<Syntagma>(new_syntagma));
      if (this->notes.syntagmas.find(level) == this->notes.syntagmas.end()) {
        this->notes.syntagmas[level] = std::map<PosInTextRanges, Syntagma*>();
      }
      this->notes.syntagmas[level][textranges] = new_syntagma;

      // let's add this new soon to its "father" :
      if (father != nullptr) {
        father->soons.push_back(new_syntagma);
      }

      current_father = new_syntagma;

      ok &= this->read_mainfile__doctype_text__syntagma(current_father);

      current_father = current_father->father;

    } else {
      if (tag_name == "note") {
        if (current_father == nullptr) {
          // error : pending 'textnote' tag.
          ok &= !this->error(QString("[DipyDoc::read_mainfile__doctype_text__syntagma]"
                                     "pending 'textnote' tag."),
                             this->error_string());
        } else {
          // let's add the textnote to its father :
          current_father->textnote = this->xmlreader->attributes().value("content").toString();

          this->xmlreader->skipCurrentElement();
        }
      } else {
        if (tag_name == "arrow") {
          if (current_father == nullptr) {
            // error : pending 'arrow' tag.
            ok &= !this->error(QString("[DipyDoc::read_mainfile__doctype_text__syntagma]"
                                       " pending 'arrow' tag."),
                               this->error_string());
          } else {
            // let's add the arrow to its father :
            QString arrow_type(this->xmlreader->attributes().value("type").toString());
            PosInTextRanges arrow_final_position(this->xmlreader->attributes().value("dest").toString());
            current_father->arrows.push_back(ArrowTarget(arrow_type, arrow_final_position));

            this->xmlreader->skipCurrentElement();
          }
        } else {
          // error : unknown tag name :
          ok &= !this->error(QString("[DipyDoc::read_mainfile__doctype_text__syntagma]"
                                     " unknown tag name=%1").arg(tag_name),
                             this->error_string());
        }
      }
    }
  }

  return ok;
}

/*______________________________________________________________________________

  DipyDoc::read_mainfile__doctype_text__init_and_check()

  Initialization and checking for "text" dipydoc.

        (1) secondary initializations
            (1.1) initialization of "audiorecord.audio2text"
            (1.2) initialization of the Syntagma::'highest_ancestor' pointers
            (1.3) initialization of the Syntagma::ancestors.
        (2) checks
            (2.1) is audiorecord.text2audio correctly initialized ?
            (2.2) is audiorecord.audio2text correctly initialized ?
            (2.3) is translation correctly initialized ?
            (2.4) is the text's filename an empty string ?
            (2.5) are the notes' levels' number defined ?
            (2.6) are the notes' aspects defined ?
            (2.7) are the notes' arrows' types defined ?
            (2.8) are the notes' types defines ?
        (3) initializaton of _well_initialized

________________________________________________________________________________*/
bool DipyDoc::read_mainfile__doctype_text__init_and_check(void) {
  bool ok = true;

  /*............................................................................
    (1) secondary initializations
  ............................................................................*/
  // DEBUG1 DebugMsg() << "(DipyDoc::read_mainfile__doctype_text__init_and_check) #1";

  /*............................................................................
    (1.1) initialization of "audiorecord.audio2text"
  ............................................................................*/
  if (this->audiorecord.found == true) {
    this->audiorecord.audio2text = PosInAudio2PosInText(this->audiorecord.text2audio);
  } else {
    // we clear the audio2text object so that its _well_initialized flag will be set to "true" :
    this->audiorecord.audio2text.clear();
  }

  /*............................................................................
    (1.2) initialization of the Syntagma::highest_ancestor pointers
  ............................................................................*/
  // for each syntagma, the following loop searches its highest father :
  for (auto & syntagma : this->notes._syntagmas) {
    Syntagma* current_forefather = syntagma->father;
    while (current_forefather != nullptr) {
      if (current_forefather->father == nullptr) {
        break;
      } else {
        current_forefather = current_forefather->father;
      }
    }
    syntagma->highest_ancestor = current_forefather;
  }

  /*............................................................................
    (1.3) initialization of the Syntagma::ancestors.
  ............................................................................*/
  for (auto & syntagma : this->notes._syntagmas) {
    Syntagma* current_forefather = syntagma->father;
    while (current_forefather != nullptr) {
      syntagma->ancestors.push_back(current_forefather);
      current_forefather = current_forefather->father;
    }
  }

  /*............................................................................
    (2) checks
  ............................................................................*/
  // DEBUG1 DebugMsg() << "(DipyDoc::read_mainfile__doctype_text__init_and_check) #2";

  /*............................................................................
    (2.1) is audiorecord.text2audio correctly initialized ?
  ............................................................................*/
  if (this->audiorecord.found == true && \
      this->audiorecord.text2audio.well_initialized() == false) {
    QString msg = "text2audio isn't correctly initialized"
                  "PosInText2PosInAudio error message = %1.";
    ok &= !this->error(msg.arg(QString().setNum(this->audiorecord.text2audio.internal_state())));
  }

  /*............................................................................
    (2.2) is audio2text correctly initialized ?
  ............................................................................*/
  if (this->audiorecord.found == true && \
      this->audiorecord.audio2text.well_initialized() == false) {
    QString msg = "audio2text isn't correctly initialized"
                  "PosInAudio2PosInText error message = %1.";
    ok &= !this->error(msg.arg(QString().setNum(this->audiorecord.audio2text.internal_state())));
  }

  /*............................................................................
    (2.3) is translation correctly initialized ?
  ............................................................................*/
  if (this->translation.translations.well_initialized() == false) {
    QString msg = "translation.translations isn't correctly initialized"
                  "PosInText2Str error message = %1.";
    ok &= !this->error(msg.arg(QString().setNum(this->translation.translations.internal_state())));
  }

  /*............................................................................
    (2.4) is the text's filename an empty string ?
  ............................................................................*/
  if (this->source_text.filename.length() == 0) {
    QString msg = "Empty text's filename";
    ok &= !this->error(msg);
  }

  /*............................................................................
    (2.5) are the notes' levels' number defined ? $$$
  ............................................................................*/
  /*
  for (auto &note_by_level : this->notes) {
    // note_by_level.first : (int)level
    // note_by_level.second : std::map<PosInTextRanges, DipyDocNote>
    if (this->levels.find(note_by_level.first) == this->levels.end()) {
      QString msg = "A note is defined with an unknown level; "
                    "level=%i .";
      ok = !this->error(msg.arg(QString().setNum(note_by_level.first)));
    }
  }
  */

  /*............................................................................
    (2.6) are the notes' aspects defined ? $$$$$$
  ............................................................................*/
  /*
  for (auto &note_by_level : this->notes) {
    // note_by_level.first : (int)level
    // note_by_level.second : std::map<PosInTextRanges, DipyDocNote>
    for (auto &pos_and_note : note_by_level.second) {
      // pos_and_note.first : PosInTextRanges
      // pos_and_note.second : DipyDocNote
      if ((pos_and_note.second.textformatname.size() != 0) && \
          (this->textformats.find(pos_and_note.second.textformatname) == this->textformats.end())) {
           QString msg = "A note is defined with an unknown textformat's name; "
                         "textformat='%1' .";
           ok = !this->error(msg.arg(pos_and_note.second.textformatname));
      }
    }
  }
  */

  /*............................................................................
    (2.7) are the notes' arrows' types defined ? $$$
  ............................................................................*/
  /*
  for (auto &note_by_level : this->notes) {
    // note_by_level.first : (int)level
    // note_by_level.second : std::map<PosInTextRanges, DipyDocNote>
    for (auto &pos_and_note : note_by_level.second) {
      // pos_and_note.first : PosInTextRanges
      // pos_and_note.second : DipyDocNote
      for (auto &arrow_in_a_note : pos_and_note.second.arrows) {
        if (this->arrows.find(arrow_in_a_note.type) == this->arrows.end()) {
           QString msg = "A note's arrow is defined with an unknown type; "
                         "type='%1' .";
           ok = !this->error(msg.arg(arrow_in_a_note.type));
        }
      }
    }
  }
  */

  /*............................................................................
    (2.8) are the notes' types defines ?
  ............................................................................*/
  for (auto & syntagma : this->notes._syntagmas) {
    if (syntagma->type.size() > 0 &&
        this->notes.syntagmas_types.find(syntagma->type) ==  this->notes.syntagmas_types.end()) {
      QString msg = "unknown syntagmas' type '%1' defined in name='%2'.";
      ok &= !this->error(msg.arg(syntagma->type,
                                 syntagma->name));
    }
  }


  /*............................................................................
    (3) initializaton of _well_initialized and of _internal_state.
  ............................................................................*/
  // DEBUG1 DebugMsg() << "(DipyDoc::read_mainfile__doctype_text__init_and_check) #3";
  if (ok == false) {
    this->_well_initialized = false;
    this->_internal_state = DipyDoc::INTERNALSTATE::NOT_CORRECTLY_INITIALIZED;
  }

  // DEBUG1 DebugMsg() << "(DipyDoc::read_mainfile__doctype_text__init_and_check) notes=\n"  << this->notes.repr();
  // DEBUG1 DebugMsg() << "(DipyDoc::read_mainfile__doctype_text__init_and_check)"
  // DEBUG1            << "_well_initialized =" << this->_well_initialized;

  return ok;
}

/*______________________________________________________________________________

        DipyDoc::read_menu_name

        Initialize "this->menu_name" from the "menu name" file.

        This method doesn't check if "path" is valid : see the ::check_path()
        method for this.

        Initialize this->_well_initialized, this->_internal_state if an error
        occurs.
________________________________________________________________________________*/
void DipyDoc::read_menu_name(const QString& _path) {
  this->menu_name = MenuNames::read_menu_name_from_a_file_within_a_directory(_path);

  // is the "menu name" empty ?
  if (this->menu_name.size() == 0) {
    QString msg("Empty menu name are not allowed.");
    this->error(msg);

    this->_well_initialized = false;
    this->_internal_state = DipyDoc::INTERNALSTATE::NOT_CORRECTLY_INITIALIZED;
    return;
  }

  // DEBUG1 DebugMsg() << "(DipyDoc::read_menu_name) menu name = " << this->menu_name;
}

/*______________________________________________________________________________

   DipyDoc::set_internal_name()

   Initialize this->internal_name from this->menu_name

   This function created name that can be used whin calls to setStyleSheet() :
   the only characters accepted are "n_" + 0-9 + a-f.
________________________________________________________________________________*/
void DipyDoc::set_internal_name(void) {
  QCryptographicHash hash(QCryptographicHash::Md5);
  hash.addData("n_");
  hash.addData(this->menu_name.toUtf8());
  this->internal_name = hash.result().toHex();

  // DEBUG1 DebugMsg() << "DipyDoc::set_internal_name = " << this->internal_name;
}

/*______________________________________________________________________________

   DipyDoc::set_qsettings_name()

   Initialize this->qsettings_name from this->menu_name

   See http://qt-project.org/doc/qt-5/QSettings.html for a list of limitations
   due to platform limitations.
________________________________________________________________________________*/
void DipyDoc::set_qsettings_name(void) {
  this->qsettings_name = this->menu_name;
  this->qsettings_name.replace("\\", "_");
  this->qsettings_name.replace("/", "_");

  // DEBUG1 DebugMsg() << "DipyDoc::set_qsettings_name = " << this->qsettings_name;
}

/*______________________________________________________________________________

   DipyDoc::set_number_of_textversions()

   Initialize this->number_of_textversions, i.e. give the number of versions
   of the same text available in _path.

   Return true if this->number_of_textversions is greater or equal to 1 and smaller
   or equal to 10.
________________________________________________________________________________*/
bool DipyDoc::set_number_of_textversions(const QString& _path) {
  /*
    main loop : the function searches _path/0, _path/1, ...
  */
  this->number_of_textversions = 0;

  bool stop = false;
  while (stop == false) {
    QString path0 = _path + "/" + QString::number(this->number_of_textversions);
    QFileInfo path_info0 = QFileInfo(path0);

    if (path_info0.exists() == false) {
      stop = true;
    } else {
      this->number_of_textversions++;
    }
  }

  // DEBUG1 DebugMsg() << "DipyDoc::set_number_of_textversions() exit point";
  // DEBUG1 DebugMsg() << "this->number_of_textversions=" << this->number_of_textversions;

  // the function returns the expected boolean :
  return (this->number_of_textversions > 0) && (this->number_of_textversions < 10);
}

/*______________________________________________________________________________

   DipyDoc::text2audio_contains(PosInText x0)

   return the text ranges and the audio positions (from, to) matching the
   'x0' character.

   If nothing matches <pos>, the first object (PosInTextRanges) is empty, the
   second (PairOfPosInAudio) being set to (0, 0).
________________________________________________________________________________*/
PTRangesAND2PosAudio DipyDoc::text2audio_contains(PosInText x0) const {
  PosInTextRanges posintext = this->audiorecord.text2audio.contains(x0);

  if (posintext.is_empty() == true) {
    return PTRangesAND2PosAudio(posintext,
                                PairOfPosInAudio(0, 0));
  } else {
    return PTRangesAND2PosAudio(posintext,
                                this->audiorecord.text2audio[posintext]);
  }
}

/*______________________________________________________________________________

   DipyDoc::translation_contains(PosInText x0)

   $$$ l'intérêt d'une telle fonction est très douteux !!! (voir aussi la suivante)
________________________________________________________________________________*/
PosInTextRanges DipyDoc::translation_contains(PosInText x0) const {
  return this->translation.translations.contains(x0);
}

/*______________________________________________________________________________

   DipyDoc::translation_contains(PosInText x0, PosInText x1)

     This function returns a PosInTextRanges object although the
   PosInText2Str::contains(x0,x1) method returns a vector : this vector is
   transformed into a PosInTextRanges object thanks to the
   VectorPosInTextRanges::toPosInTextRanges() method.
________________________________________________________________________________*/
PosInTextRanges DipyDoc::translation_contains(PosInText x0, PosInText x1) const {
  return this->translation.translations.contains(x0, x1).toPosInTextRanges();
}
