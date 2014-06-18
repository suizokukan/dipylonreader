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
SourceEditor::SourceEditor(DipyDoc& dipydoc) : current_dipydoc(dipydoc) {
  this->setReadOnly(true);
  this->setStyleSheet(parameters::source_editor_stylesheet);
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

void SourceEditor::modify_the_text_format(int dipylonui_mode, PosInTextRanges& positions) {

 QTextCharFormat fmt;
 fmt.setUnderlineStyle(QTextCharFormat::SingleUnderline);

 if( dipylonui_mode == 6123) {

   QTextCursor cur = this->textCursor();

   QList<QTextEdit::ExtraSelection> selections;

    for(auto &x0x1 : positions ) {
      qDebug() << "audio_position_changed=" << x0x1.first << "-" << x0x1.second;

      cur.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
      cur.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor, static_cast<int>(x0x1.first));
      cur.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, static_cast<int>(x0x1.second));
      QTextEdit::ExtraSelection sel = { cur, fmt };
      selections.append(sel);
    }

 this->setExtraSelections(selections);
 cur.clearSelection();
 }


}
