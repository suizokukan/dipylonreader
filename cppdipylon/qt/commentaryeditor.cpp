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

    ❏DipylonReader❏ : qt/commentaryeditor.cpp

    See commentaryeditor.h for the documentation.

*******************************************************************************/

#include "qt/commentaryeditor.h"

/*______________________________________________________________________________

  CommentaryEditor constructor

______________________________________________________________________________*/
CommentaryEditor::CommentaryEditor(const QString & splitter_name,
                                   const DipyDoc * _dipydoc,
                                   bool & _blocked_commentaries,
                                   QWidget *_parent) : TextEditor(_parent),
                                                       dipydoc(_dipydoc),
                                                       blocked_commentaries(_blocked_commentaries) {
  QString object_name(splitter_name + "::commentary zone::editor");
  this->setObjectName(object_name);

  this->setReadOnly(true);
  this->set_zoom_value(this->zoom_value);
  this->update_aspect_from_dipydoc_aspect_informations();
}

/*_____________________________________________________________________________

  CommentaryEditor::set_the_appearance
______________________________________________________________________________*/
void CommentaryEditor::set_the_appearance(void) {
  DebugMsg() << "[CommentaryEditor::set_the_appearance] setStyleSheet = " << this->dipydoc->commentaryeditor_stylesheet;
  this->setStyleSheet(this->dipydoc->commentaryeditor_stylesheet);
}

/*______________________________________________________________________________

  CommentaryEditor::set_the_text_formats

  Initialize this->format_text_*
______________________________________________________________________________*/
void CommentaryEditor::set_the_text_formats(void) {
  this->format_text = this->dipydoc->commentaryeditor_textformat.qtextcharformat();
}

/*______________________________________________________________________________

  CommentaryEditor::update_aspect_from_dipydoc_aspect_informations
______________________________________________________________________________*/
void CommentaryEditor::update_aspect_from_dipydoc_aspect_informations(void) {
  this->set_the_text_formats();
  this->set_the_appearance();
}

/*______________________________________________________________________________

  CommentaryEditor::update_content__commentary_expected
______________________________________________________________________________*/
void CommentaryEditor::update_content__commentary_expected(const QString & textnote) {
    this->clear();

    QTextCursor cur = this->textCursor();
    cur.setCharFormat(this->format_text);
    cur.insertText(textnote);
}

/*______________________________________________________________________________

  CommentaryEditor::update_content__translation_expected

  only if this->blocked_commentaries is false.
______________________________________________________________________________*/
void CommentaryEditor::update_content__translation_expected(const PosInTextRanges& posintext) {
  if (this->blocked_commentaries == false) {
    PosInText x0 = posintext.min();
    PosInText x1 = posintext.max();

    QString matching_translations = this->dipydoc->get_translations_for(x0, x1);

    this->clear();

    QTextCursor cur = this->textCursor();
    cur.setCharFormat(this->format_text);
    cur.insertText(matching_translations);
  }
}
