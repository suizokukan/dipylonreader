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

    ❏DipylonReader❏ : qt/commentaryeditor.cpp

    See commentaryeditor.h for the documentation.

*******************************************************************************/

#include "qt/commentaryeditor.h"
#include "debugmsg/debugmsg.h"

/*______________________________________________________________________________

  CommentaryEditor constructor

______________________________________________________________________________*/
CommentaryEditor::CommentaryEditor(DipylonUI& dipylonui) : current_dipylonui(dipylonui) {
  this->setReadOnly(true);

  this->update_aspect_from_dipydoc_aspect_informations();
}

/*______________________________________________________________________________

  CommentaryEditor::set_the_appearance
______________________________________________________________________________*/
void CommentaryEditor::set_the_appearance(void) {
  this->setStyleSheet(current_dipylonui.current_dipydoc.commentaryeditor_stylesheet);
}

/*______________________________________________________________________________

  CommentaryEditor::set_the_text_formats

  Initialize this->format_text_*
______________________________________________________________________________*/
void CommentaryEditor::set_the_text_formats(void) {
  this->format_text = current_dipylonui.current_dipydoc.commentaryeditor_textformat.qtextcharformat();
}

/*______________________________________________________________________________

  CommentaryEditor::update_content__translation_expected

______________________________________________________________________________*/
void CommentaryEditor::update_content__translation_expected(const PosInTextRanges& posintext) {
  PosInText x0 = posintext.min();
  PosInText x1 = posintext.max();

  QString matching_translations = this->current_dipylonui.get_translations_for(x0, x1);

  this->clear();
  QTextCursor cur = this->textCursor();
  cur.setCharFormat(this->format_text);
  cur.insertText(matching_translations);
}

/*______________________________________________________________________________

        CommentaryEditor::keyReleaseEvent

        See http://qt-project.org/doc/qt-5/qt.html#Key-enum for the list of
        constants like "Qt::Key_Space".

  known cases :

  o [1.1] RLMODE + PLAYING -> RLMODE + ON PAUSE
  o [1.2] RLMODE + ON PAUSE -> RLMODE + PLAYING
  o [1.3] RLMODE + UNDEFINED : nothing to do.
  o [2] UNDEFINED reading mode -> RLMODE + PLAYING
______________________________________________________________________________*/
void CommentaryEditor::keyReleaseEvent(QKeyEvent * keyboard_event) {
  DebugMsg() << "CommentaryEditor::keyReleaseEvent" << keyboard_event->key();

  switch (keyboard_event->key()) {
    case Qt::Key_Space : {
      switch (this->current_dipylonui.reading_mode) {
        case DipylonUI::READINGMODE_RLMODE: {
          switch (this->current_dipylonui.reading_mode_details) {
            //......................................................................
            // [1.1] RLMODE + PLAYING -> RLMODE + ON PAUSE
            case DipylonUI::READINGMODEDETAIL_RLMODE_PLAYING: {
              this->current_dipylonui.reading_mode_details = DipylonUI::READINGMODEDETAIL_RLMODE_ONPAUSE;

              QIcon icon = *(this->current_dipylonui.icon_audio_pause);
              this->current_dipylonui.mainWin->audiocontrols_playAct->setIcon(icon);

              this->current_dipylonui.mainWin->audio_player->pause();
              break;
            }

            //......................................................................
            // [1.2] RLMODE + ON PAUSE -> RLMODE + PLAYING
            case DipylonUI::READINGMODEDETAIL_RLMODE_ONPAUSE: {
              this->current_dipylonui.reading_mode_details = DipylonUI::READINGMODEDETAIL_RLMODE_PLAYING;

              QIcon icon = *(this->current_dipylonui.icon_audio_play);
              this->current_dipylonui.mainWin->audiocontrols_playAct->setIcon(icon);

              this->current_dipylonui.mainWin->audio_player->play();
              break;
            }

            // [1.3] RLMODE + UNDEFINED : nothing to do.
            default : {
              break;
            }
          }

          break;
        }

        //..........................................................................
        // [2] UNDEFINED reading mode -> RLMODE + PLAYING
        default: {
            this->current_dipylonui.reading_mode = DipylonUI::READINGMODE_RLMODE;
            this->current_dipylonui.reading_mode_details = DipylonUI::READINGMODEDETAIL_RLMODE_PLAYING;
            this->current_dipylonui.mainWin->audiocontrols_playAct->setIcon(*(this->current_dipylonui.icon_audio_play));
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

  CommentaryEditor::update_aspect_from_dipydoc_aspect_informations
______________________________________________________________________________*/
void CommentaryEditor::update_aspect_from_dipydoc_aspect_informations(void) {
  this->set_the_text_formats();
  this->set_the_appearance();
}
