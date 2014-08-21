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

#include "dipydoc.h"

/*______________________________________________________________________________

        DipyDoc::constructor from a "path" : initialize "this" from the files
                                             stored in "path"

        See above for a description of the expected files.

        Fill "errors" with human-readable messages.

______________________________________________________________________________*/
DipyDoc::DipyDoc(const QString& path) {

  qDebug() << "DipyDoc::DipyDoc from " << path;

  this->clear();

  // does the path leads to the expected files ?
  if( this->check_path(path) == false ) {
    qDebug() << "DipyDoc::DipyDoc" << "problem with the path =" << path;
    return;
  }

  // let's open the main file :
  this->init_from_xml(path);

  // let's open the text file :
  QFile src_file(this->source_text.filename);
  src_file.open( QIODevice::ReadOnly | QIODevice::Text );
  QTextStream src_file_stream(&src_file);
  src_file_stream.setCodec("UTF-8");
  this->source_text.text = src_file_stream.readAll();
}

/*______________________________________________________________________________

        DipyDoc::check_path() : check if path leads to the expected files.

        Modify _well_initialized and _internal_state if an error occurs.
        Fill "errors" with human-readable messages.

        Return false if an error occurs, or true if everything's ok.

        tests :

        o does "path" exists ?
        o is "path" a directory ?
        o does the file "path/text" exists ?
        o does the file "path/main.xml" exists ?
______________________________________________________________________________*/
bool DipyDoc::check_path(const QString& path)
{
  QString msg_error;

  // does "path" exists ?
  QFileInfo path_info = QFileInfo(path);
  if( path_info.exists() == false ) {
    this->_well_initialized = false;
    this->_internal_state = DipyDoc::INTERNALSTATE::UNKNOWN_PATH;

    msg_error = "an error occured : 'path' doesn't exist";
    msg_error += "path = " + path + "; ";
    msg_error += "[in function DipyDoc::check_path]";
    this->errors.append( msg_error );

    qDebug() << "DipyDoc::check_path; error : " << msg_error;
    return false;
  }

  // is "path" a directory ?
  if( path_info.isFile() == true ) {
    this->_well_initialized = false;
    this->_internal_state = DipyDoc::INTERNALSTATE::PATH_IS_A_FILE;

    msg_error = "an error occured : 'path' is a file, not a directory";
    msg_error += "path = " + path + "; ";
    msg_error += "[in function DipyDoc::check_path]";
    this->errors.append( msg_error );

    qDebug() << "DipyDoc::check_path; error : " << msg_error;
    return false;
  }

  // does the main file exist ?
  QFileInfo main_info = QFileInfo(path + "/" + this->MAIN_FILENAME);
  if( main_info.exists() == false ) {
    this->_well_initialized = false;
    this->_internal_state = DipyDoc::INTERNALSTATE::MISSING_MAIN_FILE;

    msg_error = "an error occured : missing main file in path.";
    msg_error += "path = " + path + "; ";
    msg_error += "[in function DipyDoc::check_path]";
    this->errors.append( msg_error );

    qDebug() << "DipyDoc::check_path; error : " << msg_error;
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

  this->errors.clear();

  this->title.clear();
  this->introduction.clear();
  this->lettrine.clear();

  this->sourceeditor_stylesheet = fixedparameters::default__sourceeditor_stylesheet;
  this->commentaryeditor_stylesheet = fixedparameters::default__commentaryeditor_stylesheet;

  this->dipydoc_version = -1;
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

  switch( this->_internal_state) {

    case DipyDoc::INTERNALSTATE::OK : {
      return QObject::tr("No problem has been detected.");
    }

    case DipyDoc::INTERNALSTATE::NOT_YET_INITIALIZED : {
      return QObject::tr("The DipyDoc has not been initialized "
                         "and stays in an undefined state.");
    }

    case DipyDoc::INTERNALSTATE::BAD_INITIALIZATION : {
      return QObject::tr("The DipyDoc has not been correctly initialized "
                         "but no further information can be given.");
    }

    case DipyDoc::INTERNALSTATE::UNKNOWN_PATH : {
      return QObject::tr("The given path doesn't exist.");
    }

    case DipyDoc::INTERNALSTATE::PATH_IS_A_FILE : {
      return QObject::tr("The given path is a file : "
                         "a DipyDoc is a folder with several files.");
    }

    case DipyDoc::INTERNALSTATE::MISSING_MAIN_FILE : {
      QString msg = QObject::tr("This DipyDoc contains an error : "
                                "the given path doesn't contain "
                                "the expected main file, '$FILENAME$'.");
      msg.replace( "$FILENAME$", this->MAIN_FILENAME );
      return msg;
    }

    case DipyDoc::INTERNALSTATE::MISSING_TEXT_FILE : {
      QString msg = QObject::tr("This DipyDoc contains an error : "
                                "the given path doesn't contain the "
                                "expected text file, '$FILENAME$'.");
      msg.replace( "$FILENAME$", this->source_text.filename );
      return msg;
    }

    case DipyDoc::INTERNALSTATE::MISSING_AUDIO_FILE : {
      QString msg = QObject::tr("This DipyDoc contains an error : "
                                "the given path doesn't contain the "
                                "expected audio file ('$FILENAME$') "
                                "whose name was given in the DipyDoc.");
      msg.replace( "$FILENAME$", this->audiorecord.filename );
      return msg;
    }

    case DipyDoc::INTERNALSTATE::MISSING_SOURCE_TEXT_FILE : {
      QString msg = QObject::tr("This DipyDoc contains an error : "
                                "the given path doesn't contain the "
                                "expected text file, '$FILENAME$'.");
      msg.replace( "$FILENAME$", this->source_text.filename );
      return msg;
    }

    case DipyDoc::INTERNALSTATE::OUTDATED_DIPYDOC_VERSION : {
      QString msg = QObject::tr("The given path contain a DipyDoc document "
                                "whose version ($VERSION$) is outdated."
                                "The minimal version being $MINVERSION$, "
                                "please update your DipyDoc documents.");
      msg.replace( "$VERSION$", QString().setNum(this->dipydoc_version ));
      msg.replace( "$MINVERSION$", QString().setNum(this->minimal_dipydoc_version ));
      return msg;
    }

    case DipyDoc::INTERNALSTATE::DIPYDOC_VERSION_TOO_RECENT : {
      QString msg = QObject::tr("The given path contain a DipyDoc document "
                                "whose version ($VERSION$) is too recent."
                                "The maximal version being $MAXVERSION$, "
                                "please update your DipyDoc reader.");
      msg.replace( "$VERSION$", QString().setNum(this->dipydoc_version ));
      msg.replace( "$MAXVERSION$", QString().setNum(this->maximal_dipydoc_version ));
      return msg;
    }

    case DipyDoc::WRONG_VALUE_FOR_LETTRINE_ASPECTRATIO : {
      QString msg = QObject::tr("This DipyDoc contains an error : "
                                "the given ratio aspect of the lettrine "
                                "is zero or above. "
                                "A correct value would be greater than 0."
                                "Value given in main.xml : $LETTRINEASPECTRATIO");
      msg.replace( "$LETTRINEASPECTRATIO$", QString().setNum(this->lettrine.aspectratio) );
      return msg;
    }

    case DipyDoc::MISSING_LETTRINE_FILE : {
      QString msg = QObject::tr("This DipyDoc contains an error : "
                                "the given path doesn't contain the "
                                "expected lettrine file image."
                                "In main.xml the name '$LETTRINEFILENAME$' "
                                "appears but such a file "
                                "can't be found in the given path.");
      msg.replace( "$LETTRINEFILENAME$", this->lettrine.filename );
      return msg;
    }

    default : {
      return QObject::tr("anomaly : unknown internal state.");
    }

  }

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

  for( auto &textrange : positions ) {
    QString substring = this->source_text.text.mid( static_cast<int>(textrange.first),
                                                    static_cast<int>(textrange.second - textrange.first ));

    if( substring.length() > maxlength ) {
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
         "languages=\"$LANGUAGEFROMTO$\">\n";

  res += "\n";

  /*............................................................................
    title :
  ............................................................................*/
  if( this->title.available == true ) {
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
  if( this->introduction.available == true ) {
    res += "  <introduction textformat=\"$INTRODUCTIONTEXTFORMAT$\" "
           "blockformat=\"$INTRODUCTIONBLOCKFORMAT$\">"
           "$INTRODUCTIONTEXT$"
           "</introduction>\n\n";
  }

  /*............................................................................
    lettrine :
  ............................................................................*/
  if( this->lettrine.available == true ) {
    res += "  <lettrine filename=\"$LETTRINEFILENAME$\" "
           "positionintextframe=\"$LETTRINEPOSITIONINTEXTFRAME$\" "
           "aspectratio=\"$LETTRINEASPECTRATIO$\"/>\n\n";
  }

  /*............................................................................
    text : no sub-elements.
  ............................................................................*/
  res += "  <text \n"
         "        name=\"$TEXTNAME$\" \n"
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
  if( this->audiorecord.available == true ) {
    res += "\n";
    list_of_posintextranges.clear();
    res += "  <audiorecord \n"
           "        name=\"$AUDIORECORDNAME$\" \n"
           "        filename=\"$AUDIORECORDFILENAME$\" \n"
           "        informations=\"$AUDIORECORDINFORMATIONS$\" \n"
           "  >\n";

      for(auto &textrange : this->audiorecord.text2audio) {
        list_of_posintextranges.vposintextranges.push_back( textrange.first );
      }
      list_of_posintextranges.sort();
      for(auto &textranges : list_of_posintextranges.vposintextranges) {
        QString new_line("    <segment "
                         "textranges=\"$TEXTRANGE$\" "
                         "audiorange=\"$AUDIORANGE$\" "
                         "srctext=\"$TEXT$\" "
                         "/>\n");
        new_line.replace( "$TEXTRANGE$", textranges.to_str() );
        PosInAudioRange posinaudiorange( this->audiorecord.text2audio[textranges] );
        new_line.replace( "$AUDIORANGE$", posinaudiorange.to_str() );
        new_line.replace( "$TEXT$",  this->get_condensed_extracts_from_the_source_text(textranges, 30) );
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
         "        name=\"$TRANSLATIONNAME$\" \n"
         "        informations=\"$TRANSLATIONINFORMATIONS$\" \n"
         "  >\n";
  for(auto &textrange : this->translation.translations) {
    list_of_posintextranges.vposintextranges.push_back( textrange.first );
  }
  list_of_posintextranges.sort();

  for(auto &textranges : list_of_posintextranges.vposintextranges) {
    QString new_line("    <segment "
                     "textranges=\"$TEXTRANGE$\" "
                     "srctext=\"$TEXT$\""
                     ">");

    new_line.replace( "$TEXTRANGE$",
                      textranges.to_str() );
    new_line.replace( "$TEXT$",
                      this->get_condensed_extracts_from_the_source_text(textranges, 30) );
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
  for(auto &textformat : this->textformats) {
    QString new_line("    <textformat name=\"$NAME$\" aspect=\"$ASPECT$\" />\n");
    new_line.replace( "$NAME$", textformat.first );
    new_line.replace( "$ASPECT$",  textformat.second );
    res += new_line;
  }
  res += "  </textformats>\n";

  /*............................................................................
    levels
  ............................................................................*/
  res += "\n";
  res += "  <levels>\n";
  for(auto &level : this->levels) {
    QString new_line("    <level number=\"$NUMBER$\" "
                     "name=\"$NAME$\" "
                     "aspect=\"$ASPECT$\" "
                     "/>\n");
    new_line.replace( "$NUMBER$", QString().setNum(level.first) );
    new_line.replace( "$NAME$", level.second.name );
    new_line.replace( "$ASPECT$", level.second.textformat.repr() );
    res += new_line;
  }
  res += "  </levels>\n";

  /*............................................................................
    arrows
  ............................................................................*/
  res += "\n";
  res += "  <arrows>\n";
  for(auto &arrow : this->arrows) {
    QString new_line("    <arrow name=\"$NAME$\" "
                     "aspect=\"$ASPECT$\" "
                     "/>\n");
    new_line.replace( "$NAME$", arrow.first );
    new_line.replace( "$ASPECT$",  arrow.second.straspect );
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
  res.replace( "$DIPYDOCVERSION$",
               QString().setNum(this->dipydoc_version) );
  res.replace( "$LANGUAGEFROMTO$",
               this->languagefromto.to_str() );

  res.replace( "$TITLETEXT$",
               this->title.text );
  res.replace( "$TITLETEXTFORMAT$",
               this->title.textformat.repr() );
  res.replace( "$TITLEBLOCKFORMAT$",
               this->title.blockformat.repr() );

  res.replace( "$INTRODUCTIONTEXT$",
               this->introduction.text );
  res.replace( "$INTRODUCTIONTEXTFORMAT$",
               this->introduction.textformat.repr() );
  res.replace( "$INTRODUCTIONBLOCKFORMAT$",
               this->introduction.blockformat.repr() );

  res.replace( "$LETTRINEFILENAME$",
               this->lettrine.filename );
  res.replace( "$LETTRINEASPECTRATIO$",
               QString().setNum(this->lettrine.aspectratio) );
  res.replace( "$LETTRINEPOSITIONINTEXTFRAME$",
               this->lettrine.position_in_text_frame.repr() );

  res.replace( "$SOURCEEDITOR_STYLESHEET$",
               this->sourceeditor_stylesheet );
  res.replace( "$SOURCEEDITOR_DEFAULTTEXTFORMAT$",
               this->sourceeditor_default_textformat.repr() );
  res.replace( "$SOURCEEDITOR_KARAOKETEXTFORMAT$",
               this->sourceeditor_karaoke_textformat.repr() );
  res.replace( "$COMMENTARYEDITOR_STYLESHEET$",
               this->commentaryeditor_stylesheet );
  res.replace( "$COMMENTARYEDITOR_DEFAULTTEXTFORMAT$",
               this->commentaryeditor_textformat.repr() );

  res.replace( "$AUDIORECORDNAME$",
               this->audiorecord.name );
  res.replace( "$AUDIORECORDINFORMATIONS$",
               this->audiorecord.informations );
  // just the filename, not the path :
  res.replace( "$AUDIORECORDFILENAME$",
               QFileInfo(this->audiorecord.filename).fileName() );

  res.replace( "$TEXTNAME$",
               this->source_text.name );
  res.replace( "$TEXTINFORMATIONS$",
               this->source_text.informations );
  res.replace( "$TEXTBLOCKFORMAT$",
               this->source_text.blockformat.repr() );
  // just the filename, not the path :
  res.replace( "$TEXTFILENAME$",
               QFileInfo(this->source_text.filename).fileName() );

  res.replace( "$TRANSLATIONNAME$",
               this->translation.name );
  res.replace( "$TRANSLATIONINFORMATIONS$",
               this->translation.informations );

  return res;
}

/*______________________________________________________________________________

        DipyDoc::init_from_xml()

        Initialize "this" from the file(s) stored in "path" and return a (bool)success.
        This method doesn't check if "path" is valid : see the ::check_path()
        method for this.

        Fill "errors" with human-readable messages.

        (1) clear "this"
        (2) main file opening
        (3) xml reading
            (3.1) main file reading
            (3.2) was the xml reading of the main file ok ?
        (4) initialize "audiorecord.audio2text"
        (5) checks
            (5.1) is the version of the Dipy doc correct ?
            (5.2) is the object languagefromto correctly initialized ?
            (5.3) is audiorecord.text2audio correctly initialized ?
            (5.4) is audiorecord.audio2text correctly initialized ?
            (5.5) is translation correctly initialized ?
            (5.6) does the audio file exist ?
            (5.7) does the text file exist ?
            (5.8) is the aspectratio of the lettrine correctly initialized ?
            (5.9) does the lettrine's file exist ?
        (6) initializaton of _well_initialized

______________________________________________________________________________*/
void DipyDoc::init_from_xml(const QString& path) {

  QString msg_error;

  /*............................................................................
    (1) clear "this"
  ............................................................................*/
  this->clear();

  qDebug() << "DipyDoc::init_from_xml" << "path=" << path;

  /*............................................................................
    (2) main file opening
  ............................................................................*/
  QString main_filename = path + "/" + this->MAIN_FILENAME;
  QFile dipydoc_main_xml(main_filename);

  if ( !dipydoc_main_xml.open( QIODevice::ReadOnly | QIODevice::Text ) ) {

    qDebug() << "DipyDoc::init_from_xml" \
             << "can't open the main file in " << path;

    msg_error = "An error occurs while opening the main file; ";
    msg_error += "filename=" + main_filename;
    msg_error += "[in the function DipyDoc::init_from_xml]";
    this->errors.append( msg_error );
    return;
  }

  /*............................................................................
    (3) xml reading
  ............................................................................*/
  QXmlStreamReader xmlreader;
  xmlreader.setDevice(&dipydoc_main_xml);

  /*............................................................................
    (3.1) main file reading
  ............................................................................*/
  DipyDocDiv current_division = DIPYDOCDIV_UNDEFINED;

  while(!xmlreader.atEnd() && !xmlreader.hasError()) {

    QXmlStreamReader::TokenType token = xmlreader.readNext();

    // token=StartElement ?
    if(token == QXmlStreamReader::StartElement) {

      QString name = xmlreader.name().toString();

      if( name == "arrow" ) {
        current_division = DIPYDOCDIV_INSIDE_ARROW;
        QString arrow_name = xmlreader.attributes().value("name").toString();
        QString arrow_aspect = xmlreader.attributes().value("aspect").toString();
        ArrowDetails arrowdetails(arrow_aspect);
        this->arrows[ arrow_name ] = arrowdetails;
        continue;
      }

      if( name == "audiorecord" ) {
        current_division = DIPYDOCDIV_INSIDE_AUDIORECORD;
        this->audiorecord.available = true;
        this->audiorecord.name = xmlreader.attributes().value("name").toString();
        this->audiorecord.filename = path + "/" + xmlreader.attributes().value("filename").toString();
        this->audiorecord.informations = xmlreader.attributes().value("informations").toString();
        continue;
      }

      if( name == "commentaryeditor" ) {
        current_division = DIPYDOCDIV_INSIDE_COMMENTARYEDITOR;
        continue;
      }

      if( name == "default_textformat" ) {

        if ( current_division == DIPYDOCDIV_INSIDE_SOURCEEDITOR ) {
          this->sourceeditor_default_textformat = TextFormat(xmlreader.readElementText());
          continue;
        }

        // $$$ problem $$$ unknown case.
      }

      if( name == "dipydoc" ) {
        current_division = DIPYDOCDIV_UNDEFINED;
        this->dipydoc_version = xmlreader.attributes().value("dipydoc_version").toString().toInt();
        this->languagefromto = LanguageFromTo( xmlreader.attributes().value("languages").toString() );
        continue;
      }

      if( name == "introduction" ) {
        this->introduction.available = true;
        this->introduction.textformat = TextFormat( xmlreader.attributes().value("textformat").toString() );
        this->introduction.blockformat = BlockFormat( xmlreader.attributes().value("blockformat").toString() );
        this->introduction.text = xmlreader.readElementText();
        continue;
      }

      if( name == "karaoke_textformat" ) {

        if ( current_division == DIPYDOCDIV_INSIDE_SOURCEEDITOR ) {
          this->sourceeditor_karaoke_textformat = TextFormat( xmlreader.readElementText() );
          continue;
        }

        // $$$ problem $$$ unknown case.
      }

      if( name == "lettrine" ) {
        this->lettrine.well_initialized = true; // this will be checked later.
        this->lettrine.available = true;
        this->lettrine.filename = xmlreader.attributes().value("filename").toString();
        this->lettrine.aspectratio = xmlreader.attributes().value("aspectratio").toInt();
        this->lettrine.position_in_text_frame = PosInTextFrameFormat( xmlreader.attributes().value("positionintextframe").toString() );
        this->lettrine.image = QImage(this->lettrine.filename);
        continue;
      }

      if( name == "level" ) {
        current_division = DIPYDOCDIV_INSIDE_LEVEL;
        int     level_number = xmlreader.attributes().value("number").toString().toInt();
        QString level_name = xmlreader.attributes().value("name").toString();
        QString level_strtextformat = xmlreader.attributes().value("aspect").toString();

        LevelDetails leveldetails( level_name, level_strtextformat );

        this->levels[ level_number ] = leveldetails;
        continue;
      }

      if( name == "segment" ) {

        switch( current_division ) {

          case DIPYDOCDIV_INSIDE_AUDIORECORD : {
            PosInTextRanges textranges( xmlreader.attributes().value("textranges").toString() );
            PosInAudioRange audiorange( xmlreader.attributes().value("audiorange").toString() );
            this->audiorecord.text2audio[ textranges ] = PairOfPosInAudio( audiorange.first(), audiorange.second() );

            qDebug() << "DipyDoc::init_from_xml : audiorecord:segment" << \
                        "textranges=" << textranges.to_str() << \
                        "audiorange=" << audiorange.to_str();
            break;
          }

          case DIPYDOCDIV_INSIDE_TRANSLATION : {
            PosInTextRanges textranges( xmlreader.attributes().value("textranges").toString() );
            QString text(xmlreader.readElementText());
            this->translation.translations[ textranges ] = text;

            qDebug() << "DipyDoc::init_from_xml : translation:segment" << \
                        "textranges=" << textranges.to_str() << \
                        "srctext=" << text;
            break;
          }

          // DIPYDOCDIV_INSIDE_TEXT, or anything else.
          default : {
            break;
          }

        }
        continue;

      }

      if( name == "sourceeditor" ) {
        current_division = DIPYDOCDIV_INSIDE_SOURCEEDITOR;
        continue;
      }

      if( name == "stylesheet" ) {
        if ( current_division == DIPYDOCDIV_INSIDE_SOURCEEDITOR ) {
          this->sourceeditor_stylesheet = xmlreader.readElementText();
          continue;
        }
        if ( current_division == DIPYDOCDIV_INSIDE_COMMENTARYEDITOR ) {
          this->commentaryeditor_stylesheet = xmlreader.readElementText();
          continue;
        }
        // $$$ problem $$$ : unknown case
        continue;
      }

      if( name == "text" ) {
        current_division = DIPYDOCDIV_INSIDE_TEXT;
        this->source_text.name = xmlreader.attributes().value("name").toString();
        this->source_text.filename = path + "/" + xmlreader.attributes().value("filename").toString();
        this->source_text.informations = xmlreader.attributes().value("informations").toString();
        this->source_text.blockformat = BlockFormat( xmlreader.attributes().value("blockformat").toString() );
        continue;
      }

      if( name == "textformat" ) {

        if ( current_division == DIPYDOCDIV_INSIDE_TEXTFORMATS ) {
          QString textformat_name = xmlreader.attributes().value("name").toString();
          QString textformat_aspect = xmlreader.attributes().value("aspect").toString();
          this->textformats[ textformat_name ] = textformat_aspect;
          continue;
        }

        if ( current_division == DIPYDOCDIV_INSIDE_COMMENTARYEDITOR ) {
          this->commentaryeditor_textformat = TextFormat( xmlreader.readElementText() );
          continue;
        }

        // $$$ error $$$ unknown case
        continue;
      }

      if( name == "textformats" ) {
        current_division = DIPYDOCDIV_INSIDE_TEXTFORMATS;
        continue;
      }

      if( name == "title" ) {
        current_division = DIPYDOCDIV_INSIDE_TITLE;
        this->title.available = true;
        this->title.textformat = TextFormat( xmlreader.attributes().value("textformat").toString() );
        this->title.blockformat = BlockFormat( xmlreader.attributes().value("blockformat").toString() );
        this->title.text = xmlreader.readElementText();
        continue;
      }

      if( name == "translation" ) {
        current_division = DIPYDOCDIV_INSIDE_TRANSLATION;
        this->translation.name = xmlreader.attributes().value("name").toString();
        this->translation.informations = xmlreader.attributes().value("informations").toString();
        continue;
      }

      current_division = DIPYDOCDIV_UNDEFINED;
    }
  }
  bool xml_reading_is_ok = !xmlreader.hasError();

  /*............................................................................
    (3.2) was the xml reading of the main file ok ?
  ............................................................................*/

  if( xml_reading_is_ok == false ) {
    msg_error = "An error occurs while reading the main file : ";
    msg_error += xmlreader.errorString() + "; ";
    msg_error += "filename=" + main_filename;
    msg_error += "[in the function DipyDoc::init_from_xml]";
    this->errors.append( msg_error );

    qDebug() << msg_error;
  }

  /*............................................................................
    (4) initialize "audio2text"
  ............................................................................*/
  if( this->audiorecord.available == true ) {
    this->audiorecord.audio2text = PosInAudio2PosInText( this->audiorecord.text2audio );
  }
  else {
    // we clear the audio2text object so that its _well_initialized flag will be set to "true" :
    this->audiorecord.audio2text.clear();
  }

  /*............................................................................
    (5) checks
  ............................................................................*/

  /*............................................................................
    (5.1) is the version of the Dipy doc correct ?
  ............................................................................*/
  bool dipydoc_version_ok = (this->dipydoc_version >= this->minimal_dipydoc_version);

  if( dipydoc_version_ok == false ) {
    msg_error = "An error occurs while reading the main file; ";
    msg_error += "the DipyDoc version of the file is outdated.";
    msg_error += "current version = " + \
                 QString().setNum(this->dipydoc_version) + "; ";
    msg_error += "minimal version supported = " + \
                 QString().setNum(this->minimal_dipydoc_version) + "; ";
    msg_error += "filename=" + main_filename;
    msg_error += "[in the function DipyDoc::init_from_xml]";
    this->errors.append( msg_error );

    this->_internal_state = OUTDATED_DIPYDOC_VERSION;

    qDebug() << msg_error;
  }

  dipydoc_version_ok = (this->dipydoc_version <= this->maximal_dipydoc_version);

  if( dipydoc_version_ok == false ) {
    msg_error = "An error occurs while reading the main file; ";
    msg_error += "the DipyDoc version of the file is too recent";
    msg_error += "current version = " + \
                 QString().setNum(this->dipydoc_version) + "; ";
    msg_error += "maximal version supported = " + \
                 QString().setNum(this->maximal_dipydoc_version) + "; ";
    msg_error += "filename=" + main_filename;
    msg_error += "[in the function DipyDoc::init_from_xml]";
    this->errors.append( msg_error );

    this->_internal_state = DIPYDOC_VERSION_TOO_RECENT;

    qDebug() << msg_error;
  }

  /*............................................................................
     (5.2) is the object languagefromto correctly initialized ?
  ............................................................................*/
  if( languagefromto.well_initialized() == false ) {
    msg_error = "An error occurs while reading the main file; ";
    msg_error += "Languages from/to could not be read";
    msg_error += "message error due to the LanguageFromTo object =" + \
                 QString().setNum(this->languagefromto.internal_state());
    msg_error += "filename=" + main_filename;
    msg_error += "[in the function DipyDoc::init_from_xml]";
    this->errors.append( msg_error );

    qDebug() << msg_error;
  }

  /*............................................................................
    (5.3) is audiorecord.text2audio correctly initialized ?
  ............................................................................*/
  if( this->audiorecord.available == true and \
      this->audiorecord.text2audio.well_initialized() == false ) {
    msg_error = "An error occurs while reading the main file; ";
    msg_error += "text2audio isn't correctly initialized";
    msg_error += "message error due to the PosInText2PosInAudio object =" +\
                 QString().setNum(this->audiorecord.text2audio.internal_state());
    msg_error += "filename=" + main_filename;
    msg_error += "[in the function DipyDoc::init_from_xml]";
    this->errors.append( msg_error );

    qDebug() << msg_error;
  }

  /*............................................................................
    (5.4) is audio2text correctly initialized ?
  ............................................................................*/
  if( this->audiorecord.available == true and \
      this->audiorecord.audio2text.well_initialized() == false ) {
    msg_error = "An error occurs while reading the main file; ";
    msg_error += "audio2text isn't correctly initialized";
    msg_error += "message error due to the PosInAudio2PosInText object =" +\
                 QString().setNum(this->audiorecord.audio2text.internal_state());
    msg_error += "filename=" + main_filename;
    msg_error += "[in the function DipyDoc::init_from_xml]";
    this->errors.append( msg_error );

    qDebug() << msg_error;
  }

  /*............................................................................
    (5.5) is translation correctly initialized ?
  ............................................................................*/
  if( translation.translations.well_initialized() == false ) {
    msg_error = "An error occurs while reading the main file; ";
    msg_error += "translation isn't correctly initialized";
    msg_error += "message error due to the PosInText2Str object =" +\
                 QString().setNum(this->translation.translations.internal_state());
    msg_error += "filename=" + main_filename;
    msg_error += "[in the function DipyDoc::init_from_xml]";
    this->errors.append( msg_error );

    qDebug() << msg_error;
  }

  /*............................................................................
    (5.6) does the audio file exist ?
  ............................................................................*/
  bool audiofile_ok = true;

  if( this->audiorecord.available == true ) {

      QFile audiofile( this->audiorecord.filename );
      if (!audiofile.open(QFile::ReadOnly) ) {
        audiofile_ok = false;

        msg_error = "An error occurs while opening the audio file; ";
        msg_error += "filename=" + this->audiorecord.filename;
        msg_error += "[in the function DipyDoc::init_from_xml]";
        this->errors.append( msg_error );

        this->_internal_state = MISSING_AUDIO_FILE;

        qDebug() << msg_error;
        }
  }

  /*............................................................................
    (5.7) does the text file exist ?
  ............................................................................*/
  bool textfile_ok = true;

  QFile textfile( this->source_text.filename );
  if (!textfile.open(QFile::ReadOnly) ) {
    textfile_ok = false;

    msg_error = "An error occurs while opening the text file; ";
    msg_error += "filename=" + this->source_text.filename;
    msg_error += "[in the function DipyDoc::init_from_xml]";
    this->errors.append( msg_error );

    this->_internal_state = MISSING_SOURCE_TEXT_FILE;

    qDebug() << msg_error;
    }

  /*............................................................................
    (5.8) is the aspectratio of the lettrine correctly initialized ?
  ............................................................................*/
  if( this->lettrine.available == true && this->lettrine.aspectratio <= 0 ) {
    msg_error = "the aspect ratio defined for the lettrine isn't correct; "
                "accepted values are integers greater than 0."
                "given aspectratio = " +\
                QString().setNum(this->lettrine.aspectratio);
    this->errors.append( msg_error );

    this->_internal_state = WRONG_VALUE_FOR_LETTRINE_ASPECTRATIO;

    qDebug() << msg_error;
  }

  /*............................................................................
    (5.9) does the lettrine's file exist ?
  ............................................................................*/
  if( this->lettrine.available == true ) {
      QFile lettrinefile( this->lettrine.filename );
      if (!lettrinefile.open(QFile::ReadOnly) ) {
        msg_error = "An error occurs while reading the lettrine's file; ";
        msg_error += "filename=" + this->lettrine.filename;
        msg_error += "[in the function DipyDoc::init_from_xml]";
        this->errors.append( msg_error );

        this->_internal_state = MISSING_LETTRINE_FILE;

        qDebug() << msg_error;
        }
  }

  /*............................................................................
    (6) initializaton of _well_initialized
  ............................................................................*/
  this->_well_initialized = xml_reading_is_ok and \
                            dipydoc_version_ok and \
                            this->languagefromto.well_initialized() and \
                            this->audiorecord.text2audio.well_initialized() and \
                            this->audiorecord.audio2text.well_initialized() and \
                            this->translation.translations.well_initialized() and \
                            audiofile_ok and \
                            textfile_ok and \
                            this->lettrine.well_initialized;

  qDebug() << "DipyDoc::init_from_xml" << \
           "xml:this->_well_initialized" << this->_well_initialized;
}
