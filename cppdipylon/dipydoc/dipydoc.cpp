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

    ❏Dipylon❏ : dipydoc/dipydoc.cpp

    See dipydoc.h for the documentation

    ____________________________________________________________________________

    expected files :

    o text file : a bunch of pure UTF-8/unicode text

    o main file : see DIPYDOC_XMLFORMAT in the documentation

*******************************************************************************/

#include "dipydoc/dipydoc.h"

/*______________________________________________________________________________

        DipyDoc::constructor from a "_path" : initialize "this" from the files
                                             stored in "_path"

        See above for a description of the expected files.

        Fill "err_messages" with human-readable messages.

______________________________________________________________________________*/
DipyDoc::DipyDoc(const QString& _path) {
  qDebug() << "DipyDoc::DipyDoc from " << _path;

  this->clear();

  // does the path leads to the expected files ?
  if (this->check_path(_path) == false) {
    qDebug() << "DipyDoc::DipyDoc" << "problem with the path =" << _path;
    this->_well_initialized = false;
    this->_internal_state = DipyDoc::INTERNALSTATE::NOT_CORRECTLY_INITIALIZED;
    return;
  }

  // let's open the main file :
  this->init_from_xml(_path);

  // let's open the text file :
  if( this->well_initialized() == true ) {
    QFile src_file(this->source_text.filename);
    src_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream src_file_stream(&src_file);
    src_file_stream.setCodec("UTF-8");
    this->source_text.text = src_file_stream.readAll();
  }
}

/*______________________________________________________________________________

  DipyDoc::arrows_repr

  Return a string which is a representation of this->arrows
______________________________________________________________________________*/
QString DipyDoc::arrows_repr(void) const {
  QString res("");
  for (auto &arrow : this->arrows) {
    res += QString("\n  name='%1' - arrowformat='%2'").arg(arrow.first,
                                                           arrow.second.repr());
    }
  return res;
}

/*______________________________________________________________________________

        DipyDoc::check_path() : check if _path leads to the expected files.

        Return false if an error occurs, or true if everything's ok.

        tests :

        o does "_path" exists ?
        o is "_path" a directory ?
        o does the file "_path/text" exists ?
        o does the file "_path/main.xml" exists ?
______________________________________________________________________________*/
bool DipyDoc::check_path(const QString& _path) {
  // does "_path" exists ?
  QFileInfo path_info = QFileInfo(_path);
  if (path_info.exists() == false) {
    QString msg(QString("An error occured while opening the main file : the path '%1' doesn't exist").arg(_path));
    this->_internal_state = DipyDoc::INTERNALSTATE::THE_GIVENPATH_DOES_NOT_EXIST;
    this->error(msg);
    return false;
  }

  // is "_path" a directory ?
  if (path_info.isFile() == true) {
    QString msg(QString("An error occured while opening the main file : the path '%1' is not a directory.").arg(_path));
    this->_internal_state = DipyDoc::INTERNALSTATE::THE_GIVENPATH_IS_NOT_A_DIRECTORY;
    this->error(msg);
    return false;
  }

  // does the main file exist ?
  QFileInfo main_info = QFileInfo(_path + "/" + this->MAIN_FILENAME);
  if (main_info.exists() == false) {
    QString msg(QString("An error occured while opening the main file : "
                        "the main file files %1 doesn't exist in %2.").arg(this->MAIN_FILENAME, _path));
    this->error(msg);
    return false;
  }

  return true;
}

/*______________________________________________________________________________

        DipyDoc::clear()

______________________________________________________________________________*/
void DipyDoc::clear(void) {
  this->_well_initialized = false;
  this->_internal_state = DipyDoc::INTERNALSTATE::NOT_YET_INITIALIZED;

  this->doctype = QString("");

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

  this->textformats.clear();
  this->arrows.clear();
  this->levels.clear();

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
                         "Please replace this Dipydoc by another one.");
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
  QString msg(QString("An error occured by reading the main file : msg=\"%1\";.").arg(_msg));
  this->err_messages.append(msg);
  qDebug() << msg;

  return true;  // since this function has been called, there must be an error !
}
bool DipyDoc::error(const QString& _msg, const QString& _error_string) {
  QString msg(QString("An error occured by reading the main file : msg=\"%1\"; error_string()=\"%2\".").arg(_msg, _error_string));
  this->err_messages.append(msg);
  qDebug() << msg;

  return true;  // since this function has been called, there must be an error !
}
// full function, for any object :
template<class T> bool DipyDoc::error(const T& object, const QString& _error_string, const QString& where) {
  // is there an error in "object" ?
  bool ok = object.well_initialized();

  if (ok == false) {
    QString msg(QString("An error occured by reading the main file : error_string=\"%1\"; where=\"%2\".").arg(_error_string, where));
    this->err_messages.append(msg);
    qDebug() << msg;
  }

  return ok;
}

/*______________________________________________________________________________

  DipyDoc::error_string()

______________________________________________________________________________*/
QString DipyDoc::error_string(const QXmlStreamReader& xmlreader) {
  return QString("%1\nLine %2, column %3").arg(xmlreader.errorString(),
                                               QString().setNum(xmlreader.lineNumber()),
                                               QString().setNum(xmlreader.columnNumber()));
}

/*______________________________________________________________________________

        DipyDoc::get_condensed_extracts_from_the_source_text

        Return from this->source_text the extracts whose position is given
        in "positions".

        o "maxlength" is the maximal length of each segment, not of the whole
          string returned.
______________________________________________________________________________*/
QString DipyDoc::get_condensed_extracts_from_the_source_text(PosInTextRanges positions, int maxlength) const {
  QString res;

  for (auto &textrange : positions) {
    QString substring = this->source_text.text.mid(static_cast<int>(textrange.first),
                                                    static_cast<int>(textrange.second - textrange.first));

    if (substring.length() > maxlength) {
      int left_length = (maxlength / 2)-3;
      int right_length = maxlength - left_length;
      substring = substring.left(left_length) + "[…]" + substring.right(right_length);
    }
    res += substring;
    res += "//";
  }

  // removing the last '//' :
  res.chop(2);

  return res;
}

/*______________________________________________________________________________

        DipyDoc::get_xml_repr

        Return an xml-string describing the current state of "this" and add :

        o a note about the file being automatically generated.
        o the extracts corresponding to the 'srctext' token.

______________________________________________________________________________*/
QString DipyDoc::get_xml_repr(void) const {
  QString res;
  VectorPosInTextRanges list_of_posintextranges;

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
  res += "      <karaoke_textformat>$SOURCEEDITOR_KARAOKETEXTFORMAT$"
         "</karaoke_textformat>\n";
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
    list_of_posintextranges.clear();
    res += "  <audiorecord \n"
           "        description=\"$AUDIORECORDNAME$\" \n"
           "        filename=\"$AUDIORECORDFILENAME$\" \n"
           "        informations=\"$AUDIORECORDINFORMATIONS$\" \n"
           "  >\n";

      for (auto &textrange : this->audiorecord.text2audio) {
        list_of_posintextranges.vposintextranges.push_back(textrange.first);
      }
      list_of_posintextranges.sort();
      for (auto &textranges : list_of_posintextranges.vposintextranges) {
        QString new_line("    <segment "
                         "textranges=\"$TEXTRANGE$\" "
                         "audiorange=\"$AUDIORANGE$\" "
                         "srctext=\"$TEXT$\" "
                         "/>\n");
        new_line.replace("$TEXTRANGE$", textranges.repr());
        PosInAudioRange posinaudiorange(this->audiorecord.text2audio[textranges]);
        new_line.replace("$AUDIORANGE$", posinaudiorange.repr());
        new_line.replace("$TEXT$",  this->get_condensed_extracts_from_the_source_text(textranges, 30));
        res += new_line;
      }
    res += "  </audiorecord>\n";
  }

  /*............................................................................
     translation : the functions reads through this->translation.translations with sorted keys.
  ............................................................................*/
  res += "\n";
  list_of_posintextranges.clear();
  res += "  <translation \n"
         "        description=\"$TRANSLATIONNAME$\" \n"
         "        informations=\"$TRANSLATIONINFORMATIONS$\" \n"
         "  >\n";
  for (auto &textrange : this->translation.translations) {
    list_of_posintextranges.vposintextranges.push_back(textrange.first);
  }
  list_of_posintextranges.sort();

  for (auto &textranges : list_of_posintextranges.vposintextranges) {
    QString new_line("    <segment "
                     "textranges=\"$TEXTRANGE$\" "
                     "srctext=\"$TEXT$\""
                     ">");

    new_line.replace("$TEXTRANGE$",
                      textranges.repr());
    new_line.replace("$TEXT$",
                      this->get_condensed_extracts_from_the_source_text(textranges, 30));
    res += new_line;
    res += this->translation.translations[ textranges ];
    res += "</segment>\n";
  }
  res += "  </translation>\n";

  /*............................................................................
    textformats
  ............................................................................*/
  res += "\n";
  res += "  <textformats>\n";
  for (auto &textformat : this->textformats) {
    QString new_line("    <textformat name=\"$NAME$\" aspect=\"$ASPECT$\" />\n");
    new_line.replace("$NAME$", textformat.first);
    new_line.replace("$ASPECT$",  textformat.second);
    res += new_line;
  }
  res += "  </textformats>\n";

  /*............................................................................
    levels
  ............................................................................*/
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

  /*............................................................................
    arrows
  ............................................................................*/
  res += "\n";
  res += "  <arrows>\n";
  for (auto &arrow : this->arrows) {
    QString new_line("    <arrow name=\"$NAME$\" "
                     "arrowformat=\"$ARROWFORMAT$\" "
                     "/>\n");
    new_line.replace("$NAME$", arrow.first);
    new_line.replace("$ARROWFORMAT$",  arrow.second.repr());
    res += new_line;
  }
  res += "  </arrows>\n";

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
  res.replace("$SOURCEEDITOR_KARAOKETEXTFORMAT$",
               this->sourceeditor_karaoke_textformat.repr());
  res.replace("$COMMENTARYEDITOR_STYLESHEET$",
               this->commentaryeditor_stylesheet);
  res.replace("$COMMENTARYEDITOR_DEFAULTTEXTFORMAT$",
               this->commentaryeditor_textformat.repr());

  res.replace("$AUDIORECORDNAME$",
               this->audiorecord.name);
  res.replace("$AUDIORECORDINFORMATIONS$",
               this->audiorecord.informations);
  // just the filename, not the path :
  res.replace("$AUDIORECORDFILENAME$",
               QFileInfo(this->audiorecord.filename).fileName());

  res.replace("$TEXTNAME$",
               this->source_text.name);
  res.replace("$TEXTINFORMATIONS$",
               this->source_text.informations);
  res.replace("$TEXTBLOCKFORMAT$",
               this->source_text.blockformat.repr());
  // just the filename, not the path :
  res.replace("$TEXTFILENAME$",
               QFileInfo(this->source_text.filename).fileName());

  res.replace("$TRANSLATIONNAME$",
               this->translation.name);
  res.replace("$TRANSLATIONINFORMATIONS$",
               this->translation.informations);

  return res;
}

/*______________________________________________________________________________

        DipyDoc::init_from_xml()

        Initialize "this" from the file(s) stored in "_path" and return a (bool)success.
        This method doesn't check if "path" is valid : see the ::check_path()
        method for this.

        Fill "err_messages" with human-readable messages.

        (1) clear "this"
        (2) main file opening
        (3) xml reading : main file reading
        (4) secondary initializations
            (4.1) initialization of "audiorecord.audio2text"
            (4.2) "number_of_chars_before_source_text" is not initialized here
        (5) checks
            (5.1) is audiorecord.text2audio correctly initialized ?
            (5.2) is audiorecord.audio2text correctly initialized ?
            (5.3) is translation correctly initialized ?
        (6) initializaton of _well_initialized

______________________________________________________________________________*/
void DipyDoc::init_from_xml(const QString& _path) {
  QString msg_error;

  /*............................................................................
    (1) clear "this"
  ............................................................................*/
  this->clear();

  qDebug() << "DipyDoc::init_from_xml" << "path=" << _path;

  /*............................................................................
    (2) main file opening
  ............................................................................*/
  this->path = _path;
  this->main_filename_with_fullpath = _path + "/" + this->MAIN_FILENAME;
  QFile dipydoc_main_xml_file(this->main_filename_with_fullpath);

  if (!dipydoc_main_xml_file.open(QIODevice::ReadOnly | QIODevice::Text)) {

    QString msg("An error occurs while opening the main file, named '%1'");

    this->error(msg.arg(this->main_filename_with_fullpath));

    this->_internal_state = DipyDoc::INTERNALSTATE::NOT_CORRECTLY_INITIALIZED;
    this->_well_initialized = false;
    return;
  }

  /*............................................................................
    (3) xml reading : main file reading

    If an error occurs, set "xml_reading_is_ok" to false and fills "err_messages".
  ............................................................................*/
  QXmlStreamReader xmlreader;
  xmlreader.setDevice(&dipydoc_main_xml_file);

  bool ok = false;
  if (xmlreader.readNextStartElement()) {
    if (xmlreader.name() == "dipydoc") {
      /*
         ok, it's a DipyDoc file : let's read and check its first token
      */
      if (this->init_from_xml__read_first_token(xmlreader) == true) {
        // ok, let's read the rest of the file :
        ok = this->init_from_xml__read_the_rest_of_the_file(xmlreader);
      }
    }
    else {
      /*
         not a DipyDoc file :
      */
      this->error( "This isn' a DipyDoc file : incorrect first token.", this->error_string(xmlreader) );

      this->_internal_state = DipyDoc::INTERNALSTATE::NOT_CORRECTLY_INITIALIZED;
      this->_well_initialized = false;
    }
  }

  if( ok == false ) {
    return;
  }

  /*............................................................................
    (4) secondary initializations
  ............................................................................*/

  /*............................................................................
    (4.1) initialization of "audiorecord.audio2text"
  ............................................................................*/
  if (this->audiorecord.found == true) {
    this->audiorecord.audio2text = PosInAudio2PosInText(this->audiorecord.text2audio);
  } else {
    // we clear the audio2text object so that its _well_initialized flag will be set to "true" :
    this->audiorecord.audio2text.clear();
  }

  /*............................................................................
    (4.2) "number_of_chars_before_source_text" is not initialized here

    The first attempt to compute "number_of_chars_before_source_text was doubtfull :

      this->source_text.number_of_chars_before_source_text = 0;
      if (this->title.found == true) {
        this->source_text.number_of_chars_before_source_text += this->title.text.length();
      }
      if (this->introduction.found == true) {
        this->source_text.number_of_chars_before_source_text += this->introduction.text.length();
      }
      if (this->lettrine.found == true) {
        this->source_text.number_of_chars_before_source_text += 1;
      }

    ... the main problem was that it's difficult to know how is the lettrine's
    image coded into the text. The result was ok but I can not trust this
    code : how will Qt work on different architectures ? So I decided to ask
    SourceEditor::load_text() to initialize "number_of_chars_before_source_text"
    by simply incrementing a cursor's position as the document is filled.
  ............................................................................*/

  /*............................................................................
    (5) checks
  ............................................................................*/

  /*............................................................................
    (5.1) is audiorecord.text2audio correctly initialized ?
  ............................................................................*/
  if (this->audiorecord.found == true && \
      this->audiorecord.text2audio.well_initialized() == false) {
    QString msg = "text2audio isn't correctly initialized"
                  "PosInText2PosInAudio error message = %1.";
    this->error( msg.arg(QString().setNum(this->audiorecord.text2audio.internal_state()) ));
  }

  /*............................................................................
    (5.2) is audio2text correctly initialized ?
  ............................................................................*/
  if (this->audiorecord.found == true && \
      this->audiorecord.audio2text.well_initialized() == false) {
    QString msg = "audio2text isn't correctly initialized"
                  "PosInAudio2PosInText error message = %1.";
    this->error( msg.arg(QString().setNum(this->audiorecord.audio2text.internal_state()) ));
  }

  /*............................................................................
    (5.3) is translation correctly initialized ?
  ............................................................................*/
  if (this->translation.translations.well_initialized() == false) {
    QString msg = "translation.translations isn't correctly initialized"
                  "PosInText2Str error message = %1.";
    this->error( msg.arg(QString().setNum(this->translation.translations.internal_state()) ));
  }

  /*............................................................................
    (6) initializaton of _well_initialized
  ............................................................................*/
  this->_well_initialized = ok;

  if( this->_well_initialized == false ) {
    this->_internal_state = DipyDoc::INTERNALSTATE::NOT_CORRECTLY_INITIALIZED;
  }
  else {
    this->_internal_state = DipyDoc::INTERNALSTATE::OK;
  }

  qDebug() << "(DipyDoc::init_from_xml) levels=" << this->levels_repr();

  qDebug() << "(DipyDoc::init_from_xml) arrows=" << this->arrows_repr();

  qDebug() << "(DipyDoc::init_from_xml) notes=";
  qDebug() << this->notes.repr();

  qDebug() << "DipyDoc::init_from_xml" << \
           "xml:this->_well_initialized = " << this->_well_initialized;
}

/*______________________________________________________________________________

  DipyDoc::init_from_xml__read_first_token()

  read the first token and initializes the object.

  return a bool (=success)
______________________________________________________________________________*/
bool DipyDoc::init_from_xml__read_first_token(QXmlStreamReader& xmlreader) {

  bool ok = true;

  /*
    let's read and check the version :
  */
  this->dipydocformat_version = xmlreader.attributes().value("dipydoc_version").toString().toInt();

  bool dipydoc_version_ok = (this->dipydocformat_version >= this->min_dipydocformat_version) && \
                            (this->dipydocformat_version <= this->max_dipydocformat_version);

  if( dipydoc_version_ok == false ) {
    QString msg("wrong version's format : "
                "we should have (min. version))%1 <= (version read)%2 <= (max. version)%3");
    this->_internal_state = DipyDoc::INTERNALSTATE::INCORRECT_VERSION_OF_THE_DIPYDOC;
    this->error( msg.arg(this->min_dipydocformat_version,
                         this->dipydocformat_version,
                         this->max_dipydocformat_version),
                 this->error_string(xmlreader) );

  ok &= dipydoc_version_ok;
  }

  /*
    let's read and check the languages :
  */
  this->languagefromto = LanguageFromTo(xmlreader.attributes().value("languages").toString());
  bool languagesfromto_ok = this->error( this->languagefromto, this->error_string(xmlreader), "dipydoc:first token" );
  ok &= languagesfromto_ok;

  /*
    let's read and check the doctype :
  */
  this->doctype = xmlreader.attributes().value("type").toString();
  bool doctype_is_ok = (fixedparameters::known_doctypes.indexOf(this->doctype) != -1);

  if( doctype_is_ok == false ) {
    QString msg("incorrect document's type : accepted document's types are : %1");
    this->error( msg.arg( fixedparameters::known_doctypes.join(";")),
                 this->error_string(xmlreader) );
  }

  ok &= doctype_is_ok;

  return ok;
}

/*______________________________________________________________________________

  DipyDoc::init_from_xml__read_the_rest_of_the_file()

  read everything but the first token and initializes the object.

  return a bool (=success)
______________________________________________________________________________*/
bool DipyDoc::init_from_xml__read_the_rest_of_the_file(QXmlStreamReader& xmlreader) {

 bool ok = true;

 while (xmlreader.readNextStartElement()) {
   QString tokenname = xmlreader.name().toString();

   /*
     title
   */
   if (xmlreader.name() == "title") {
     this->title.found = true;

     // title::textformat
     this->title.textformat = TextFormat(xmlreader.attributes().value("textformat").toString());
     ok &= this->error(this->title.textformat, this->error_string(xmlreader), QString("title:textformat"));

     // title::blockformat
     this->title.blockformat = BlockFormat(xmlreader.attributes().value("blockformat").toString());
     ok &= this->error(this->title.blockformat, this->error_string(xmlreader), QString("title:blockformat"));

     // title::text
     this->title.text = xmlreader.readElementText();

     continue;
  }

   /*
     introduction
   */
   if (tokenname == "introduction") {
     this->introduction.found = true;

     // introduction::textformat
     this->introduction.textformat = TextFormat(xmlreader.attributes().value("textformat").toString());
     ok &= this->error(this->introduction.textformat, this->error_string(xmlreader),
                       QString("introduction:textformat"));

     // introduction::blockformat
     this->introduction.blockformat = BlockFormat(xmlreader.attributes().value("blockformat").toString());
     ok &= this->error(this->introduction.blockformat, this->error_string(xmlreader),
                       QString("introduction:blockformat"));

     // introduction::text
     this->introduction.text = xmlreader.readElementText();

     continue;
  }

   /*
     lettrine
   */
   if (tokenname == "lettrine") {
     this->lettrine.found = true;

     // lettrine::positionintextframe
     QString str_pos = xmlreader.attributes().value("positionintextframe").toString();
     this->lettrine.position_in_text_frame = PosInTextFrameFormat(str_pos);
     ok &= this->error(this->lettrine.position_in_text_frame, this->error_string(xmlreader),
                       QString("lettrine:posintextframe"));

     // lettrine::filename
     this->lettrine.filename_with_fullpath = this->path + "/" + xmlreader.attributes().value("filename").toString();
     QFile lettrinefile(this->lettrine.filename_with_fullpath);
     if (!lettrinefile.open(QFile::ReadOnly)) {
       QString msg( "An error occurs while reading the lettrine's file; "
                    "is the file missing ? "
                    "filename='%1'");
       this->error(msg.arg(this->lettrine.filename_with_fullpath), this->error_string(xmlreader));
       this->lettrine.found = false;
       ok = false;
     } else {
       this->lettrine.image = QImage(this->lettrine.filename_with_fullpath);
     }

     // lettrine::aspectratio
     this->lettrine.aspectratio = xmlreader.attributes().value("aspectratio").toInt();
     if (this->lettrine.aspectratio <= 0) {
       QString msg("the aspect ratio found for the lettrine isn't correct; "
                   "accepted values are integers greater than 0."
                   "given aspectratio = %1.");
       this->error(msg.arg(QString().setNum(this->lettrine.aspectratio)), error_string(xmlreader));
       ok = false;
     }

     xmlreader.skipCurrentElement();
     continue;
   }

   /*
     text
   */
   if (tokenname == "text") {

     // text::blockformat
     this->source_text.blockformat = BlockFormat(xmlreader.attributes().value("blockformat").toString());
     ok &= this->error(this->source_text.blockformat, this->error_string(xmlreader), QString("text:blockformat"));

     // text::description
     this->source_text.name = xmlreader.attributes().value("description").toString();

     // text::filename
     this->source_text.filename = this->path + "/" + xmlreader.attributes().value("filename").toString();

     QFile textfile(this->source_text.filename);
     if (!textfile.open(QFile::ReadOnly)) {
       ok = false;
       this->error( QString("Missing text file named '%1'.").arg(this->source_text.filename),
                    error_string(xmlreader));
     }

     // text::informations
     this->source_text.informations = xmlreader.attributes().value("informations").toString();

     xmlreader.skipCurrentElement();
     continue;
  }

   /*
     aspect
   */
   if (tokenname == "aspect") {
     while (xmlreader.readNextStartElement()) {

       // aspect::sourceeditor
       if (xmlreader.name() == "sourceeditor") {

         while (xmlreader.readNextStartElement()) {
           // aspect::sourceeditor::stylesheet
           if (xmlreader.name() == "stylesheet") {
             this->sourceeditor_stylesheet = xmlreader.readElementText();
             continue;
           }
           // aspect::sourceeditor::default_textformat
           if (xmlreader.name() == "default_textformat") {
             this->sourceeditor_default_textformat = TextFormat(xmlreader.readElementText());
             ok &= this->error(this->sourceeditor_default_textformat, this->error_string(xmlreader),
                               QString("aspect::sourceeditor::default_textformat"));
             continue;
           }
           // aspect::sourceeditor::karaoke_textformat
           if (xmlreader.name() == "karaoke_textformat") {
             this->sourceeditor_karaoke_textformat = TextFormat(xmlreader.readElementText());
             ok &= this->error(this->sourceeditor_karaoke_textformat, this->error_string(xmlreader),
                               QString("aspect::sourceeditor::karaoke_textformat"));
             continue;
           }
         }
       }

       // aspect::commentaryeditor
       if (xmlreader.name() == "commentaryeditor") {

         while (xmlreader.readNextStartElement()) {
           // aspect::commentaryeditor::stylesheet
           if (xmlreader.name() == "stylesheet") {
             this->commentaryeditor_stylesheet = xmlreader.readElementText();
             continue;
           }
           // aspect::commentaryeditor::textformat
           if (xmlreader.name() == "textformat") {
             this->commentaryeditor_textformat = TextFormat(xmlreader.readElementText());
             ok &= this->error(this->commentaryeditor_textformat, this->error_string(xmlreader),
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

     this->audiorecord.found = true;
     // audiorecord::description
     this->audiorecord.name = xmlreader.attributes().value("description").toString();

     // audiorecord::filename
     this->audiorecord.filename = this->path + "/" + xmlreader.attributes().value("filename").toString();

     QFile audiofile(this->audiorecord.filename);
     if (!audiofile.open(QFile::ReadOnly)) {
       ok = false;
       this->error(QString("Can't open the audio record file named '%1'").arg(this->audiorecord.filename),
                   error_string(xmlreader));
     }

     // audiorecord::informations
     this->audiorecord.informations = xmlreader.attributes().value("informations").toString();

     while (xmlreader.readNextStartElement()) {

       // audiorecord::segment
       if (xmlreader.name() == "segment") {

         // audiorecord::segment::textranges
         PosInTextRanges textranges(xmlreader.attributes().value("textranges").toString());
         ok &= this->error(textranges, this->error_string(xmlreader),
                           QString("audiorecord::segment::textranges"));

         // audiorecord::segment::audiorange
         PosInAudioRange audiorange(xmlreader.attributes().value("audiorange").toString());
         ok &= this->error(audiorange, this->error_string(xmlreader),
                           QString("audiorecord::segment::audiorange"));

         this->audiorecord.text2audio[ textranges ] = PairOfPosInAudio(audiorange.first(), audiorange.second());

         xmlreader.skipCurrentElement();
         continue;
       }
     }

     continue;
   }

   /*
     translation
   */
   if (tokenname == "translation") {

     this->translation.found = true;
     // translation::informations
     this->translation.informations = xmlreader.attributes().value("informations").toString();
     // translation::description
     this->translation.name = xmlreader.attributes().value("name").toString();

     while (xmlreader.readNextStartElement()) {

       // translation::segment
       if (xmlreader.name() == "segment") {

         // translation::segment::textranges
         PosInTextRanges textranges(xmlreader.attributes().value("textranges").toString());
         ok &= this->error(textranges, this->error_string(xmlreader),
                           QString("translation::segment::textranges"));

         // translation's text
         QString text(xmlreader.readElementText());
         this->translation.translations[ textranges ] = xmlreader.readElementText();

         continue;
       }
     }

     continue;
   }

   /*
     textformats
   */
   if (tokenname == "textformats") {
     while (xmlreader.readNextStartElement()) {

       // textformats::textformat
       if (xmlreader.name() == "textformat") {
         // textformats::textformat::name
         QString name = xmlreader.attributes().value("name").toString();
         // textformats::textformat::aspect
         QString aspect = xmlreader.attributes().value("aspect").toString();

         this->textformats[ name ] = aspect;

         xmlreader.skipCurrentElement();
         continue;
       }
     }

     continue;
   }

   /*
     levels
   */
   if (tokenname == "levels") {
     while (xmlreader.readNextStartElement()) {

       // level::level
       if (xmlreader.name() == "level") {
         // levels::level::name
         QString name = xmlreader.attributes().value("name").toString();
         // levels::level::number
         int number = xmlreader.attributes().value("number").toString().toInt();
         // levels::level::textformat
         QString textformat_str = xmlreader.attributes().value("textformat").toString();
         TextFormat textformat(textformat_str);
         ok &= this->error(textformat, this->error_string(xmlreader),
                           QString("levels::level::textformat"));

         this->levels[ number ] = LevelDetails(name, textformat_str);

         xmlreader.skipCurrentElement();
         continue;
       }
     }

     continue;
   }

   /*
     arrows
   */
   if (tokenname == "arrows") {
     while (xmlreader.readNextStartElement()) {

       // arrows::arrow
       if (xmlreader.name() == "arrow") {
         // arrows::arrow::name
         QString name = xmlreader.attributes().value("name").toString();
         // arrows::arrow::arrowformat
         ArrowFormat arrowformat( xmlreader.attributes().value("arrowformat").toString() );
         ok &= this->error(arrowformat, this->error_string(xmlreader),
                           QString("arrows::arrow::arrowformat"));

         this->arrows[ name ] = arrowformat;

         xmlreader.skipCurrentElement();
         continue;
       }
     }

     continue;
   }

   /*
     notes
   */
   if (tokenname == "notes") {
     while (xmlreader.readNextStartElement()) {

       // notes::note
       if (xmlreader.name() == "note") {
         // notes::note::level
         int level = xmlreader.attributes().value("level").toString().toInt();
         // notes::note::textranges
         PosInTextRanges textranges(xmlreader.attributes().value("textranges").toString());
         ok &= this->error(textranges, this->error_string(xmlreader),
                           QString("notes::note::textranges"));
         // notes::note::aspect
         QString         textformatname = xmlreader.attributes().value("aspect").toString();
         // notes::note::text
         QString         text(xmlreader.readElementText());

         this->notes.insert(level,
                            textranges,
                            DipyDocNote(level, textranges, text, textformatname));

         continue;
       }
     }

     continue;
   }
 } // ... while (xmlreader.readNextStartElement())
 return ok;
}

/*______________________________________________________________________________

  DipyDoc::levels_repr

  Return a string which is a representation of this->levels
______________________________________________________________________________*/
QString DipyDoc::levels_repr(void) const {
  QString res("");
  for (auto &level : this->levels) {
    res += QString("\n  #%1 - name='%2' - textformat='%3'").arg(QString().setNum(level.first),
                                                                level.second.name,
                                                                level.second.textformat.repr());
    }
  return res;
}
