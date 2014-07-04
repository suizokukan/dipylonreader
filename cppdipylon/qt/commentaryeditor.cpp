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

    ❏Dipylon❏ : qt/commentaryeditor.cpp

    See commentaryeditor.h for the documentation.

*******************************************************************************/

#include "qt/commentaryeditor.h"

/*______________________________________________________________________________

  CommentaryEditor constructor

______________________________________________________________________________*/
CommentaryEditor::CommentaryEditor(DipylonUI& dipylonui) : current_dipylonui(dipylonui) {
  this->setReadOnly(true);
  this->set_the_appearance();
}

/*______________________________________________________________________________

  CommentaryEditor::set_the_appearance
______________________________________________________________________________*/
void CommentaryEditor::set_the_appearance(void) {
  this->setStyleSheet(fixedparameters::commentaryeditor_default_stylesheet);
}

/*______________________________________________________________________________

  CommentaryEditor::update_content__translation_expected

______________________________________________________________________________*/
void CommentaryEditor::update_content__translation_expected(PosInTextRanges& posintext) {

  PosInText x0 = posintext.min();
  PosInText x1 = posintext.max();

  QString matching_translations = this->current_dipylonui.get_translations_for(x0, x1);

  this->setPlainText(matching_translations);
}
