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

    ____________________________________________________________________________

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
  QFile src_file(path + "/" + this->TEXT_FILENAME);
  src_file.open( QIODevice::ReadOnly | QIODevice::Text );
  QTextStream src_file_stream(&src_file);
  src_file_stream.setCodec("UTF-8");
  this->source_text = src_file_stream.readAll();
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

  // does the text file exist ?
  QFileInfo text_info = QFileInfo(path + "/" + this->TEXT_FILENAME);
  if( text_info.exists() == false ) {
    this->_well_initialized = false;
    this->_internal_state = DipyDoc::INTERNALSTATE::MISSING_TEXT_FILE;

    msg_error = "an error occured : missing text file in path.";
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
  this->text2audio.clear();
  this->audio2text.clear();
  this->dipydoc_version = -1;
  this->languagefromto.clear();
  this->translation.clear();
}

/*______________________________________________________________________________

        DipyDoc::diagnosis()

        Return a QString explaining the internal state of the program.

______________________________________________________________________________*/
QString DipyDoc::diagnosis(void) const {

  switch( this->_internal_state) {

    case DipyDoc::INTERNALSTATE::OK : {
      return QObject::tr("No problem has been detected.");
    }

    case DipyDoc::INTERNALSTATE::NOT_YET_INITIALIZED : {
      return QObject::tr("The DipyDoc has not been initialized and it stays in an undefined state.");
    }

    case DipyDoc::INTERNALSTATE::BAD_INITIALIZATION : {
      return QObject::tr("The DipyDoc has not been correctly initialized but no further information can be given.");
    }

    case DipyDoc::INTERNALSTATE::UNKNOWN_PATH : {
      return QObject::tr("The given path doesn't exist.");
    }

    case DipyDoc::INTERNALSTATE::PATH_IS_A_FILE : {
      return QObject::tr("The given path is a file.");
    }

    case DipyDoc::INTERNALSTATE::MISSING_MAIN_FILE : {
      QString msg = QObject::tr("The given path doesn't contain the expected main file, '$FILENAME$'.");
      msg.replace( "$FILENAME$", this->MAIN_FILENAME );
      return msg;
    }

    case DipyDoc::INTERNALSTATE::MISSING_TEXT_FILE : {
      QString msg = QObject::tr("The given path doesn't contain the expected text file, '$FILENAME$'.");
      msg.replace( "$FILENAME$", this->TEXT_FILENAME );
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
    QString substring = this->source_text.mid( static_cast<int>(textrange.first),
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

  // header :
  res += "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";

  res += "\n";

  res += "<!--\n";
  res += "  This file was automatically generated by a call to DipyDoc::get_xml_repr()\n";
  res += "-->\n";

  res += "\n";

  res += "<dipydoc dipydoc_version=\"$DIPYDOCVERSION$\" languages=\"$LANGUAGEFROMTO$\">\n";

  res += "\n";

  // audiorecord : the functions reads through this->text2audio with sorted keys.
  list_of_posintextranges.clear();
  res += "  <audiorecord name=\"$AUDIORECORDNAME$\" filename=\"$AUDIORECORDFILENAME$\">\n";
  for(auto &textrange : this->text2audio) {
    list_of_posintextranges.vposintextranges.push_back( textrange.first );
  }
  list_of_posintextranges.sort();
  for(auto &textranges : list_of_posintextranges.vposintextranges) {
    QString new_line("    <segment textranges=\"$TEXTRANGE$\" audiorange=\"$AUDIORANGE$\" srctext=\"$TEXT$\" />\n");
    new_line.replace( "$TEXTRANGE$", textranges.to_str() );
    PosInAudioRange posinaudiorange( this->text2audio[textranges] );
    new_line.replace( "$AUDIORANGE$", posinaudiorange.to_str() );
    new_line.replace( "$TEXT$",  this->get_condensed_extracts_from_the_source_text(textranges, 30) );
    res += new_line;
  }
  res += "  </audiorecord>\n";

  // translation : the functions reads through this->translation with sorted keys.
  res += "\n";
  list_of_posintextranges.clear();
  res += "  <translation name=\"$AUDIORECORDNAME$\">\n";
  for(auto &textrange : this->translation) {
    list_of_posintextranges.vposintextranges.push_back( textrange.first );
  }
  list_of_posintextranges.sort();
  for(auto &textranges : list_of_posintextranges.vposintextranges) {
    QString new_line("    <segment textranges=\"$TEXTRANGE$\" srctext=\"$TEXT$\">");
    new_line.replace( "$TEXTRANGE$", textranges.to_str() );
    new_line.replace( "$TEXT$",  this->get_condensed_extracts_from_the_source_text(textranges, 30) );
    res += new_line;
    res += this->translation[ textranges ];
    res += "</segment>\n";
  }
  res += "  </translation>\n";

  // final line :
  res += "\n";
  res += "</dipydoc>\n";

  res.replace( "$DIPYDOCVERSION$", QString().setNum(this->dipydoc_version) );
  res.replace( "$LANGUAGEFROMTO$", this->languagefromto.to_str() );
  res.replace( "$AUDIORECORDNAME$", this->audiorecord_name );
  res.replace( "$AUDIORECORDFILENAME$", this->audiorecord_filename );
  res.replace( "$TRANSLATIONNAME$", this->translation_name );

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
        (4) initialize "audio2text"
        (5) checks
            (5.1) is the version of the Dipy doc correct ?
            (5.2) is the object languagefromto correctly initialized ?
            (5.3) is text2audio correctly initialized ?
            (5.4) is audio2text correctly initialized ?
            (5.5) is translation correctly initialized ?
        (6) initializaton of _well_initialized, _internal_state

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

    qDebug() << "DipyDoc::init_from_xml" << "can't open the main file in " << path;

    msg_error = "An error occurs while reading the main file; ";
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

      if( name == "dipydoc" ) {
        current_division = DIPYDOCDIV_UNDEFINED;
        this->dipydoc_version = xmlreader.attributes().value("dipydoc_version").toString().toInt();
        this->languagefromto = LanguageFromTo( xmlreader.attributes().value("languages").toString() );
        continue;
      }

      if( name == "audiorecord" ) {
        current_division = DIPYDOCDIV_INSIDE_AUDIORECORD;
        this->audiorecord_name = xmlreader.attributes().value("name").toString();
        this->audiorecord_filename = path + "/" + xmlreader.attributes().value("filename").toString();
        continue;
      }

      if( name == "translation" ) {
        current_division = DIPYDOCDIV_INSIDE_TRANSLATION;
        this->translation_name = xmlreader.attributes().value("name").toString();
        continue;
      }

      if( name == "segment" ) {

        switch( current_division ) {

          case DIPYDOCDIV_INSIDE_AUDIORECORD : {
            PosInTextRanges textranges( xmlreader.attributes().value("textranges").toString() );
            PosInAudioRange audiorange( xmlreader.attributes().value("audiorange").toString() );
            this->text2audio[ textranges ] = PairOfPosInAudio( audiorange.first(), audiorange.second() );

            qDebug() << "DipyDoc::init_from_xml : audiorecord:segment" << \
                        "textranges=" << textranges.to_str() << \
                        "audiorange=" << audiorange.to_str();
            break;
          }

          case DIPYDOCDIV_INSIDE_TRANSLATION : {
            PosInTextRanges textranges( xmlreader.attributes().value("textranges").toString() );
            QString text(xmlreader.readElementText());
            this->translation[ textranges ] = text;

            qDebug() << "DipyDoc::init_from_xml : translation:segment" << \
                        "textranges=" << textranges.to_str() << \
                        "srctext=" << text;
            break;
          }

          default : {
            break;
          }

        }
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
    msg_error += "filename=" + path + "/" + main_filename;
    msg_error += "[in the function DipyDoc::init_from_xml]";
    this->errors.append( msg_error );

    qDebug() << msg_error;
  }

  /*............................................................................
    (4) initialize "audio2text"
  ............................................................................*/
  this->audio2text = PosInAudio2PosInText( this->text2audio );

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
    msg_error += "current version = " + QString().setNum(this->dipydoc_version) + "; ";
    msg_error += "minimal version supported = " + QString().setNum(this->minimal_dipydoc_version) + "; ";
    msg_error += "filename=" + main_filename;
    msg_error += "[in the function DipyDoc::init_from_xml]";
    this->errors.append( msg_error );

    qDebug() << msg_error;
  }

  /*............................................................................
     (5.2) is the object languagefromto correctly initialized ?
  ............................................................................*/
  if( languagefromto.well_initialized() == false ) {
    msg_error = "An error occurs while reading the main file; ";
    msg_error += "Languages from/to could not be read";
    msg_error += "message error due to the LanguageFromTo object =" + QString().setNum(this->languagefromto.internal_state());
    msg_error += "filename=" + main_filename;
    msg_error += "[in the function DipyDoc::init_from_xml]";
    this->errors.append( msg_error );

    qDebug() << msg_error;
  }

  /*............................................................................
    (5.3) is text2audio correctly initialized ?
  ............................................................................*/
  if( text2audio.well_initialized() == false ) {
    msg_error = "An error occurs while reading the main file; ";
    msg_error += "text2audio isn't correctly initialized";
    msg_error += "message error due to the PosInText2PosInAudio object =" + QString().setNum(this->text2audio.internal_state());
    msg_error += "filename=" + main_filename;
    msg_error += "[in the function DipyDoc::init_from_xml]";
    this->errors.append( msg_error );

    qDebug() << msg_error;
  }

  /*............................................................................
    (5.4) is audio2text correctly initialized ?
  ............................................................................*/
  if( audio2text.well_initialized() == false ) {
    msg_error = "An error occurs while reading the main file; ";
    msg_error += "audio2text isn't correctly initialized";
    msg_error += "message error due to the PosInAudio2PosInText object =" + QString().setNum(this->audio2text.internal_state());
    msg_error += "filename=" + main_filename;
    msg_error += "[in the function DipyDoc::init_from_xml]";
    this->errors.append( msg_error );

    qDebug() << msg_error;
  }

  /*............................................................................
    (5.5) is translation correctly initialized ?
  ............................................................................*/
  if( translation.well_initialized() == false ) {
    msg_error = "An error occurs while reading the main file; ";
    msg_error += "translation isn't correctly initialized";
    msg_error += "message error due to the PosInText2Str object =" + QString().setNum(this->translation.internal_state());
    msg_error += "filename=" + main_filename;
    msg_error += "[in the function DipyDoc::init_from_xml]";
    this->errors.append( msg_error );

    qDebug() << msg_error;
  }

  /*............................................................................
    (6) initializaton of _well_initialized, _internal_state
  ............................................................................*/
  this->_well_initialized = xml_reading_is_ok and \
                            dipydoc_version_ok and \
                            this->languagefromto.well_initialized() and \
                            this->text2audio.well_initialized() and \
                            this->audio2text.well_initialized() and \
                            this->translation.well_initialized();

  if( this->_well_initialized == true ) {
    this->_internal_state = OK;
  }
  else {
    this->_internal_state = BAD_INITIALIZATION;
  }

  qDebug() << "DipyDoc::init_from_xml" << "xml:this->_well_initialized" << this->_well_initialized;
}
