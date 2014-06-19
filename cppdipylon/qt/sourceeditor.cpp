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

    ❏Dipylon❏ : qt/sourceeditor.cpp

    See sourceeditor.h for the documentation.

*******************************************************************************/

#include "qt/sourceeditor.h"

/*______________________________________________________________________________

  SourceEditor constructor
______________________________________________________________________________*/
SourceEditor::SourceEditor(DipylonUI& dipylonui) : current_dipylonui(dipylonui) {

  this->setReadOnly(true);

  this->set_the_text_formats();

  this->set_the_appearance();
}

/*______________________________________________________________________________

  SourceEditor::set_the_appearance
______________________________________________________________________________*/
void SourceEditor::set_the_appearance(void) {

  // everything but the text :
  const QString default_stylesheet = "background-color: #9ABCDE;"
                                     "selection-color: yellow;"
                                     "selection-background-color: blue;";
  this->setStyleSheet(default_stylesheet);

  // the text (default format) :
  this->setCurrentCharFormat(this->format_text_default);
}

/*______________________________________________________________________________

  SourceEditor::set_the_text_formats()

  Initialize this->format_text_*
______________________________________________________________________________*/
void SourceEditor::set_the_text_formats(void) {

  // null style format :
  auto default_brush = QBrush(Qt::white);
  this->format_text_default.setForeground(default_brush);

  // karaoke style format :
  auto karaoke_brush = QBrush(Qt::red);
  this->format_text_karaoke.setFontWeight(QFont::Bold);
  this->format_text_karaoke.setForeground(karaoke_brush);
}

/*______________________________________________________________________________

        SourceEditor::mousePressEvent
______________________________________________________________________________*/
void SourceEditor::mousePressEvent(QMouseEvent* mouse_event)
{
    QTextCursor cur = this->textCursor();

    qDebug() << "SourceEditor::mousePressEvent" << "pos=" << cur.position();

    //this->cursor.select(QTextCursor::WordUnderCursor);
    PosInText x0 =  static_cast<PosInText>(cur.position());
    qDebug() << "x0=" << x0;

    QTextEdit::mousePressEvent(mouse_event);
}

/*______________________________________________________________________________

        SourceEditor::mouseReleaseEvent
_____________________________________________________________________________*/
void SourceEditor::mouseReleaseEvent(QMouseEvent* mouse_event)
{
    QTextCursor cur = this->textCursor();

    qDebug() << "SourceEditor::mouseReleaseEvent" << "pos=" << cur.position();

    if ( cur.hasSelection() ) {
      QString selected_txt = cur.selectedText();
      PosInText x0 = static_cast<PosInText>( cur.selectionStart() );
      PosInText x1 = static_cast<PosInText>( cur.selectionEnd() );
      qDebug() << "SourceEditor::mouseReleaseEvent" << x0 << "-" << x1;
    }

    QTextEdit::mouseReleaseEvent(mouse_event);
}

/*______________________________________________________________________________

        SourceEditor::modify_the_text_format

        This function modify the appearence of the text BUT DOES NOT UPDATE
        the .modified_chars_hash attribute.
_____________________________________________________________________________*/
void SourceEditor::modify_the_text_format(PosInTextRanges& positions) {

  if( this->current_dipylonui.reading_mode == DipylonUI::READINGMODES::KARAOKE) {

   QTextCursor cur = this->textCursor();

   // first we set the ancient modified text's appearance to "default" :
   QList<QTextEdit::ExtraSelection> selections;

    for(auto &x0x1 : this->modified_chars ) {
      cur.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
      cur.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor, static_cast<int>(x0x1.first));
      cur.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, static_cast<int>(x0x1.second));
      QTextEdit::ExtraSelection sel = { cur, this->format_text_default };
      selections.append(sel);
    }
    this->setExtraSelections(selections);

    selections.clear();

   // ... and then we modify the new text's appearance :
    for(auto &x0x1 : positions ) {
      qDebug() << "SourceEditor::modify_the_text_format=" << static_cast<int>(x0x1.first) << "-" << static_cast<int>(x0x1.second);

      cur.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
      cur.movePosition(QTextCursor::NextCharacter,
                       QTextCursor::MoveAnchor,
                       static_cast<int>(x0x1.first));
      cur.movePosition(QTextCursor::NextCharacter,
                       QTextCursor::KeepAnchor,
                       static_cast<int>(x0x1.second - x0x1.first));
      QTextEdit::ExtraSelection sel = { cur, this->format_text_karaoke };
      selections.append(sel);
    }
    this->setExtraSelections(selections);

    this->modified_chars = positions;

    cur.clearSelection();
 }

}
