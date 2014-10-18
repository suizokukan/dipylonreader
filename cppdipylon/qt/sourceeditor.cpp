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

    ❏DipylonReader❏ : qt/sourceeditor.cpp

    See sourceeditor.h for the documentation.

*******************************************************************************/

#include "qt/sourceeditor.h"

/*______________________________________________________________________________

  SourceEditor constructor
______________________________________________________________________________*/
SourceEditor::SourceEditor(const QString & splitter_name,
                           ReadingMode* _readingmode,
                           ReadingModeDetails*  _readingmode_details,
                           const DipyDoc & _dipydoc,
                           QMediaPlayer* _audio_player,
                           QAction* _audiocontrols_playAct,
                           QAction* _audiocontrols_stopAct,
                           bool* _selected_text_and_blocked_commentaries,
                           QWidget* _parent) : TextEditor(_parent),
                                               readingmode(_readingmode),
                                               readingmode_details(_readingmode_details),
                                               dipydoc(_dipydoc),
                                               audio_player(_audio_player),
                                               audiocontrols_playAct(_audiocontrols_playAct),
                                               audiocontrols_stopAct(_audiocontrols_stopAct),
                                               selected_text_and_blocked_commentaries(_selected_text_and_blocked_commentaries) {
  DebugMsg() << "SourceEditor::SourceEditor() : entry point";

  QString object_name(splitter_name + "::source zone::editor");
  this->setObjectName(object_name);

  this->setReadOnly(true);
  this->setMouseTracking(true);
  this->update_aspect_from_dipydoc_aspect_informations();

  DebugMsg() << "SourceEditor::SourceEditor() : exit point";
}

/*______________________________________________________________________________

  SourceEditor::corrected_cursor_position()

  Return the cursor position, "corrected" since the characters before the
  text (=title, intro, ...) are not taken in account. E.g. if this function
  returns 0, it means that the cursor is on the first character of the
  text.
______________________________________________________________________________*/
PosInText SourceEditor::corrected_cursor_position(void) const {
  return static_cast<PosInText>(this->textCursor().position()) - \
         static_cast<PosInText>(this->number_of_chars_before_source_text);
}

/*______________________________________________________________________________

        SourceEditor::keyReleaseEvent()

        See http://qt-project.org/doc/qt-5/qt.html#Key-enum for the list of
        constants like "Qt::Key_Space".

  known cases :

  [1] space
    [1.1] LMODE + PLAYING -> LMODE + ON PAUSE
    [1.2] LMODE + ON PAUSE -> LMODE + PLAYING
    [1.3] LMODE + UNDEFINED : nothing to do.
    [1.4] UNDEFINED reading mode -> LMODE + PLAYING
  [2] arrows
  [3] other keys

______________________________________________________________________________*/
void SourceEditor::keyReleaseEvent(QKeyEvent * keyboard_event) {
  DebugMsg() << "SourceEditor::keyReleaseEvent" << keyboard_event->key();

  switch (keyboard_event->key()) {
    //......................................................................
    // [1] space
    case Qt::Key_Space : {
      switch (*(this->readingmode)) {
        case READINGMODE::READINGMODE_LMODE: {
          switch (*(this->readingmode_details)) {
            //......................................................................
            // [1.1] LMODE + PLAYING -> LMODE + ON PAUSE
            case READINGMODEDETAILS::READINGMODEDETAIL_LMODE_PLAYING: {
              *(this->readingmode_details) = READINGMODEDETAILS::READINGMODEDETAIL_LMODE_ONPAUSE;
              this->audiocontrols_playAct->setIcon(*(icons.audio_pause));
              this->audio_player->pause();
              break;
            }

            //......................................................................
            // [1.2] LMODE + ON PAUSE -> LMODE + PLAYING
            case READINGMODEDETAILS::READINGMODEDETAIL_LMODE_ONPAUSE: {
              *(this->readingmode_details) = READINGMODEDETAILS::READINGMODEDETAIL_LMODE_PLAYING;
              this->audiocontrols_playAct->setIcon(*(icons.audio_play));
              this->audio_player->play();
              break;
            }

            // [1.3] LMODE + UNDEFINED : nothing to do.
            default : {
              break;
            }
          }

          break;
        }

        //..........................................................................
        // [1.4] UNDEFINED reading mode -> LMODE + PLAYING
        default: {
            *(this->readingmode) = READINGMODE::READINGMODE_LMODE;
            *(this->readingmode_details) = READINGMODEDETAILS::READINGMODEDETAIL_LMODE_PLAYING;
            this->audiocontrols_playAct->setIcon(*(icons.audio_play));
            this->audio_player->play();
            break;
        }
      }

      break;
    }

    //......................................................................
    // [2] arrows
    case Qt::Key_Left :
    case Qt::Key_Right : {
      switch (*(this->readingmode)) {
        case READINGMODE::READINGMODE_LMODE: {
          switch (*(this->readingmode_details)) {
            case READINGMODEDETAILS::READINGMODEDETAIL_LMODE_PLAYING: {
              break;
            }
            case READINGMODEDETAILS::READINGMODEDETAIL_LMODE_STOP :
            case READINGMODEDETAILS::READINGMODEDETAIL_LMODE_ONPAUSE : {
              break;
            }
            default : {
              break;
            }
          }
          break;
        }
        default : {
          break;
        }
      }
      break;
    }

    // [3] other keys :
    default : {
      break;
    }
  }

  QTextEdit::keyReleaseEvent(keyboard_event);
}

/*______________________________________________________________________________

        SourceEditor::load_text()
______________________________________________________________________________*/
void SourceEditor::load_text(const DipyDocSourceText& source_text) {
  this->clear();

  QTextCursor cur = this->textCursor();
  QTextDocument* qtextdocument = this->document();

  /*
     title
  */
  if (this->dipydoc.title.found == true) {
    // format :
    QTextCharFormat title_qtextcharformat = this->dipydoc.title.textformat.qtextcharformat();
    QTextBlockFormat title_qtextblockformat = this->dipydoc.title.blockformat.qtextblockformat();

    cur.insertBlock(title_qtextblockformat, title_qtextcharformat);

    // text :
    cur.insertText(this->dipydoc.title.text);
    cur.insertText("\n");
  }

  /*
    introduction
  */
  if (this->dipydoc.introduction.found == true) {
    // format :
    QTextCharFormat introduction_qtextcharformat = this->dipydoc.introduction.textformat.qtextcharformat();
    QTextBlockFormat introduction_qtextblockformat = this->dipydoc.introduction.blockformat.qtextblockformat();

    cur.insertBlock(introduction_qtextblockformat, introduction_qtextcharformat);

    // text :
    cur.insertText(this->dipydoc.introduction.text);
    cur.insertText("\n");
  }

  /*
     lettrine ("initial") + text
  */

  /*
    new block for the lettrine and the text :
  */
  QTextCharFormat text_qtextcharformat = this->dipydoc.sourceeditor_default_textformat.qtextcharformat();
  QTextBlockFormat text_blockformat = this->dipydoc.source_text.blockformat.qtextblockformat();

  // inserting the block :
  cur.insertBlock(text_blockformat, text_qtextcharformat);

  // adding the lettrine :
  if (this->dipydoc.lettrine.found == true) {
    int aspectratio = this->dipydoc.lettrine.aspectratio;

    qtextdocument->addResource(QTextDocument::ImageResource,
                               QUrl("lettrine"),
                               this->dipydoc.lettrine.image);

    QTextImageFormat qtextimageformat = QTextImageFormat();
    /*
       the image's size is reduced according to the "aspectratio" variable.

       It is noteworthy that the height is automatically resized so that the
       image' proportions are intact after the resizing.
    */
    qtextimageformat.setWidth(this->width() / aspectratio);

    qtextimageformat.setName("lettrine");

    cur.insertImage(qtextimageformat,
                    this->dipydoc.lettrine.position_in_text_frame.position());
  }

  /*
    Before the source text, the title and the introduction may be inserted.
    This attribute stores the number of characters appearing before
    the source text.
  */
  this->number_of_chars_before_source_text = cur.position();

  cur.setCharFormat(text_qtextcharformat);
  cur.insertText(source_text.text);
}

/*______________________________________________________________________________

        SourceEditor::modify_the_text_format()

        This function modify the appearence of the text BUT DOES NOT UPDATE
        the .modified_chars_hash attribute.
7_____________________________________________________________________________*/
void SourceEditor::modify_the_text_format(const PosInTextRanges& positions) {

  switch (*(this->readingmode)) {
    /*
      rmode, lmode
    */
    case READINGMODE::READINGMODE_RMODE :
    case READINGMODE::READINGMODE_LMODE : {
      int shift = this->number_of_chars_before_source_text;

      QTextCursor cur = this->textCursor();

      // first we set the ancient modified text's appearance to "default" :
      QList<QTextEdit::ExtraSelection> selections;

      for (auto &x0x1 : this->modified_chars) {
        cur.setPosition(static_cast<int>(x0x1.first) + shift, QTextCursor::MoveAnchor);
        cur.setPosition(static_cast<int>(x0x1.second) + shift, QTextCursor::KeepAnchor);
        QTextEdit::ExtraSelection sel = { cur,
                                          this->dipydoc.sourceeditor_default_textformat.qtextcharformat() };
        selections.append(sel);
      }
      this->setExtraSelections(selections);

      selections.clear();

      // ... and then we modify the new text's appearance :
      for (auto &x0x1 : positions) {
        cur.setPosition(static_cast<int>(x0x1.first) + shift, QTextCursor::MoveAnchor);
        cur.setPosition(static_cast<int>(x0x1.second) + shift, QTextCursor::KeepAnchor);

        QTextEdit::ExtraSelection sel;
        if (*(this->readingmode) == READINGMODE::READINGMODE_RMODE) {
          sel = { cur,
                  this->dipydoc.sourceeditor_rmode_textformat.qtextcharformat() };
        }
        if (*(this->readingmode) == READINGMODE::READINGMODE_LMODE) {
          sel = { cur,
                  this->dipydoc.sourceeditor_lmode_textformat.qtextcharformat() };
        }

        selections.append(sel);
      }
      this->setExtraSelections(selections);

      this->modified_chars = positions;

      cur.clearSelection();

      break;
    }

    default : {
      break;
    }
  }
}

/*______________________________________________________________________________

        SourceEditor::mouseMoveEvent()
______________________________________________________________________________*/
void SourceEditor::mouseMoveEvent(QMouseEvent* mouse_event) {
  if (*(this->selected_text_and_blocked_commentaries) == false) {
    switch (*(this->readingmode_details)) {
      case READINGMODEDETAILS::READINGMODEDETAIL_RMODE : {
        QTextCursor cur = this->cursorForPosition(mouse_event->pos());
        int shift = this->number_of_chars_before_source_text;
        PosInText cursor_position = static_cast<PosInText>(cur.position()) - static_cast<PosInText>(shift);

        // where are the characters linked to "cursor_position" ?
        PosInTextRanges pos_in_text = this->dipydoc.translation_contains(cursor_position);

        std::size_t text_ranges_hash = pos_in_text.get_hash();

        // if the user is really on another text's segment ...
        if (text_ranges_hash != this->modified_chars_hash) {
          // ... we refresh the ui :

          // the function modifies the appearence of such characters :
          this->modify_the_text_format(pos_in_text);

          // hash update :
          this->modified_chars_hash = text_ranges_hash;

          /*
            TODO
          this->commentary_editor->update_content__translation_expected(pos_in_text);
          */
        }

        break;
      }

      default : {
        break;
      }
    }
  }
  QTextEdit::mouseMoveEvent(mouse_event);
}

/*______________________________________________________________________________

        SourceEditor::mouseReleaseEvent()

        (1) with selection
        (2) without selection
_____________________________________________________________________________*/
void SourceEditor::mouseReleaseEvent(QMouseEvent* mouse_event) {
  QTextCursor cur = this->textCursor();
  DebugMsg() << "SourceEditor::mouseReleaseEvent";

  /*............................................................................
    (1) RMODE + selection
  ............................................................................*/
  if (*(this->readingmode_details) == READINGMODEDETAILS::READINGMODEDETAIL_RMODE && cur.hasSelection() == true) {
    DebugMsg() << "SourceEditor::mouseReleaseEvent; RMODE + selection";

    int shift = this->number_of_chars_before_source_text;
    PosInText x0 = static_cast<PosInText>(cur.selectionStart() - shift);
    PosInText x1 = static_cast<PosInText>(cur.selectionEnd() - shift);

    // where are the characters in the translations linked to "x0-x1" ?
    PosInTextRanges pos_in_text =  this->dipydoc.translation_contains(x0, x1);
    DebugMsg() << "... pos_in_text=" << pos_in_text.repr();

    /*
      we refresh the ui :
    */
    std::size_t text_ranges_hash = pos_in_text.get_hash();

    // the function modifies the appearence of such characters :
    this->modify_the_text_format(pos_in_text);

    // hash update :
    this->modified_chars_hash = text_ranges_hash;

    *(this->selected_text_and_blocked_commentaries) = false;
    /*
      TODO
    this->commentary_editor->update_content__translation_expected(pos_in_text);
    */
    *(this->selected_text_and_blocked_commentaries) = true;

    /*
      TODO (la méthode appartient au parent)
    this->update_icons();
    */

    return;
  }

  // no selection ? we don't protect anymore the commentary zone :
  if (cur.hasSelection() == false) {
    *(this->selected_text_and_blocked_commentaries) = false;
  }

  /*............................................................................
    (2) without selection
  ............................................................................*/
  PosInText cursor_position = this->corrected_cursor_position();

  switch (*(this->readingmode)) {
    case READINGMODE::READINGMODE_LMODE: {
      switch (*(this->readingmode_details)) {
        //......................................................................
        // LMODE + ON PAUSE
        // LMODE + STOP
        case READINGMODEDETAILS::READINGMODEDETAIL_LMODE_ONPAUSE:
        case READINGMODEDETAILS::READINGMODEDETAIL_LMODE_STOP : {
          // where are the characters linked to "cursor_position" ?
          PTRangesAND2PosAudio found_position = this->dipydoc.text2audio_contains(cursor_position);
          PosInTextRanges pos_in_text = found_position.first;

          std::size_t text_ranges_hash = pos_in_text.get_hash();

          // if the user has really click on another text's segment ...
          if (text_ranges_hash != this->modified_chars_hash) {
            // ... we refresh the ui :

            // the function modifies the appearence of such characters :
            this->modify_the_text_format(pos_in_text);

            // hash update :
            this->modified_chars_hash = text_ranges_hash;

            /*
              TODO
            this->commentary_editor->update_content__translation_expected(pos_in_text);
            */
          }
          break;
        }
        //......................................................................
        // LMODE + PLAYING
        case READINGMODEDETAILS::READINGMODEDETAIL_LMODE_PLAYING : {
          // where are the characters linked to "cursor_position" ?
          PTRangesAND2PosAudio found_position = this->dipydoc.text2audio_contains(cursor_position);
          PairOfPosInAudio pos_in_audio = found_position.second;

          // we jump to the beginning of the audio gap (pos_in_audio.first, pos_in_audio.second) :
          this->audio_player->setPosition(pos_in_audio.first);
          break;
        }
        default : {
          break;
        }
      }
      break;
    }

    // other reading modes.
    default : {
      break;
    }
  }

  QTextEdit::mouseReleaseEvent(mouse_event);
}

/*______________________________________________________________________________

  SourceEditor::paintEvent()

  doc : http://qt-project.org/doc/qt-4.8/qpainterpath.html#cubicTo

  sur QPen : http://qt-project.org/doc/qt-4.8/qpen.html
______________________________________________________________________________*/
void SourceEditor::paintEvent(QPaintEvent* ev) {
  /*
  // starting point :
  QTextCursor current_posintext_pos = this->textCursor();
  QPoint current_xy_pos = this->mapFromGlobal(QCursor().pos());
  // end point :
  QTextCursor dest_posintext_pos = this->textCursor();
  dest_posintext_pos.movePosition(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor, 100);
  QRect dest_rect = this->cursorRect(dest_posintext_pos);

  // à étudier (???)
  // http://www.qtcentre.org/threads/32130-Getting-the-bounding-rect-of-a-character-in-a-QTextDocument
  // http://elonen.iki.fi/code/misc-notes/char-bbox-qtextedit/

  //const QRect rec = ev->rect();
  QPainter p(viewport());

  float x0 = current_xy_pos.x();
  float y0 = current_xy_pos.y();
  float x1 = dest_rect.x();
  float y1 = dest_rect.y();

  QPointF startingpoint = QPointF(x0, y0);
  QPointF endpoint = QPointF(x1, y1);

  p.setPen(QPen(QBrush("red"), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));

  // arrow body :
  QPainterPath path = QPainterPath(startingpoint);  // starting point
  path.cubicTo(QPointF(x0*1.3, y0*0.9),
               QPointF(x0*1.1, y0*0.7),
               endpoint);  // p1, p2, endpoint
  p.drawPath(path);

  p.setPen(QPen(QBrush("yellow"), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));

  p.drawRect(x0-2, y0-2, 4, 4);

  p.drawRect(x1-1, y1-1, 2, 2);

  this->update();
  */

  // arrow head :
  /*  const double cos = -0.707; //0.866;
  const double sin =  0.707; //0.500.
  QPointF end1 = QPointF(
        x1 + (dx * cos + dy * -sin),
        y1 + (dx * sin + dy * cos));
  QPointF end2 = QPointF(
        x1 + (dx * cos + dy * sin),
        y1 + (dx * -sin + dy * cos));
  p.drawLine(endpoint, end1);
  p.drawLine(endpoint, end2);
  */

  QTextEdit::paintEvent(ev);
}

/*______________________________________________________________________________

        SourceEditor::reset_all_text_format_to_default()

        This function resets the appearance of all the text.
_____________________________________________________________________________*/
void SourceEditor::reset_all_text_format_to_default(void) {

  QTextCursor cur = this->textCursor();

  QList<QTextEdit::ExtraSelection> selections;
  this->setExtraSelections(selections);

  cur.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
  cur.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
  QTextEdit::ExtraSelection sel = { cur,
                                    this->dipydoc.sourceeditor_default_textformat.qtextcharformat() };
  selections.append(sel);

  cur.clearSelection();
}

/*______________________________________________________________________________

  SourceEditor::set_the_appearance()
______________________________________________________________________________*/
void SourceEditor::set_the_appearance(void) {
  this->setStyleSheet(this->dipydoc.sourceeditor_stylesheet);
}

/*______________________________________________________________________________

  SourceEditor::update_aspect_from_dipydoc_aspect_informations()
______________________________________________________________________________*/
void SourceEditor::update_aspect_from_dipydoc_aspect_informations(void) {
  this->set_the_appearance();
}
