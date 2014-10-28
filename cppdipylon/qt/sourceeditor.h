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
#include <QPainter>

#include <vector>

#include "debugmsg/debugmsg.h"
#include "dipydoc/dipydoc.h"
#include "dipydoc/dipydocsyntagmas.h"
#include "pos/posintext/posintext.h"
#include "qt/blockformat.h"
#include "qt/icons.h"
#include "qt/readingmodes.h"
#include "qt/texteditor.h"
#include "qt/textformat.h"

extern Icons icons;

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
                           const DipyDoc *      _dipydoc,
                           QMediaPlayer *       _audio_player,
                           QAction *            _audiocontrols_playAct,
                           QAction *            _audiocontrols_stopAct,
                           bool &               _blocked_commentaries,
                           int &                _amode_level,
                           QWidget*             _parent);

    PosInText corrected_cursor_position(void) const;
    void      load_text(void);
    void      modify_the_text_format__amode(Syntagma* syntagma);
    void      modify_the_text_format__amode_recursively(Syntagma* current_syntagma,
                                                        QList<QTextEdit::ExtraSelection> & selections);
    void      modify_the_text_format__rmode__lmode(const PosInTextRanges & posintext);
    void      reset_all_text_format_to_default(void);
    void      set_the_appearance(void);
    void      update_aspect_from_dipydoc_aspect_informations(void);
    void      update_icons(void);

 signals:
    void      signal__close_the_current_dipydoc(void);
    void      signal__open_a_new_dipydoc(void);
    void      signal__source_zone_update_icons(void);
    void      signal__update_translation_in_commentary_zone(const PosInTextRanges & posintext);
    void      signal__update_note_in_commentary_zone(const QString& textnote);

 protected:
    void      keyReleaseEvent(QKeyEvent* keyboard_event);
    void      mouseMoveEvent(QMouseEvent* mouse_event);
    void      mouseReleaseEvent(QMouseEvent* mouse_event);
    void      paintEvent(QPaintEvent* event);

 private:
    ReadingMode &        readingmode;
    ReadingModeDetails & readingmode_details;
    const DipyDoc *      dipydoc;
    QMediaPlayer*        audio_player = nullptr;

    QAction*             audiocontrols_playAct = nullptr;
    QAction*             audiocontrols_stopAct = nullptr;

    bool &               blocked_commentaries;

    int &                amode_level;

    PosInTextRanges      modified_chars = PosInTextRanges();

    Syntagma*            focused_syntagma = nullptr;

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
