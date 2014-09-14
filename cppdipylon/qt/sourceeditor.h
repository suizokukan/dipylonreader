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

    ❏DipylonReader❏ : qt/sourceeditor.h

    Zone where the source text is displayed.

*******************************************************************************/

#ifndef CPPDIPYLON_QT_SOURCEEDITOR_H_
#define CPPDIPYLON_QT_SOURCEEDITOR_H_

#include <QDebug>

#include <QTextEdit>
#include <QTextCharFormat>
#include <QList>
#include <vector>

#include "dipydoc/dipydoc.h"
#include "qt/ui.h"
#include "qt/textformat.h"
#include "qt/blockformat.h"
#include "pos/posintext/posintext.h"


class DipylonUI;

/*______________________________________________________________________________

  SourceEditor class
______________________________________________________________________________*/
class SourceEditor : public QTextEdit {
  friend class DipylonUI;
  friend class MainWindow;

    Q_OBJECT

 public:
    explicit SourceEditor(DipylonUI&);
    PosInText corrected_cursor_position(void) const;
    void      load_text(const DipyDocSourceText&);
    void      modify_the_text_format(PosInTextRanges&);
    void      reset_all_text_format_to_default(void);
    void      set_the_appearance(void);
    void      update_aspect_from_dipydoc_aspect_informations(void);

 protected:
    void      keyReleaseEvent(QKeyEvent* keyboard_event);
    void      mouseMoveEvent(QMouseEvent* mouse_event);
    void      mouseReleaseEvent(QMouseEvent* mouse_event);
    void      mousePressEvent(QMouseEvent* mouse_event);
    void      paintEvent(QPaintEvent* ev);

 private:
    // DipylonUI object linked to the editor :
    DipylonUI& current_dipylonui;

    PosInTextRanges modified_chars = PosInTextRanges();
    // random value :
    #ifdef COMPILE_TO_32BITS_ARCHITECTURE
    std::size_t modified_chars_hash = 0x12345678;
    #else
    std::size_t modified_chars_hash = 0x123456789;
    #endif
};

#endif  // CPPDIPYLON_QT_SOURCEEDITOR_H_
