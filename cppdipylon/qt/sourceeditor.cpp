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

    See sourceeditor.h for the documentation.

*******************************************************************************/

#include "qt/sourceeditor.h"

/*______________________________________________________________________________

  SourceEditor constructor
______________________________________________________________________________*/
SourceEditor::SourceEditor(DipylonUI& dipylonui) : current_dipylonui(dipylonui) {
  this->setReadOnly(true);

  this->update_aspect_from_dipydoc_aspect_informations();
}

/*______________________________________________________________________________

        SourceEditor::keyReleaseEvent

        See http://qt-project.org/doc/qt-5/qt.html#Key-enum for the list of
        constants like "Qt::Key_Space".

  known cases :

  o [1.1] KARAOKE + PLAYING -> KARAOKE + ON PAUSE
  o [1.2] KARAOKE + ON PAUSE -> KARAOKE + PLAYING
  o [1.3] KARAOKE + UNDEFINED : nothing to do.
  o [2] UNDEFINED reading mode -> KARAOKE + PLAYING
______________________________________________________________________________*/
void SourceEditor::keyReleaseEvent(QKeyEvent * keyboard_event) {
  DipylonUI& ui = this->current_dipylonui;
  qDebug() << "SourceEditor::keyReleaseEvent" << keyboard_event->key();

  switch (keyboard_event->key()) {
    case Qt::Key_Space : {
      switch (ui.reading_mode) {
        case DipylonUI::READINGMODE_KARAOKE: {
          switch (ui.reading_mode_details) {
            //......................................................................
            // [1.1] KARAOKE + PLAYING -> KARAOKE + ON PAUSE
            case DipylonUI::READINGMODEDETAIL_KARAOKE_PLAYING: {
              ui.reading_mode_details = DipylonUI::READINGMODEDETAIL_KARAOKE_ONPAUSE;
              ui.mainWin->audiocontrols_playAct->setIcon(*(ui.icon_audio_pause));
              ui.mainWin->audio_player->pause();
              break;
            }

            //......................................................................
            // [1.2] KARAOKE + ON PAUSE -> KARAOKE + PLAYING
            case DipylonUI::READINGMODEDETAIL_KARAOKE_ONPAUSE: {
              ui.reading_mode_details = DipylonUI::READINGMODEDETAIL_KARAOKE_PLAYING;
              ui.mainWin->audiocontrols_playAct->setIcon(*(ui.icon_audio_play));
              ui.mainWin->audio_player->play();
              break;
            }

            // [1.3] KARAOKE + UNDEFINED : nothing to do.
            default : {
              break;
            }
          }

          break;
        }

        //..........................................................................
        // [2] UNDEFINED reading mode -> KARAOKE + PLAYING
        default: {
            ui.reading_mode = DipylonUI::READINGMODE_KARAOKE;
            ui.reading_mode_details = DipylonUI::READINGMODEDETAIL_KARAOKE_PLAYING;
            ui.mainWin->audiocontrols_playAct->setIcon(*(ui.icon_audio_play));
            ui.mainWin->audio_player->play();
            break;
        }
      }

      break;
    }

    // other keys :
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

  DipyDoc& dipydoc = this->current_dipylonui.current_dipydoc;

  QTextCursor cur = this->textCursor();
  QTextDocument* qtextdocument = this->document();

  /*
     title
  */
  if (dipydoc.title.found == true) {
    // format :
    QTextCharFormat title_qtextcharformat = dipydoc.title.textformat.qtextcharformat();
    QTextBlockFormat title_qtextblockformat = dipydoc.title.blockformat.qtextblockformat();

    cur.insertBlock(title_qtextblockformat, title_qtextcharformat);

    // text :
    cur.insertText(dipydoc.title.text);
    cur.insertText("\n");
  }

  /*
    introduction
  */
  if (dipydoc.introduction.found == true) {
    // format :
    QTextCharFormat introduction_qtextcharformat = dipydoc.introduction.textformat.qtextcharformat();
    QTextBlockFormat introduction_qtextblockformat = dipydoc.introduction.blockformat.qtextblockformat();

    cur.insertBlock(introduction_qtextblockformat, introduction_qtextcharformat);

    // text :
    cur.insertText(dipydoc.introduction.text);
    cur.insertText("\n");
  }

  /*
     lettrine ("initial") + text
  */

  /*
    new block for the lettrine and the text :
  */
  QTextCharFormat text_qtextcharformat = dipydoc.sourceeditor_default_textformat.qtextcharformat();
  QTextBlockFormat text_blockformat = dipydoc.source_text.blockformat.qtextblockformat();

  // inserting the block :
  cur.insertBlock(text_blockformat, text_qtextcharformat);

  // adding the lettrine :
  if (dipydoc.lettrine.found == true) {
    int aspectratio = dipydoc.lettrine.aspectratio;

    qtextdocument->addResource(QTextDocument::ImageResource,
                               QUrl("lettrine"),
                               dipydoc.lettrine.image);

    QTextImageFormat qtextimageformat = QTextImageFormat();
    /*
       the image's size is reduced according to the "aspectratio" variable.

       It is noteworthy that the height is automatically resized so that the
       image' proportions are intact after the resizing.
    */
    qtextimageformat.setWidth(this->width() / aspectratio);

    qtextimageformat.setName("lettrine");

    cur.insertImage(qtextimageformat,
                    dipydoc.lettrine.position_in_text_frame.position());
  }

  /*
    text

     about the followig initialization of "number_of_chars_before_source_text" :
     see DipyDoc::init_from_xml() to see why this attribute has not been
     initialized before.
  */
  dipydoc.source_text.number_of_chars_before_source_text = cur.position();

  cur.setCharFormat(text_qtextcharformat);
  cur.insertText(source_text.text);
}

/*______________________________________________________________________________

        SourceEditor::modify_the_text_format

        This function modify the appearence of the text BUT DOES NOT UPDATE
        the .modified_chars_hash attribute.
_____________________________________________________________________________*/
void SourceEditor::modify_the_text_format(PosInTextRanges& positions) {
  DipyDoc& dipydoc = this->current_dipylonui.current_dipydoc;

  if (this->current_dipylonui.reading_mode == DipylonUI::READINGMODE_KARAOKE) {
    int shift = dipydoc.source_text.number_of_chars_before_source_text;

    QTextCursor cur = this->textCursor();

    // first we set the ancient modified text's appearance to "default" :
    QList<QTextEdit::ExtraSelection> selections;

    for (auto &x0x1 : this->modified_chars) {
      cur.movePosition(QTextCursor::Start,
                       QTextCursor::MoveAnchor);
      cur.movePosition(QTextCursor::NextCharacter,
                       QTextCursor::MoveAnchor, static_cast<int>(x0x1.first) + shift);
      cur.movePosition(QTextCursor::NextCharacter,
                       QTextCursor::KeepAnchor, static_cast<int>(x0x1.second));
      QTextEdit::ExtraSelection sel = { cur,
                                        dipydoc.sourceeditor_default_textformat.qtextcharformat() };
      selections.append(sel);
    }
    this->setExtraSelections(selections);

    selections.clear();

    // ... and then we modify the new text's appearance :
    for (auto &x0x1 : positions) {
      qDebug() << "SourceEditor::modify_the_text_format=" << \
               static_cast<int>(x0x1.first) + shift << \
               "-" << \
               static_cast<int>(x0x1.second);

      cur.movePosition(QTextCursor::Start,
                       QTextCursor::MoveAnchor);
      cur.movePosition(QTextCursor::NextCharacter,
                       QTextCursor::MoveAnchor,
                       static_cast<int>(x0x1.first) + shift);
      cur.movePosition(QTextCursor::NextCharacter,
                       QTextCursor::KeepAnchor,
                       static_cast<int>(x0x1.second - x0x1.first));
      QTextEdit::ExtraSelection sel = { cur,
                            dipydoc.sourceeditor_karaoke_textformat.qtextcharformat() };
      selections.append(sel);
    }
    this->setExtraSelections(selections);

    this->modified_chars = positions;

    cur.clearSelection();
  }
}

/*______________________________________________________________________________

        SourceEditor::mousePressEvent
______________________________________________________________________________*/
void SourceEditor::mousePressEvent(QMouseEvent* mouse_event) {
    QTextCursor cur = this->textCursor();

    qDebug() << "SourceEditor::mousePressEvent" << "pos=" << cur.position();

    //    //this->cursor.select(QTextCursor::WordUnderCursor);
    //    PosInText x0 =  static_cast<PosInText>(cur.position());
    //    qDebug() << "x0=" << x0;
    /*
  switch (this->current_dipylonui.reading_mode) {

    case DipylonUI::READINGMODE_KARAOKE: {

      cur.position()

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        (1) récupérer la position <p> dans le texte => cur.position()
        (2) récupérer le segment audio <segA> correspondant à <p>.
        (3) récupérer le segment dans le texte <segT> correspondant audit segment audio.
        (4) modifier le format du texte de manière à ce que segA apparaisse en surbrillance.
        (5) indiquer que l'on reprend la lecture en pause

      this->current_dipylonui.reading_mode_details = DipylonUI::READINGMODEDETAIL_KARAOKE_PLAYING;
      this->current_dipylonui.mainWin->audiocontrols_playAct->setIcon(*(this->current_dipylonui.icon_audio_play));
      this->current_dipylonui.mainWin->audio_player->play();
      break;
    }

    // other reading mode
    default: {
      break;
    }
  }
    */

  QTextEdit::mousePressEvent(mouse_event);
}

/*______________________________________________________________________________

        SourceEditor::mouseReleaseEvent
_____________________________________________________________________________*/
void SourceEditor::mouseReleaseEvent(QMouseEvent* mouse_event) {
    QTextCursor cur = this->textCursor();

    qDebug() << "SourceEditor::mouseReleaseEvent" << "pos=" << cur.position();

    if (cur.hasSelection()) {
      QString selected_txt = cur.selectedText();
      PosInText x0 = static_cast<PosInText>(cur.selectionStart());
      PosInText x1 = static_cast<PosInText>(cur.selectionEnd());
      qDebug() << "SourceEditor::mouseReleaseEvent; selection=" << x0 << "-" << x1;
     }

    QTextEdit::mouseReleaseEvent(mouse_event);
}

/*______________________________________________________________________________

  SourceEditor::paintEvent()

  doc : http://qt-project.org/doc/qt-4.8/qpainterpath.html#cubicTo

  sur QPen : http://qt-project.org/doc/qt-4.8/qpen.html
______________________________________________________________________________*/
void SourceEditor::paintEvent(QPaintEvent* ev) {
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

        SourceEditor::reset_all_text_format_to_default

        This function resets the appearance of all the text.
_____________________________________________________________________________*/
void SourceEditor::reset_all_text_format_to_default(void) {
  DipyDoc& dipydoc = this->current_dipylonui.current_dipydoc;
  QTextCursor cur = this->textCursor();

  QList<QTextEdit::ExtraSelection> selections;
  this->setExtraSelections(selections);

  cur.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
  cur.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
  QTextEdit::ExtraSelection sel = { cur,
                                    dipydoc.sourceeditor_default_textformat.qtextcharformat() };
  selections.append(sel);

  cur.clearSelection();
}

/*______________________________________________________________________________

  SourceEditor::set_the_appearance
______________________________________________________________________________*/
void SourceEditor::set_the_appearance(void) {
  this->setStyleSheet(current_dipylonui.current_dipydoc.sourceeditor_stylesheet);
}

/*______________________________________________________________________________

  SourceEditor::update_aspect_from_dipydoc_aspect_informations
______________________________________________________________________________*/
void SourceEditor::update_aspect_from_dipydoc_aspect_informations(void) {
  this->set_the_appearance();
}
