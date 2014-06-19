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

    ❏Dipylon❏ : qt/sourceeditor.h

    Zone where the source text is displayed.

*******************************************************************************/

#ifndef SOURCEEDITOR_H
#define SOURCEEDITOR_H

#include "fixedparameters.h"
#include "dipydoc/dipydoc.h"
#include "qt/dipylonui.h"
#include "pos/posintext/posintext.h"

#include <QTextEdit>
#include <QTextCharFormat>
#include <QList>

// $$$
#include <QDebug>

class DipylonUI;

/*______________________________________________________________________________

  SourceEditor class
______________________________________________________________________________*/
class SourceEditor : public QTextEdit
{
    Q_OBJECT

public:
         SourceEditor(DipylonUI&);
    void modify_the_text_format(int, PosInTextRanges&);
    void set_the_text_formats(void);
    void set_the_appearance(void);

protected:
    void mouseReleaseEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);

private:
    // DipylonUI object linked to the editor :
    DipylonUI& current_dipylonui;

    QTextCharFormat format_text_karaoke = QTextCharFormat();
};

#endif
