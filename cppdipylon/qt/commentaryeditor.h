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

    ❏Dipylon❏ : qt/commentaryeditor.h

    Zone where the annotations are displayed.

*******************************************************************************/

#ifndef COMMENTARYEDITOR_H
#define COMMENTARYEDITOR_H

#include "qt/dipylonui.h"

#include <QTextEdit>

class DipylonUI;

/*______________________________________________________________________________

  CommentaryEditor class
______________________________________________________________________________*/

class CommentaryEditor : public QTextEdit
{
friend class DipylonUI;
friend class MainWindow;

    Q_OBJECT

public:
    CommentaryEditor(DipylonUI&);

    void set_the_appearance(void);
    void set_the_text_formats(void);
    void update_content__translation_expected(PosInTextRanges&);
    void update_aspect_from_dipydoc_aspect_informations(void);

protected:
    void keyReleaseEvent(QKeyEvent*);

private:
    // DipylonUI object linked to the editor :
    DipylonUI& current_dipylonui;

    // text formats, initialized by this->set_the_text_formats() :
    QTextCharFormat format_text = QTextCharFormat();
};

#endif
