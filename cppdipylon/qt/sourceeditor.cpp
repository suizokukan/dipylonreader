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
SourceEditor::SourceEditor(const QString &       splitter_name,
                           ReadingMode &         _readingmode,
                           ReadingModeDetails &  _readingmode_details,
                           const DipyDoc *       _dipydoc,
                           QMediaPlayer *        _audio_player,
                           QAction *             _audiocontrols_playAct,
                           QAction *             _audiocontrols_stopAct,
                           bool &                _blocked_commentaries,
                           int &                 _amode_level,
                           QWidget* _parent) : TextEditor(_parent),
                                               readingmode(_readingmode),
                                               readingmode_details(_readingmode_details),
                                               dipydoc(_dipydoc),
                                               audio_player(_audio_player),
                                               audiocontrols_playAct(_audiocontrols_playAct),
                                               audiocontrols_stopAct(_audiocontrols_stopAct),
                                               blocked_commentaries(_blocked_commentaries),
                                               amode_level(_amode_level) {
  //DEBUG1 DebugMsg() << "SourceEditor::SourceEditor() : entry point";

  QString object_name(splitter_name + "::source zone::editor");
  this->setObjectName(object_name);

  this->setReadOnly(true);
  this->setMouseTracking(true);
  this->load_text();
  this->update_aspect_from_dipydoc_aspect_informations();

  //$$$this->update_arrows__timer = new QTimer(this);
  // connection #C041 (confer documentation)
  //$$$this->connect(this->update_arrows__timer, &QTimer::timeout,
  //$$$              this,                       &QWidget::update);
  //$$$this->connect(this->update_arrows__timer, SIGNAL(timeout()),
  //$$$              this,                       SLOT(Q::update()));
  //$$$this->update_arrows__timer->start(250);

  //DEBUG1 DebugMsg() << "SourceEditor::SourceEditor() : exit point";
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

  known cases :

  [0] special cases
    [0.1] control + w
  [1] space
    [1.1] LMODE + PLAYING -> LMODE + ON PAUSE
    [1.2] LMODE + ON PAUSE -> LMODE + PLAYING
    [1.3] LMODE + UNDEFINED : nothing to do.
    [1.4] UNDEFINED reading mode -> LMODE + PLAYING
  [2] arrows
  [3] other keys

______________________________________________________________________________*/
void SourceEditor::keyReleaseEvent(QKeyEvent * keyboard_event) {
  //DEBUG1 DebugMsg() << "SourceEditor::keyReleaseEvent" << keyboard_event->key();

  switch (keyboard_event->key()) {
    //......................................................................
    // [1] space
    case Qt::Key_Space : {
      switch (this->readingmode) {
        case READINGMODE::READINGMODE_LMODE: {
          switch (this->readingmode_details) {
            //......................................................................
            // [1.1] LMODE + PLAYING -> LMODE + ON PAUSE
            case READINGMODEDETAILS::READINGMODEDETAIL_LMODE_PLAYING: {
              this->readingmode_details = READINGMODEDETAILS::READINGMODEDETAIL_LMODE_ONPAUSE;
              this->audiocontrols_playAct->setIcon(*(icons.audio_pause));
              this->audio_player->pause();
              break;
            }

            //......................................................................
            // [1.2] LMODE + ON PAUSE -> LMODE + PLAYING
            case READINGMODEDETAILS::READINGMODEDETAIL_LMODE_ONPAUSE: {
              this->readingmode_details = READINGMODEDETAILS::READINGMODEDETAIL_LMODE_PLAYING;
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
            this->readingmode = READINGMODE::READINGMODE_LMODE;
            this->readingmode_details = READINGMODEDETAILS::READINGMODEDETAIL_LMODE_PLAYING;
            this->audiocontrols_playAct->setIcon(*(icons.audio_play));
            this->audio_player->play();

            /* SourceEditor::focused_syntagma_in_amode isn't relevant anymore since
               this attribute has a sense only in A-mode.
            */
            this->focused_syntagma_in_amode = nullptr;
            break;
        }
      }

      break;
    }

    //......................................................................
    // [2] arrows $$$ unfinished $$$
    case Qt::Key_Left :
    case Qt::Key_Right : {
      switch (this->readingmode) {
        case READINGMODE::READINGMODE_LMODE: {
          switch (this->readingmode_details) {
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
void SourceEditor::load_text(void) {
  this->clear();

  QTextCursor cur = this->textCursor();
  QTextDocument* qtextdocument = this->document();

  /*
     title
  */
  if (this->dipydoc->title.found == true) {
    // format :
    QTextCharFormat title_qtextcharformat = this->dipydoc->title.textformat.qtextcharformat();
    QTextBlockFormat title_qtextblockformat = this->dipydoc->title.blockformat.qtextblockformat();

    cur.insertBlock(title_qtextblockformat, title_qtextcharformat);

    // text :
    cur.insertText(this->dipydoc->title.text);
    cur.insertText("\n");
  }

  /*
    introduction
  */
  if (this->dipydoc->introduction.found == true) {
    // format :
    QTextCharFormat introduction_qtextcharformat = this->dipydoc->introduction.textformat.qtextcharformat();
    QTextBlockFormat introduction_qtextblockformat = this->dipydoc->introduction.blockformat.qtextblockformat();

    cur.insertBlock(introduction_qtextblockformat, introduction_qtextcharformat);

    // text :
    cur.insertText(this->dipydoc->introduction.text);
    cur.insertText("\n");
  }

  /*
     lettrine ("initial") + text
  */

  /*
    new block for the lettrine and the text :
  */
  QTextCharFormat text_qtextcharformat = this->dipydoc->sourceeditor_default_textformat.qtextcharformat();
  QTextBlockFormat text_blockformat = this->dipydoc->source_text.blockformat.qtextblockformat();

  // inserting the block :
  cur.insertBlock(text_blockformat, text_qtextcharformat);

  // adding the lettrine :
  if (this->dipydoc->lettrine.found == true) {
    int aspectratio = this->dipydoc->lettrine.aspectratio;

    qtextdocument->addResource(QTextDocument::ImageResource,
                               QUrl("lettrine"),
                               this->dipydoc->lettrine.image);

    QTextImageFormat qtextimageformat = QTextImageFormat();
    /*
       the image's size is reduced according to the "aspectratio" variable.

       It is noteworthy that the height is automatically resized so that the
       image' proportions are intact after the resizing.
    */
    qtextimageformat.setWidth(this->width() / aspectratio);

    qtextimageformat.setName("lettrine");

    cur.insertImage(qtextimageformat,
                    this->dipydoc->lettrine.position_in_text_frame.position());
  }

  /*
    Before the source text, the title and the introduction may be inserted.
    This attribute stores the number of characters appearing before
    the source text.
  */
  this->number_of_chars_before_source_text = cur.position();

  cur.setCharFormat(text_qtextcharformat);
  cur.insertText(this->dipydoc->source_text.text);
}

/*______________________________________________________________________________

        SourceEditor::modify_the_text_format__amode

        This function modify the appearence of the text BUT DOES NOT UPDATE
        the .modified_chars_hash attribute.

        Use this function only for the a-mode.
_____________________________________________________________________________*/
void SourceEditor::modify_the_text_format__amode(Syntagma* syntagma) {
  //DEBUG1 DebugMsg() << "SourceEditor::modify_the_text_format__amode() syntagma=" << syntagma;

  int shift = this->number_of_chars_before_source_text;

  QTextCursor cur = this->textCursor();

  cur.beginEditBlock();

  // first we set the ancient modified text's appearance to "default" :
  QList<QTextEdit::ExtraSelection> selections;

  for (auto &x0x1 : this->modified_chars) {
    cur.setPosition(static_cast<int>(x0x1.first) + shift, QTextCursor::MoveAnchor);
    cur.setPosition(static_cast<int>(x0x1.second) + shift, QTextCursor::KeepAnchor);
    selections.append({ cur,
                        this->dipydoc->sourceeditor_default_textformat.qtextcharformat() });
  }
  this->setExtraSelections(selections);

  // ... and then we modify the new text's appearance :
  selections.clear();

  /*
    The following loop goes through the tree and adds the modifications to "selections".

    The higher the syntagma (=phrase, proposition...) the sooner they are "draw".
    The deeper the syntagma (=word, ...) the later they are "draw".


    E.g. with Syntagma objects replaced by integers :

                                0+
                ---------------------------------
                |               |               |
                0               1               2
                            -------------
                            1           2*


       hierarchy = [0]     means : let's call __amode__syntagma() for the (0)+ element
       hierarchy = [0,1,2] means : let's call __amode__syntagma() for the (0,1,2)* element

  */
  QList<int> hierarchy = {0};
  Syntagma* current_syntagma = syntagma->highest_ancestor;

  while (current_syntagma != nullptr) {
    /*
       let's call the ::this->modify_the_text_format__amode__syntagma() method
      with the element described in "hierarchy" whose address is stored in
      "current_syntagma" .
    */

    // link betwween current_syntagma and focused_syntagma_in_amode ?
    int link = -1; // by default, no link.
    if (this->focused_syntagma_in_amode == current_syntagma) {
      // focused :
      link=0;
    } else {
      if (this->focused_syntagma_in_amode->father == current_syntagma->father) {
        // brother :
        link=1;
      } else {
        if (this->focused_syntagma_in_amode->ancestors.contains(current_syntagma)) {
          // family :
          link=2;
        }
      }
    }

    // the method is not called for every value of "link" :
    if (link != -1) {
      this->modify_the_text_format__amode__syntagma(current_syntagma,
                                                    selections,
                                                    link);
    }

    /*
      let's go through the tree, searching the next syntagma :
    */
    if (current_syntagma->soons.size() == 0) {
      bool keep_on = true;
      while(keep_on==true) {
        current_syntagma = current_syntagma->father;

        if (current_syntagma == nullptr) {
          keep_on=false;
        } else {
          if (hierarchy.last()+1 < current_syntagma->soons.size()) {
            keep_on = false;
            hierarchy[hierarchy.size()-1]++;
            current_syntagma = current_syntagma->soons[hierarchy.last()];
          } else {
            hierarchy.removeLast();
          }
        }
      }
    } else {
      current_syntagma = current_syntagma->soons[0];
      hierarchy.append(0);
    }
  }

  /*
    Let's apply the modifications :
  */
  this->setExtraSelections(selections);

  this->modified_chars = syntagma->posintextranges;

  cur.clearSelection();

  cur.endEditBlock();
}

/*______________________________________________________________________________

        SourceEditor::modify_the_text_format__amode__syntagma

        Function called by SourceEditor::modify_the_text_format__amode

        parameters :

        o 'current_syntagma' is the current syntagma to be modified
          This pointer should never be set to nullptr.

        o 'selections' is the bunch of (text) selections to be filled.

        o 'link' between current_syntagma and this->focused_syntagma_in_amode
           0 : focused
           1 : brother
           2 : family
_____________________________________________________________________________*/
void SourceEditor::modify_the_text_format__amode__syntagma(Syntagma* current_syntagma,
                                                           QList<QTextEdit::ExtraSelection> & selections,
                                                           int link) {
  //DEBUG1 DebugMsg() << "SourceEditor::modify_the_text_format__amode__syntagma() : entry point : #" << current_syntagma->name << " link=" << link << " pos=" << current_syntagma->posintextranges.repr();

  int shift = this->number_of_chars_before_source_text;

  QTextCursor cur = this->textCursor();
  QTextCharFormat qtextcharformat;

  for (auto & x0x1 : current_syntagma->posintextranges) {

    cur.setPosition(static_cast<int>(x0x1.first) + shift, QTextCursor::MoveAnchor);
    // $$$ plus rapide ??? $$$ cur.setPosition(static_cast<int>(x0x1.second) + shift, QTextCursor::KeepAnchor);
    cur.movePosition(QTextCursor::NextCharacter,
                     QTextCursor::KeepAnchor,
                     static_cast<int>(x0x1.second - x0x1.first));

    switch(link) {
      case 0 : {
        /*
          link = "focused"

          'current_syntagma' is 'this->focused_syntagma_in_amode' :
        */
        if (current_syntagma->type.size() != 0) {
          // the type has been defined :
          qtextcharformat = this->dipydoc->notes.syntagmas_types.at(current_syntagma->type).qtextcharformat();
          selections.append( {cur, qtextcharformat} );
          //DEBUG1 DebugMsg() << "###foc0" << static_cast<int>(x0x1.first) + shift << " - " << static_cast<int>(x0x1.second) + shift;
        } else {
          // no type defined :
          qtextcharformat = this->dipydoc->notes.syntagmas_aspects.at(current_syntagma->name+"+foc").qtextcharformat();
          selections.append( {cur, qtextcharformat} );
          //DEBUG1 DebugMsg() << "###foc1" << static_cast<int>(x0x1.first) + shift << " - " << static_cast<int>(x0x1.second) + shift;
        }
        break;
      }

      case 1 : {
        /*
          link = "brothers"

          'this->focused_syntagma_in_amode' and 'current_syntagma' are brothers (=have the same father)
        */
        if (current_syntagma->type.size() != 0) {
          // the type has been defined :
          qtextcharformat = this->dipydoc->notes.syntagmas_types.at(current_syntagma->type).qtextcharformat();
          selections.append( {cur, qtextcharformat} );
          //DEBUG1 DebugMsg() << "###bro0" << static_cast<int>(x0x1.first) + shift << " - " << static_cast<int>(x0x1.second) + shift;
        } else {
          // no type defined :
          qtextcharformat = this->dipydoc->notes.syntagmas_aspects.at(current_syntagma->name+"+bro").qtextcharformat();
          selections.append( {cur, qtextcharformat} );
          //DEBUG1 DebugMsg() << "###bro1" << static_cast<int>(x0x1.first) + shift << " - " << static_cast<int>(x0x1.second) + shift;
        }
        break;
      }

      case 2 : {
        /*
          link = "family"

          One of the ancestors of 'this->focused_syntagma_in_amode' is 'current_syntagma'.
        */
        qtextcharformat = this->dipydoc->notes.syntagmas_aspects.at(current_syntagma->name+"+fam").qtextcharformat();
        selections.append( {cur, qtextcharformat} );
        //DEBUG1 DebugMsg() << "###fam" << static_cast<int>(x0x1.first) + shift << " - " << static_cast<int>(x0x1.second) + shift;
        break;
      }

      default: {
        break;
      }
    }
  }

  //DEBUG1 DebugMsg() << "SourceEditor::modify_the_text_format__amode__syntagma() : exit point : #" << current_syntagma->name << " - " << current_syntagma->type << " this= " << current_syntagma << " father= " << current_syntagma->father;
}

/*______________________________________________________________________________

        SourceEditor::modify_the_text_format__rmode__lmode

        This function modify the appearence of the text BUT DOES NOT UPDATE
        the .modified_chars_hash attribute.

        Use this function only for r-mode and l-mode.
_____________________________________________________________________________*/
void SourceEditor::modify_the_text_format__rmode__lmode(const PosInTextRanges& positions) {
  int shift = this->number_of_chars_before_source_text;

  QTextCursor cur = this->textCursor();

  // first we set the ancient modified text's appearance to "default" :
  QList<QTextEdit::ExtraSelection> selections;

  for (auto &x0x1 : this->modified_chars) {
    cur.setPosition(static_cast<int>(x0x1.first) + shift, QTextCursor::MoveAnchor);
    cur.setPosition(static_cast<int>(x0x1.second) + shift, QTextCursor::KeepAnchor);
    QTextEdit::ExtraSelection sel = { cur,
                                      this->dipydoc->sourceeditor_default_textformat.qtextcharformat() };
    selections.append(sel);
  }
  this->setExtraSelections(selections);

  selections.clear();

  // ... and then we modify the new text's appearance :
  for (auto &x0x1 : positions) {
    cur.setPosition(static_cast<int>(x0x1.first) + shift, QTextCursor::MoveAnchor);
    cur.setPosition(static_cast<int>(x0x1.second) + shift, QTextCursor::KeepAnchor);

    QTextEdit::ExtraSelection sel;
    if (this->readingmode == READINGMODE::READINGMODE_RMODE) {
      sel = { cur,
              this->dipydoc->sourceeditor_rmode_textformat.qtextcharformat() };
    }
    if (this->readingmode == READINGMODE::READINGMODE_LMODE) {
      sel = { cur,
              this->dipydoc->sourceeditor_lmode_textformat.qtextcharformat() };
    }

    selections.append(sel);
  }
  this->setExtraSelections(selections);

  this->modified_chars = positions;

  cur.clearSelection();
}

/*______________________________________________________________________________

        SourceEditor::mouseMoveEvent()
______________________________________________________________________________*/
void SourceEditor::mouseMoveEvent(QMouseEvent* mouse_event) {

  if (this->blocked_commentaries == false) {
    switch (this->readingmode_details) {
      case READINGMODEDETAILS::READINGMODEDETAIL_RMODE : {
        QTextCursor cur = this->cursorForPosition(mouse_event->pos());
        int shift = this->number_of_chars_before_source_text;
        PosInText cursor_position = static_cast<PosInText>(cur.position()) - static_cast<PosInText>(shift);

        // in the translation, where are the characters linked to "cursor_position" ?
        PosInTextRanges pos_in_text = this->dipydoc->translation_contains(cursor_position);

        std::size_t text_ranges_hash = pos_in_text.get_hash();

        // if the user is really on another text's segment ...
        if (text_ranges_hash != this->modified_chars_hash) {
          // ... we refresh the ui :

          // the function modifies the appearence of such characters :
          this->modify_the_text_format__rmode__lmode(pos_in_text);

          // hash update :
          this->modified_chars_hash = text_ranges_hash;

          // SIGNAL #S001 (confer documentation)
          emit this->signal__update_translation_in_commentary_zone(pos_in_text);

          this->update();
        }

        break;
      }

      case READINGMODEDETAILS::READINGMODEDETAIL_AMODE : {
        QTextCursor cur = this->cursorForPosition(mouse_event->pos());
        int shift = this->number_of_chars_before_source_text;
        PosInText cursor_position = static_cast<PosInText>(cur.position()) - static_cast<PosInText>(shift);

        // in the syntagmas, where are the characters linked to "cursor_position" ?
        Syntagma* syntagma = this->dipydoc->notes.contains(cursor_position, this->amode_level);

        if (syntagma != nullptr) {

          this->focused_syntagma_in_amode = syntagma;

          std::size_t text_ranges_hash = syntagma->posintextranges.get_hash();

          // if the user is really on another text's segment ...
          if (text_ranges_hash != this->modified_chars_hash) {
            // ... we refresh the ui :

            // the function modifies the appearence of such characters :
            this->modify_the_text_format__amode(syntagma);
            // hash update :
            this->modified_chars_hash = text_ranges_hash;
            // let's show the note :
            // SIGNAL #S013 (confer documentation)
            emit this->signal__update_note_in_commentary_zone(syntagma->textnote);

            this->update();
          }
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
  //DEBUG1 DebugMsg() << "SourceEditor::mouseReleaseEvent";

  /*............................................................................
    (1) RMODE + selection
  ............................................................................*/
  if (this->readingmode_details == READINGMODEDETAILS::READINGMODEDETAIL_RMODE && cur.hasSelection() == true) {
    //DEBUG1 DebugMsg() << "SourceEditor::mouseReleaseEvent; RMODE + selection";

    int shift = this->number_of_chars_before_source_text;
    PosInText x0 = static_cast<PosInText>(cur.selectionStart() - shift);
    PosInText x1 = static_cast<PosInText>(cur.selectionEnd() - shift);

    // where are the characters in the translations linked to "x0-x1" ?
    PosInTextRanges pos_in_text =  this->dipydoc->translation_contains(x0, x1);
    //DEBUG1 DebugMsg() << x0 << "-" << x1 << "; pos_in_text=" << pos_in_text.repr();

    /*
      we refresh the ui :
    */
    std::size_t text_ranges_hash = pos_in_text.get_hash();

    // the function modifies the appearence of such characters :
    this->modify_the_text_format__rmode__lmode(pos_in_text);

    // hash update :
    this->modified_chars_hash = text_ranges_hash;

    this->blocked_commentaries = false;
    // SIGNAL #S002 (confer documentation)
    emit this->signal__update_translation_in_commentary_zone(pos_in_text);
    this->blocked_commentaries = true;

    // SIGNAL #S003 (confer documentation)
    emit this->signal__source_zone_update_icons();

    this->update();

    return;
  }

  // no selection ? we don't protect anymore the commentary zone :
  if (cur.hasSelection() == false) {
    this->blocked_commentaries = false;
  }

  /*............................................................................
    (2) without selection
  ............................................................................*/
  PosInText cursor_position = this->corrected_cursor_position();

  switch (this->readingmode) {
    case READINGMODE::READINGMODE_LMODE: {
      switch (this->readingmode_details) {
        //......................................................................
        // LMODE + ON PAUSE
        // LMODE + STOP
        case READINGMODEDETAILS::READINGMODEDETAIL_LMODE_ONPAUSE:
        case READINGMODEDETAILS::READINGMODEDETAIL_LMODE_STOP : {
          // where are the characters linked to "cursor_position" ?
          PTRangesAND2PosAudio found_position = this->dipydoc->text2audio_contains(cursor_position);
          PosInTextRanges pos_in_text = found_position.first;

          std::size_t text_ranges_hash = pos_in_text.get_hash();

          // if the user has really click on another text's segment ...
          if (text_ranges_hash != this->modified_chars_hash) {
            // ... we refresh the ui :

            // the function modifies the appearence of such characters :
            this->modify_the_text_format__rmode__lmode(pos_in_text);

            // hash update :
            this->modified_chars_hash = text_ranges_hash;

            // SIGNAL #S004 (confer documentation)
            emit this->signal__update_translation_in_commentary_zone(pos_in_text);

            this->update();
          }
          break;
        }
        //......................................................................
        // LMODE + PLAYING
        case READINGMODEDETAILS::READINGMODEDETAIL_LMODE_PLAYING : {
          // where are the characters linked to "cursor_position" ?
          PTRangesAND2PosAudio found_position = this->dipydoc->text2audio_contains(cursor_position);
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

  SourceEditor::paintEvent

  $$$ à étudier (???)
  $$$ http://www.qtcentre.org/threads/32130-Getting-the-bounding-rect-of-a-character-in-a-QTextDocument
  $$$ http://elonen.iki.fi/code/misc-notes/char-bbox-qtextedit/
______________________________________________________________________________*/
void SourceEditor::paintEvent(QPaintEvent* ev) {

  /*
    Let's draw anything but the arrows :
  */
  QTextEdit::paintEvent(ev);

  int shift = this->number_of_chars_before_source_text;

  /*
       If there's a defined (=not nullptr) focused_syntagma_in_amode, let's draw
     the arrows between this focused syntagma and the other syntagmas.
  */
  if (this->focused_syntagma_in_amode != nullptr) {

    QPainter p(this->viewport());

    for (auto & arrowtarget : this->focused_syntagma_in_amode->arrows) {
      // starting point :
      QTextCursor start_cur = this->textCursor();
      start_cur.setPosition(shift+static_cast<int>(this->focused_syntagma_in_amode->posintextranges.medium()));
      QRect start_rect = this->cursorRect(start_cur);

      // end point :
      QTextCursor end_cur = this->textCursor();
      end_cur.setPosition(shift+static_cast<int>(arrowtarget.final_position.medium()));
      QRect dest_rect = this->cursorRect(end_cur);

      float x0 = start_rect.x();
      float y0 = start_rect.y();
      float x1 = dest_rect.x();
      float y1 = dest_rect.y();

      QPointF startingpoint = QPointF(x0, y0);
      QPointF endpoint = QPointF(x1, y1);

      // arrow body :
      p.setPen( this->dipydoc->notes.arrows_types.at(arrowtarget.type).body_qpen());
      QPainterPath path = QPainterPath(startingpoint);  // starting point
      path.cubicTo(QPointF(x0*1.3, y0*0.9),
                   QPointF(x0*1.1, y0*0.7),
                   endpoint);  // p1, p2, endpoint
      p.drawPath(path);

      // initial/final boxes :
      p.setPen(this->dipydoc->notes.arrows_types.at(arrowtarget.type).start_qpen());
      p.drawRect(x0-3, y0-3, 6, 6);

      p.setPen(this->dipydoc->notes.arrows_types.at(arrowtarget.type).end_qpen());
      p.drawRect(x1-3, y1-3, 6, 6);
    }
  }
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
                                    this->dipydoc->sourceeditor_default_textformat.qtextcharformat() };
  selections.append(sel);

  cur.clearSelection();
}

/*______________________________________________________________________________

  SourceEditor::set_the_appearance()
______________________________________________________________________________*/
void SourceEditor::set_the_appearance(void) {
  //DEBUG1 DebugMsg() << "[SourceEditor::set_the_appearance] this->setStyleSheet = " << this->dipydoc->sourceeditor_stylesheet;
  this->setStyleSheet(this->dipydoc->sourceeditor_stylesheet);
}

/*______________________________________________________________________________

  SourceEditor::update_aspect_from_dipydoc_aspect_informations()
______________________________________________________________________________*/
void SourceEditor::update_aspect_from_dipydoc_aspect_informations(void) {
  this->set_the_appearance();
}
