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

*******************************************************************************/

#include "sourceeditor.h"

/*______________________________________________________________________________

        SourceEditor::SourceEditor(int*, QWidget) : constructor
_____________________________________________________________________________*/
SourceEditor::SourceEditor(QWidget *parent, DipyDoc* current_dipydoc) :          \
QTextEdit(parent), current_dipydoc(current_dipydoc)
{
  qDebug() << "SourceEditor::SourceEditor : enter";
  /*CORE DUMPED
  this->setReadOnly(true);

  this->setStyleSheet("color: black;"
                      "background-color: #9ABCDE;"
                      "selection-color: yellow;"
                      "selection-background-color: blue;");

  QFont font; //"DejaVu LGC Sans Mono");
  //font.setStyleHint(QFont::Monospace);
  font.setStyleHint(QFont::TypeWriter);
  font.setStyle(QFont::StyleItalic);
  this->setFont(font);
  */
  qDebug() << "SourceEditor::SourceEditor : exit";
}

/*______________________________________________________________________________

        SourceEditor::~SourceEditor destructor
_____________________________________________________________________________*/
SourceEditor::~SourceEditor(void)
{
  qDebug() << "SourceEditor::~SourceEditor : enter";
  delete this->current_dipydoc;
  qDebug() << "SourceEditor::~SourceEditor : exit";
}

/*______________________________________________________________________________

        SourceEditor::mousePressEvent
______________________________________________________________________________*/
void SourceEditor::mousePressEvent(QMouseEvent* mouse_event)
{
    qDebug() << "SourceEditor::mousePressEvent : enter";
    /*CORE DUMPED
    QTextCursor cursor = this->textCursor();

    qDebug() << "SourceEditor::mousePressEvent" << "pos=" << cursor.position();

    //this->cursor.select(QTextCursor::WordUnderCursor);
    TextPos x0 =  cursor.position();
    qDebug() << "x0=" << x0;
    qDebug() << this->current_dipydoc->translations.is_inside(x0).to_str();

    QTextEdit::mousePressEvent(mouse_event);
    */
    qDebug() << "SourceEditor::mousePressEvent : exit";
}

/*______________________________________________________________________________

        SourceEditor::mouseReleaseEvent
_____________________________________________________________________________*/
void SourceEditor::mouseReleaseEvent(QMouseEvent* mouse_event)
{
    QTextCursor cursor = this->textCursor();

    qDebug() << "SourceEditor::mouseReleaseEvent" << "pos=" << cursor.position();
    /*CORE DUMPED
    if ( cursor.hasSelection() )
    {
      // some text has been selected :
      QString selected_txt = cursor.selectedText();
      TextPos x0 = cursor.selectionStart();
      TextPos x1 = cursor.selectionEnd();
      qDebug() << "SourceEditor::mouseReleaseEvent" << selected_txt << x0 << "," << x1;
      qDebug() << this->current_dipydoc->translations.is_inside(x0, x1).to_str();
      //cursor.removeSelectedText();
      //cursor.insertHtml( QString("<b>aaa</b>") );

      // formatter : http://qt-project.org/doc/qt-5/qtextcharformat.html
      QTextCharFormat fmt1;
      fmt1.setUnderlineStyle(QTextCharFormat::SingleUnderline);
      fmt1.setBackground(QBrush(QColor(240,230,220)));

      QTextCharFormat fmt2;
      fmt2.setUnderlineStyle(QTextCharFormat::WaveUnderline);
      fmt2.setFontWeight(QFont::Weight(QFont::Bold)); // http://qt-project.org/doc/qt-5/qfont.html#Weight-enum
      fmt2.setForeground(QColor(255,0,10));
      fmt2.setFontItalic(true);
      QTextCharFormat fmt3;
      fmt3.setUnderlineStyle(QTextCharFormat::DashUnderline);
      fmt3.setUnderlineColor(QColor(200,100,50));
      fmt3.setFontStrikeOut(true);
      fmt3.setToolTip( "111111111111111111111111111" );

      // 1ère sélection = le mot souligné
      QList<QTextEdit::ExtraSelection> selections;
      QTextEdit::ExtraSelection sel = { cursor, fmt1 };
      selections.append(sel);
      // 2e sélection : 10 caractères + loin, sélectionner les 15 caractères qui suivent
      // moveoperation : http://qt-project.org/doc/qt-5/qtextcursor.html#MoveOperation-enum
      // movemode : http://qt-project.org/doc/qt-5/qtextcursor.html#MoveMode-enum
      cursor.clearSelection();
      cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor, 20);
      cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::QTextCursor::KeepAnchor, 15);
      sel = { cursor, fmt2 };
      selections.append(sel);
      // 3ème sélection : sélectionner le texte en [2,30] :
      cursor.clearSelection();
      cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
      cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor, 2);
      cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, 20);
      sel = { cursor, fmt3 };
      selections.append(sel);
      // appliquer la sélection :
      this->setExtraSelections(selections);
      // faire disparaître la sélection :
      cursor.clearSelection();
      this->setTextCursor(cursor);

      this->show();
    }
    */
    QTextEdit::mouseReleaseEvent(mouse_event);
}
