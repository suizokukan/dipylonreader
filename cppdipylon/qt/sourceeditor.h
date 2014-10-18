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

#include <QAction>
#include <QTextEdit>
#include <QTextCharFormat>
#include <QList>
#include <QMediaPlayer>

#include <vector>

#include "debugmsg/debugmsg.h"
#include "dipydoc/dipydoc.h"
#include "pos/posintext/posintext.h"
#include "qt/blockformat.h"
#include "qt/icons.h"
#include "qt/readingmodes.h"
#include "qt/texteditor.h"
#include "qt/textformat.h"

/*______________________________________________________________________________

  SourceEditor class
______________________________________________________________________________*/
class SourceEditor : public TextEditor {
  friend class MainWindow;
  friend class SourceZone;

    Q_OBJECT

 public:
    explicit  SourceEditor(const QString &      splitter_name,
                           ReadingMode &        _readingmode,
                           ReadingModeDetails & _readingmode_details,
                           const DipyDoc &      _dipydoc,
                           QMediaPlayer *       _audio_player,
                           QAction *            _audiocontrols_playAct,
                           QAction *            _audiocontrols_stopAct,
                           bool &               _selected_text_and_blocked_commentaries,
                           QWidget*             _parent);

    PosInText corrected_cursor_position(void) const;
    void      load_text(const DipyDocSourceText&);
    void      modify_the_text_format(const PosInTextRanges&);
    void      reset_all_text_format_to_default(void);
    void      set_the_appearance(void);
    void      update_aspect_from_dipydoc_aspect_informations(void);
    void      update_icons(void);


 protected:
    void      keyReleaseEvent(QKeyEvent* keyboard_event);
    void      mouseMoveEvent(QMouseEvent* mouse_event);
    void      mouseReleaseEvent(QMouseEvent* mouse_event);
    void      paintEvent(QPaintEvent* event);

 private:
    ReadingMode &        readingmode;
    ReadingModeDetails & readingmode_details;
    const DipyDoc &      dipydoc;
    QMediaPlayer*        audio_player = nullptr;

    QAction*             audiocontrols_playAct = nullptr;
    QAction*             audiocontrols_stopAct = nullptr;

    bool &               selected_text_and_blocked_commentaries;

    PosInTextRanges modified_chars = PosInTextRanges();
    // random value :
    #ifdef COMPILE_TO_32BITS_ARCHITECTURE
    std::size_t modified_chars_hash = 0x12345678;
    #else
    std::size_t modified_chars_hash = 0x123456789;
    #endif

    /*
       the number of characters appearing before the source text.
       initialized by SourceEditor::load_text()
    */
    int number_of_chars_before_source_text = 0;
};

#endif  // CPPDIPYLON_QT_SOURCEEDITOR_H_
