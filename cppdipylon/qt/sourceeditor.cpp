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

  this->set_the_text_formats();

  this->set_the_appearance();
}

/*______________________________________________________________________________

  SourceEditor::set_the_appearance
______________________________________________________________________________*/
void SourceEditor::set_the_appearance(void) {

  // everything but the text :
  this->setStyleSheet(fixedparameters::sourceeditor_default_stylesheet);

  // the text (default format) :
  this->setCurrentCharFormat(this->format_text_default);
}

/*______________________________________________________________________________

  SourceEditor::set_the_text_formats()

  Initialize this->format_text_*
______________________________________________________________________________*/
void SourceEditor::set_the_text_formats(void) {

  // default style format :
  auto default_brush = QBrush(Qt::white);
  this->format_text_default.setForeground(default_brush);

  // karaoke style format :
  auto karaoke_brush = QBrush(Qt::red);
  this->format_text_karaoke.setFontWeight(QFont::Bold);
  this->format_text_karaoke.setForeground(karaoke_brush);
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
void SourceEditor::keyReleaseEvent(QKeyEvent * keyboard_event)
{
  qDebug() << "SourceEditor::keyReleaseEvent" << keyboard_event->key();

  switch( keyboard_event->key() ) {

    case Qt::Key_Space : {

      switch( this->current_dipylonui.reading_mode ) {

        case DipylonUI::READINGMODE_KARAOKE: {

          switch( this->current_dipylonui.reading_mode_details ) {

            //......................................................................
            // [1.1] KARAOKE + PLAYING -> KARAOKE + ON PAUSE
            case DipylonUI::READINGMODEDETAIL_KARAOKE_PLAYING: {
              this->current_dipylonui.reading_mode_details = DipylonUI::READINGMODEDETAIL_KARAOKE_ONPAUSE;
              this->current_dipylonui.mainWin->audiocontrols_playAct->setIcon( *(this->current_dipylonui.icon_audio_pause) );
              this->current_dipylonui.mainWin->audio_player->pause();
              break;
            }

            //......................................................................
            // [1.2] KARAOKE + ON PAUSE -> KARAOKE + PLAYING
            case DipylonUI::READINGMODEDETAIL_KARAOKE_ONPAUSE: {
              this->current_dipylonui.reading_mode_details = DipylonUI::READINGMODEDETAIL_KARAOKE_PLAYING;
              this->current_dipylonui.mainWin->audiocontrols_playAct->setIcon( *(this->current_dipylonui.icon_audio_play) );
              this->current_dipylonui.mainWin->audio_player->play();
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
        //[2] UNDEFINED reading mode -> KARAOKE + PLAYING
        default: {
            this->current_dipylonui.reading_mode = DipylonUI::READINGMODE_KARAOKE;
            this->current_dipylonui.reading_mode_details = DipylonUI::READINGMODEDETAIL_KARAOKE_PLAYING;
            this->current_dipylonui.mainWin->audiocontrols_playAct->setIcon( *(this->current_dipylonui.icon_audio_play) );
            this->current_dipylonui.mainWin->audio_player->play();
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

        SourceEditor::mousePressEvent
______________________________________________________________________________*/
void SourceEditor::mousePressEvent(QMouseEvent* mouse_event) {

    QTextCursor cur = this->textCursor();

    qDebug() << "SourceEditor::mousePressEvent" << "pos=" << cur.position();

    //    //this->cursor.select(QTextCursor::WordUnderCursor);
    //    PosInText x0 =  static_cast<PosInText>(cur.position());
    //    qDebug() << "x0=" << x0;
    /*
  switch( this->current_dipylonui.reading_mode ) {

    case DipylonUI::READINGMODE_KARAOKE: {

      cur.position()

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        (1) récupérer la position <p> dans le texte => cur.position()
        (2) récupérer le segment audio <segA> correspondant à <p>.
        (3) récupérer le segment dans le texte <segT> correspondant audit segment audio.
        (4) modifier le format du texte de manière à ce que segA apparaisse en surbrillance.
        (5) indiquer que l'on reprend la lecture en pause

      this->current_dipylonui.reading_mode_details = DipylonUI::READINGMODEDETAIL_KARAOKE_PLAYING;
      this->current_dipylonui.mainWin->audiocontrols_playAct->setIcon( *(this->current_dipylonui.icon_audio_play) );
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
void SourceEditor::mouseReleaseEvent(QMouseEvent* mouse_event)
{
    QTextCursor cur = this->textCursor();

    qDebug() << "SourceEditor::mouseReleaseEvent" << "pos=" << cur.position();

    if ( cur.hasSelection() ) {
      QString selected_txt = cur.selectedText();
      PosInText x0 = static_cast<PosInText>( cur.selectionStart() );
      PosInText x1 = static_cast<PosInText>( cur.selectionEnd() );
      qDebug() << "SourceEditor::mouseReleaseEvent; selection=" << x0 << "-" << x1;
     }

    QTextEdit::mouseReleaseEvent(mouse_event);
}

/*______________________________________________________________________________

        SourceEditor::modify_the_text_format

        This function modify the appearence of the text BUT DOES NOT UPDATE
        the .modified_chars_hash attribute.
_____________________________________________________________________________*/
void SourceEditor::modify_the_text_format(PosInTextRanges& positions) {

  if( this->current_dipylonui.reading_mode == DipylonUI::READINGMODE_KARAOKE) {

   QTextCursor cur = this->textCursor();

   // first we set the ancient modified text's appearance to "default" :
   QList<QTextEdit::ExtraSelection> selections;

    for(auto &x0x1 : this->modified_chars ) {
      cur.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
      cur.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor, static_cast<int>(x0x1.first));
      cur.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, static_cast<int>(x0x1.second));
      QTextEdit::ExtraSelection sel = { cur, this->format_text_default };
      selections.append(sel);
    }
    this->setExtraSelections(selections);

    selections.clear();

   // ... and then we modify the new text's appearance :
    for(auto &x0x1 : positions ) {
      qDebug() << "SourceEditor::modify_the_text_format=" << static_cast<int>(x0x1.first) << "-" << static_cast<int>(x0x1.second);

      cur.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
      cur.movePosition(QTextCursor::NextCharacter,
                       QTextCursor::MoveAnchor,
                       static_cast<int>(x0x1.first));
      cur.movePosition(QTextCursor::NextCharacter,
                       QTextCursor::KeepAnchor,
                       static_cast<int>(x0x1.second - x0x1.first));
      QTextEdit::ExtraSelection sel = { cur, this->format_text_karaoke };
      selections.append(sel);
    }
    this->setExtraSelections(selections);

    this->modified_chars = positions;

    cur.clearSelection();
 }

}

/*______________________________________________________________________________

        SourceEditor::reset_all_text_format_to_default

        This function resets the appearance of all the text.
_____________________________________________________________________________*/
void SourceEditor::reset_all_text_format_to_default(void) {

  QTextCursor cur = this->textCursor();

  QList<QTextEdit::ExtraSelection> selections;
  this->setExtraSelections(selections);

  cur.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
  cur.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
  QTextEdit::ExtraSelection sel = { cur, this->format_text_default };
  selections.append(sel);

  cur.clearSelection();
}
