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

    ❏DipylonReader❏ : qt/texteditor.h

    Parent class of CommentaryEditor and SourceEditor.

*******************************************************************************/

#ifndef CPPDIPYLON_QT_TEXTEDITOR_H_
#define CPPDIPYLON_QT_TEXTEDITOR_H_

#include <QTextEdit>
#include <QWheelEvent>

class UI;

/*______________________________________________________________________________

  TextEditor class
______________________________________________________________________________*/
class TextEditor : public QTextEdit {
friend class CommentaryEditor;
friend class MainWindow;
friend class SourceEditor;
friend class UI;

    Q_OBJECT

 public:
    explicit  TextEditor(UI& _ui);

 private:
    // UI object linked to the editor :
    UI& ui;

    int      zoom_value = 0;

    void     zoom_in(void);
    void     zoom_out(void);
    void     set_zoom_value(const signed int value);

 protected:
    void     wheelEvent(QWheelEvent* e);
};

#endif  // CPPDIPYLON_QT_TEXTEDITOR_H_
