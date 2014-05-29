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

    See the documentation in dipydoc.h .

*******************************************************************************/

#include "dipydoc.h"

/*______________________________________________________________________________

        DipyDoc::DipyDoc(QString) : initialize the object from the files present
                                    in "path", set the value of _well_initialized
                                    and of _internal_state;

______________________________________________________________________________*/
DipyDoc::DipyDoc(QString path)
{
  this->_well_initialized = true;
  this->_internal_state = this->INTERNALSTATE_OK;
  this->text = QString("");

  // does the path leads to the expected files ?
  this->check_path(path);
  if( this->_well_initialized == false )
  {
    return;
  }

  // let's open the text file :
  QFile src_file(path + "/" + this->TEXTFILE_NAME);
  src_file.open( QIODevice::ReadOnly | QIODevice::Text );
  QTextStream src_file_stream(&src_file);
  src_file_stream.setCodec("UTF-8");
  this->text = src_file_stream.readAll();

  // let's initialize the translations :
  this->translations[ { {8,26}, } ] = \
                "Le premier amour de Phébus";
  this->translations[ { {633, 649}, } ] = \
                "Ton arc peut bien transpercer toutes tes cibles";
}

/*______________________________________________________________________________

        DipyDoc::check_path() : check if path leads to the expected files.

        Modify _well_initialized and _internal_state if an error occurs.

        tests :

        o does "path" exists ?
        o is "path" a directory ?
        o does the file "path/text" exists ?
______________________________________________________________________________*/
void DipyDoc::check_path(QString path)
{

  // does "path" exists ?
  QFileInfo path_info = QFileInfo(path);
  if( path_info.exists() == false )
  {
    this->_well_initialized = false;
    this->_internal_state = this->INTERNALSTATE_UNKNOWNPATH;
    return;
  }

  // is "path" a directory ?
  if( path_info.isFile() == true )
  {
    this->_well_initialized = false;
    this->_internal_state = this->INTERNALSTATE_PATHISAFILE;
    return;
  }

  // does the file "path/text" exists ?
  QFileInfo text_info = QFileInfo(path + "/" + this->TEXTFILE_NAME);
  if( text_info.exists() == false )
  {
    this->_well_initialized = false;
    this->_internal_state = this->INTERNALSTATE_MISSINGTEXT;
    return;
  }

}

/*______________________________________________________________________________

        DipyDoc::internal_state() : return the value of the private
                                    "_internal_state" attribute

______________________________________________________________________________*/
int DipyDoc::internal_state(void) const
{
  return this->_internal_state;
}

/*______________________________________________________________________________

        DipyDoc::well_initialized() : return the value of the private
                                      "_well_initialized" attribute

______________________________________________________________________________*/
bool DipyDoc::well_initialized(void) const
{
  return this->_well_initialized;
}
