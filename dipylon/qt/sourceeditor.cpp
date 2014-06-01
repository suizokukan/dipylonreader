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
  qDebug() << "SourceEditor::SourceEditor";
  this->setReadOnly(true);

  this->setStyleSheet("color: black;"
                      "background-color: #9ABCDE;"
                      "selection-color: yellow;"
                      "selection-background-color: blue;");

}

/*______________________________________________________________________________

        SourceEditor::mousePressEvent
______________________________________________________________________________*/
void SourceEditor::mousePressEvent(QMouseEvent* mouse_event)
{
    qDebug() << "SourceEditor::mousePressEvent";

    // mouse_event isn't used :
    Q_UNUSED(mouse_event);

    QTextCursor cursor = this->textCursor();
    TextPos x0 = cursor.position();
    qDebug() << "x0=" << x0;
    qDebug() << this->current_dipydoc->translations.is_inside(x0).to_str();

    QTextEdit::mousePressEvent(mouse_event);
}

/*______________________________________________________________________________

        SourceEditor::mouseReleaseEvent
_____________________________________________________________________________*/
void SourceEditor::mouseReleaseEvent(QMouseEvent* mouse_event)
{
    // mouse_event isn't used :
    Q_UNUSED(mouse_event);

    QTextCursor cursor = this->textCursor();

    if ( cursor.hasSelection() )
    {
      // some text has been selected :
      QString selected_txt = cursor.selectedText();
      TextPos x0 = cursor.selectionStart();
      TextPos x1 = cursor.selectionEnd();
      qDebug() << "SourceEditor::mouseReleaseEvent" << selected_txt << x0 << "," << x1;
      qDebug() << this->current_dipydoc->translations.is_inside(x0, x1).to_str();
      cursor.removeSelectedText();
      cursor.insertHtml( QString("<b>aaa</b>") );
    }

    QTextEdit::mouseReleaseEvent(mouse_event);
}
