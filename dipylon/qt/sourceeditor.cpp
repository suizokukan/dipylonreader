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
SourceEditor::SourceEditor(DipyDoc* current_dipydoc, QWidget *parent) :  \
QTextEdit(parent), current_dipydoc(current_dipydoc)
{
  this->setReadOnly(true);

  delete current_dipydoc;
  current_dipydoc = new DipyDoc("../texts/Ovid_M_I_452_567/");
  this->setPlainText(current_dipydoc->text);
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
      qDebug() << selected_txt \
               << cursor.position() - selected_txt.length() << "," << cursor.position();
    }
}
