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

*******************************************************************************/

#include "dipydoc.h"

/*______________________________________________________________________________

        DipyDoc::constructor from a "path" : initialize "this" from the files
                                             stored in "path"

______________________________________________________________________________*/
DipyDoc::DipyDoc(QString& path) {

  this->clear();

  // does the path leads to the expected files ?
  this->check_path(path);
  if( this->_well_initialized == false ) {
    return;
  }

  // let's open the text file :
  QFile src_file(path + "/" + this->TEXTFILE_NAME);
  src_file.open( QIODevice::ReadOnly | QIODevice::Text );
  QTextStream src_file_stream(&src_file);
  src_file_stream.setCodec("UTF-8");
  this->source_text = src_file_stream.readAll();

  this->init_from_xml(path);
}

/*______________________________________________________________________________

        DipyDoc::check_path() : check if path leads to the expected files.

        Modify _well_initialized and _internal_state if an error occurs.

        tests :

        o does "path" exists ?
        o is "path" a directory ?
        o does the file "path/text" exists ?
______________________________________________________________________________*/
void DipyDoc::check_path(QString& path)
{

  // does "path" exists ?
  QFileInfo path_info = QFileInfo(path);
  if( path_info.exists() == false ) {
    this->_well_initialized = false;
    this->_internal_state = DipyDoc::INTERNALSTATE::UNKNOWN_PATH;
    return;
  }

  // is "path" a directory ?
  if( path_info.isFile() == true ) {
    this->_well_initialized = false;
    this->_internal_state = DipyDoc::INTERNALSTATE::PATH_IS_A_FILE;
    return;
  }

  // does the file "path/text" exists ?
  QFileInfo text_info = QFileInfo(path + "/" + this->TEXTFILE_NAME);
  if( text_info.exists() == false ) {
    this->_well_initialized = false;
    this->_internal_state = DipyDoc::INTERNALSTATE::MISSING_TEXT_FILE;
    return;
  }

}

/*______________________________________________________________________________

        DipyDoc::init_from_xml

        o clear "this"
        o initialize the DipyDoc data from the files stored in "path".
          This method doesn't check if "path" is valid : see the ::check_path()
          method for this.

______________________________________________________________________________*/
void DipyDoc::init_from_xml(QString& path) {

  this->clear();

  qDebug() << "DipyDoc::init_from_xml" << "path=" << path;

  QXmlStreamReader xmlreader;

  QFile dipydoc_xml(path + "/" + "main.xml");
  if ( !dipydoc_xml.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
    // http://qt-project.org/doc/qt-5/qtxml-streambookmarks-example.html
    qDebug() << "??? ERROR";
    return;
  }

  xmlreader.setDevice(&dipydoc_xml);

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
        continue;
      }

      if( name == "translation" ) {
        current_division = DIPYDOCDIV_INSIDE_TRANSLATION;
        //qDebug() << "translation::text" << xmlreader.readElementText(); }
        continue;
      }

      if( name == "segment" ) {
        if( current_division == DIPYDOCDIV_INSIDE_AUDIORECORD) {
          PosInTextRanges textranges( xmlreader.attributes().value("textrange").toString() );
          PosInAudioRange audiorange( xmlreader.attributes().value("audiorange").toString() );

          qDebug() << "xml:audiorecord:segment" << "text=" << textranges.to_str() << "audio=" << audiorange.to_str();
          continue;
        }
      }

      current_division = DIPYDOCDIV_UNDEFINED;
    }
  }

  // $$$ fake initialization $$$ :
  // let's initialize the translations :
  this->translation[ { {8,26}, } ] = \
                "Le premier amour de Phébus";
  this->translation[ { {633, 649}, } ] = \
                "Ton arc peut bien transpercer toutes tes cibles";

  // $$$ fake initialization of the karaoke data (this->text2audio & this->audio2text)
  this->text2audio = {
                { {{ {8, 26}, },},  {0, 2399} },
                { {{ {29, 51}, },},  {3000, 5147} },
                { {{ {60, 77}, },},  {5148, 7449} },
                { {{ {80, 104}, },},  {7450, 10667} },
                { {{ {113, 130}, },},  {10668, 13182} },
                { {{ {133, 156}, },},  {13183, 16061} },
      };
  this->audio2text = PosInAudio2PosInText( this->text2audio );


  /*
    Is everything in order ?
  */
  //+ problème de version ? (minimal version)
  //+ message d'erreur ?
  //+ pour chque textranges/audiorange, vérifier le _well_initialized.
  //this->_well_initialized = xmlinit_is_ok and
      //                          this->languagefromto.well_initialized();


  qDebug() << "xmlreader.error=" << static_cast<int>(xmlreader.error());
}

/*______________________________________________________________________________

        DipyDoc::clear()

______________________________________________________________________________*/
void DipyDoc::clear(void) {
  this->_well_initialized = false;
  this->_internal_state = DipyDoc::INTERNALSTATE::NOT_YET_INITIALIZED;

  //this->errors.clear();
  //this->text2audio.clear();
  //this->audio2text.clear();
  //this->dipydoc_version.clear();
  //this->languagefromto.clear();
}
