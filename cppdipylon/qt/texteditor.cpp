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

    ❏DipylonReader❏ : qt/texteeditor.cpp

    See texteeditor.h for the documentation.

*******************************************************************************/

#include "qt/texteditor.h"

/*______________________________________________________________________________

  TextEditor::TextEditor()

  class constructor
______________________________________________________________________________*/
TextEditor::TextEditor(UI& _ui) : ui(_ui) {
}

/*______________________________________________________________________________

  TextEditor::set_zoom_value
______________________________________________________________________________*/
void TextEditor::set_zoom_value(const signed int value) {
  this->zoom_value = value;

  if (value > 0) {
    this->zoomIn(value);
  } else {
    this->zoomOut(-value);
  }
}

/*______________________________________________________________________________

  TextEditor::zoom_in()
______________________________________________________________________________*/
void TextEditor::zoom_in(void) {
  this->zoom_value += 1;
  this->zoomIn(1);
}

/*______________________________________________________________________________

  TextEditor::zoom_out()
______________________________________________________________________________*/
void TextEditor::zoom_out(void) {
  this->zoom_value -= 1;
  this->zoomOut(1);
}
