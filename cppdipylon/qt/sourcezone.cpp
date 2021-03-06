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

    ❏DipylonReader❏ : qt/sourcezone.cpp

    See sourcezone.h for the documentation.

*******************************************************************************/

#include "qt/sourcezone.h"

/*______________________________________________________________________________

  SourceZone::constructor
______________________________________________________________________________*/
SourceZone::SourceZone(const QString & splitter_name,
                       DipyDoc * _dipydoc,
                       bool & _blocked_commentaries,
                       bool & _visible_toolbars,
                       ReadingMode        & _readingmode,
                       ReadingModeDetails & _readingmodedetails,
                       QWidget *_parent) : QFrame(_parent),
                                           dipydoc(_dipydoc),
                                           blocked_commentaries(_blocked_commentaries),
                                           visible_toolbars(_visible_toolbars),
                                           readingmode(_readingmode),
                                           readingmode_details(_readingmodedetails) {
  // DEBUG1 DebugMsg() << "SourceZone::SourceZone : entry point";

  QString object_name(splitter_name + "::source_zone");
  this->setObjectName(object_name);

  /*
    (0) actions

        (0.1) audio-control objects
        (0.2) r-l-a-mode objects
        (0.3) level objects $$$ unused objects ! $$$
        (0.4) textversion-buttons
   */

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
  // (0.1) audio-control objects
  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  // audiocontrols_playAct
  this->audiocontrols_playAct = new QAction( QIcon(":resources/images/icons/audio_play.png"),
                                             tr("play"),
                                             this);
  this->audiocontrols_playAct->setStatusTip(tr("play..."));
  // connection #C028 (confer documentation)
  QObject::connect(this->audiocontrols_playAct, &QAction::triggered,
                   this,                        &SourceZone::audiocontrols_play);

  // audiocontrols_stopAct
  this->audiocontrols_stopAct = new QAction( QIcon(":resources/images/icons/audio_stop.png"),
                                             tr("stop"),
                                             this);
  this->audiocontrols_stopAct->setStatusTip(tr("stop..."));
  // connection #C029 (confer documentation)
  QObject::connect(this->audiocontrols_stopAct, &QAction::triggered,
                   this,                        &SourceZone::audiocontrols_stop);

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
  // (0.2) r-l-a-mode objects
  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  // readingmode_aAct
  this->readingmode_aAct = new QAction( QIcon(":resources/images/icons/readingmode_amode_on.png"),
                                        tr("switch to analyse mode"),
                                        this);
  this->readingmode_aAct->setStatusTip(tr("switched to analyse mode"));
  // connection #C030 (confer documentation)
  QObject::connect(this->readingmode_aAct, &QAction::triggered,
                   this,                   &SourceZone::readingmode_aAct__buttonpressed);

  // readingmode_lAct
  this->readingmode_lAct = new QAction( QIcon(":resources/images/icons/readingmode_lmode_on.png"),
                                        tr("switch to read-and-listen mode"),
                                        this);
  this->readingmode_lAct->setStatusTip(tr("switched to read-and-listen mode"));
  // connection #C031 (confer documentation)
  QObject::connect(this->readingmode_lAct, &QAction::triggered,
                   this,                   &SourceZone::readingmode_lAct__buttonpressed);

  // readingmode_rAct
  this->readingmode_rAct = new QAction( QIcon(":resources/images/icons/readingmode_rmode_on.png"),
                                        tr("switch to read mode"),
                                        this);
  this->readingmode_rAct->setStatusTip(tr("switched to read mode"));
  // connection #C032 (confer documentation)
  QObject::connect(this->readingmode_rAct, &QAction::triggered,
                   this,                   &SourceZone::readingmode_rAct__buttonpressed);

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
  // (0.3) level objects $$$ unused objects ! $$$
  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  // levelupAct
  this->levelupAct = new QAction( QIcon(":resources/images/icons/up.png"),
                                  tr("reading mode : level up"),
                                  this);
  // connection #C038 (confer documentation)
  QObject::connect(this->levelupAct, &QAction::triggered,
                   this,             &SourceZone::levelupAct__buttonpressed);

  // leveldownAct
  this->leveldownAct = new QAction( QIcon(":resources/images/icons/down.png"),
                                    tr("reading mode : level down"),
                                    this);
  // connection #C039 (confer documentation)
  QObject::connect(this->leveldownAct, &QAction::triggered,
                   this,               &SourceZone::leveldownAct__buttonpressed);

  // levelAct
  this->levelAct = new QAction( QIcon(":resources/images/icons/level.png"),
                                tr("reading mode : select level"),
                                this);

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
  // (0.4) textversion-buttons
  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  // textversionupAct
  this->textversionupAct = new QAction( QIcon(":resources/images/icons/textversionup.png"),
                                      tr("text level up"),
                                      this);
  // connection #C042 (confer documentation)
  QObject::connect(this->textversionupAct, &QAction::triggered,
                   this,                 &SourceZone::textversionupAct__buttonpressed);

  // textversioninfoAct
  this->textversioninfoAct = new QAction( QIcon(":resources/images/icons/textversion0.png"),
                                        _dipydoc->textversion_description,
                                        this);
  // connection #C044 (confer documentation)
  QObject::connect(this->textversioninfoAct, &QAction::triggered,
                   this,                   &SourceZone::textversioninfoAct__buttonpressed);

  // textversiondownAct
  this->textversiondownAct = new QAction( QIcon(":resources/images/icons/textversiondown.png"),
                                        tr("text level down"),
                                        this);
  // connection #C043 (confer documentation)
  QObject::connect(this->textversiondownAct, &QAction::triggered,
                   this,                   &SourceZone::textversiondownAct__buttonpressed);

  // only one textversion ? no textversion icons :
  if (_dipydoc->number_of_textversions == 1) {
      this->textversionupAct->setVisible(false);
      this->textversioninfoAct->setVisible(false);
      this->textversiondownAct->setVisible(false);
  }

  /*
    (1) audio player
  */
  this->load_audiorecord();

  /*
    (2) setting the object : UI
  */
  // DEBUG1 DebugMsg() << "[SourceZone::] setStyleSheet = "
  // DEBUG1            << QString("#%1 {border: 0px; padding: 0px}").arg(object_name);
  this->setStyleSheet(QString("#%1 {border: 0px; padding: 0px}").arg(object_name));

  this->editor = new SourceEditor(splitter_name,
                                  this->readingmode,
                                  this->readingmode_details,
                                  this->dipydoc,
                                  this->audio_player,
                                  this->audiocontrols_playAct,
                                  this->audiocontrols_stopAct,
                                  this->blocked_commentaries,
                                  this->amode_level,
                                  this);
  this->toolbar = new SourceToolBar(splitter_name,
                                    this);

  this->layout = new QHBoxLayout(this);
  this->layout->addWidget(this->editor);
  this->layout->addWidget(this->toolbar);

  this->setLayout(this->layout);

  /*
    (3) actions
  */
  this->textminusAct = new QAction(QIcon(":resources/images/icons/textminus.png"),
                                   tr("reduce the font size"), this);
  this->textplusAct  = new QAction(QIcon(":resources/images/icons/textplus.png"),
                                   tr("enlarge the font size"), this);

  if (this->dipydoc->translation.found == true) {
    this->toolbar->addAction(this->readingmode_rAct);
    this->toolbar->addSeparator();
  }

  if (this->dipydoc->audiorecord.found == true) {
    this->toolbar->addAction(this->readingmode_lAct);
    this->toolbar->addAction(this->audiocontrols_playAct);
    this->toolbar->addAction(this->audiocontrols_stopAct);
    this->toolbar->addSeparator();
  }

  if (this->dipydoc->notes.found == true) {
    this->toolbar->addAction(this->readingmode_aAct);
    this->toolbar->addAction(this->levelupAct);
    this->toolbar->addAction(this->levelAct);
    this->toolbar->addAction(this->leveldownAct);
    this->toolbar->addSeparator();
  }

  this->toolbar->addAction(this->textplusAct);
  this->toolbar->addAction(this->textminusAct);

  this->toolbar->addSeparator();
  this->toolbar->addAction(this->textversionupAct);
  this->toolbar->addAction(this->textversioninfoAct);
  this->toolbar->addAction(this->textversiondownAct);

  // connection #C033 (confer documentation)
  QObject::connect(this->textminusAct, &QAction::triggered,
                   this->editor,       &SourceEditor::zoom_out);

  // connection #C034 (confer documentation)
  QObject::connect(this->textplusAct,  &QAction::triggered,
                   this->editor,       &SourceEditor::zoom_in);

  // connection #C035 (confer documentation)
  QObject::connect(this->audio_player, &QMediaPlayer::positionChanged,
                   this,               &SourceZone::audio_position_changed);

  /*
    (4) default reading mode
  */
  this->readingmode         = READINGMODE::READINGMODE_RMODE;
  this->readingmode_details = READINGMODEDETAILS::READINGMODEDETAIL_RMODE;
  // DEBUG1 DebugMsg() << "now in RMODE mode";

  /*
    (5) zoom values for this document :
  */
  QSettings settings;
  QString setting_name;

  setting_name = QString("text/%1/sourceeditor/zoomvalue").arg(this->dipydoc->qsettings_name);
  if (settings.contains(setting_name) == true) {
    this->editor->set_zoom_value(settings.value(setting_name).toInt());
  } else {
    this->editor->set_zoom_value(fixedparameters::default__zoom_value);
  }

  setting_name = QString("text/%1/commentaryeditor/zoomvalue").arg(this->dipydoc->qsettings_name);
  if (settings.contains(setting_name) == true) {
    this->editor->set_zoom_value(settings.value(setting_name).toInt());
  } else {
    // SIGNAL #S006 (confer documentation)
    emit this->signal__set_zoom_value_in_commentary_editor(fixedparameters::default__zoom_value);
  }

  /*
    (6) updating document aspect :
  */
  // update source editor aspect :
  this->editor->update_aspect_from_dipydoc_aspect_informations();

  // update commentary editor aspect :
  // SIGNAL #S007 (confer documentation)
  emit this->signal__in_commentary_editor_update_from_dipydoc_info();

  /*
    (7) updating the icons
  */
  // SIGNAL #S008 (confer documentation)
  emit this->signal__update_icons();

  // DEBUG1 DebugMsg() << "SourceZone::SourceZone : exit point";
}

/*______________________________________________________________________________

  SourceZone::audiocontrols_play()

  Function connected to this->audiocontrols_playAct::triggered()

  known cases :

  o [1] lmode
        o [1.1] LMODE + PLAYING -> LMODE + ON PAUSE
        o [1.2] LMODE + ON PAUSE -> LMODE + PLAYING
        o [1.3] LMODE + STOP -> LMODE + PLAYING
        o [1.4] LMODE + UNDEFINED : nothing to do.
  o [2] other modes
________________________________________________________________________________*/
void SourceZone::audiocontrols_play(void) {
  switch (this->readingmode) {
    /*
      [1] lmode
    */
    case READINGMODE_LMODE: {
      switch (this->readingmode_details) {
        // [1.1] LMODE + PLAYING -> LMODE + ON PAUSE
        case READINGMODEDETAIL_LMODE_PLAYING: {
          this->readingmode_details = READINGMODEDETAIL_LMODE_ONPAUSE;
          this->audiocontrols_playAct->setIcon(QIcon(":resources/images/icons/audio_pause.png"));
          this->audio_player->pause();
          break;
        }

        // [1.2] LMODE + ON PAUSE -> LMODE + PLAYING
        case READINGMODEDETAIL_LMODE_ONPAUSE: {
          this->readingmode_details = READINGMODEDETAIL_LMODE_PLAYING;
          this->audiocontrols_playAct->setIcon(QIcon(":resources/images/icons/audio_play.png"));
          this->audio_player->play();
          break;
        }

        // [1.3] LMODE + STOP -> LMODE + PLAYING
        case READINGMODEDETAIL_LMODE_STOP: {
          this->readingmode_details = READINGMODEDETAIL_LMODE_PLAYING;
          this->audiocontrols_playAct->setIcon(QIcon(":resources/images/icons/audio_play.png"));
          this->audio_player->play();
          break;
        }

        // [1.4] LMODE + UNDEFINED
        default : {
          break;
        }
      }

      break;
    }

    /*
      [2] other modes
    */
    default: {
        break;
    }
  }
}

/*______________________________________________________________________________

  SourceZone::audiocontrols_stop()

  Function connected to this->audiocontrols_stopAct::triggered()

  o stop the sound
  o set the mode's detail to READINGMODEDETAIL_LMODE_STOP
  o set the source editor's text format to "default".

________________________________________________________________________________*/
void SourceZone::audiocontrols_stop(void) {
  // DEBUG1 DebugMsg() << "SourceZone::audiocontrols_stop";

  // LMODE + ON PAUSE ? we set the icon from "pause" to "play".
  if (this->readingmode == READINGMODE_LMODE &&
      this->readingmode_details == READINGMODEDETAIL_LMODE_ONPAUSE) {
    this->audiocontrols_playAct->setIcon(QIcon(":resources/images/icons/audio_play.png"));
  }

  this->readingmode_details = READINGMODEDETAIL_LMODE_STOP;

  audio_player->stop();

  this->editor->reset_all_text_format_to_default();
}

/*______________________________________________________________________________

  SourceZone::audio_position_changed

________________________________________________________________________________*/
void SourceZone::audio_position_changed(qint64 arg_pos) {
  /*
     LMODE + PLAYING :
  */
  if (this->readingmode == READINGMODE_LMODE &&
      this->readingmode_details == READINGMODEDETAIL_LMODE_PLAYING) {
      // where are the characters linked to "arg_pos" ?
      PosInTextRanges text_ranges = this->dipydoc->audio2text_contains(arg_pos);

      if (text_ranges.is_empty() == false) {
        std::size_t text_ranges_hash = text_ranges.get_hash();

        if (text_ranges_hash != this->editor->modified_chars_hash) {
          // the function modifies the appearence of such characters :
          this->editor->modify_the_text_format__rmode__lmode(text_ranges);

          // hash update :
          this->editor->modified_chars_hash = text_ranges_hash;

          /* updating the vertical scrolling :

             we set the cursor at the end of the current range and we ask Qt
             to scroll down, if necessary, with the help of 
             QTextEdit::ensureCursorVisible() .
          */
          QTextCursor cur = this->editor->textCursor();
          cur.movePosition(QTextCursor::Start,
                           QTextCursor::MoveAnchor);
          cur.movePosition(QTextCursor::NextCharacter,
                           QTextCursor::MoveAnchor,
                           static_cast<int>(text_ranges.max()) + \
                           static_cast<int>(this->editor->number_of_chars_before_source_text) + \
                           fixedparameters::default__sourcezone__jump_ahead);
          this->editor->setTextCursor(cur);
          this->editor->ensureCursorVisible();

          // SIGNAL #S009 (confer documentation)
          emit this->signal__update_translation_in_commentary_zone(text_ranges);
        }
      }
      return;
  }

  /*
    other reading modes : nothing to do.
  */
}

/*______________________________________________________________________________

  SourceZone::leveldownAct__buttonpressed()
______________________________________________________________________________*/
void SourceZone::leveldownAct__buttonpressed(void) {
  // DEBUG1 DebugMsg() << "SourceZone::leveldownAct__buttonpressed" << this->amode_level;
}

/*______________________________________________________________________________

  SourceZone::levelupAct__buttonpressed()
______________________________________________________________________________*/
void SourceZone::levelupAct__buttonpressed(void) {
  // DEBUG1 DebugMsg() << "SourceZone::levelupAct__buttonpressed" << this->amode_level;
}

/*______________________________________________________________________________

  SourceZone::load_audiorecord()

    Load the audio file.
______________________________________________________________________________*/
void SourceZone::load_audiorecord(void) {
  // DEBUG1 DebugMsg() << "loading audio record : entry point";

  delete this->audio_player;
  this->audio_player = new QMediaPlayer(this);

  if (this->dipydoc->audiorecord.found == true) {
    // DEBUG1 DebugMsg() << "... loading audiofile" << this->dipydoc->audiorecord.filename;
    this->audio_player->setMedia(QUrl::fromLocalFile(this->dipydoc->audiorecord.filename));

    this->audio_player->setNotifyInterval(fixedparameters::default__audio_notify_interval);
    this->audio_player->setVolume(fixedparameters::default__audio_player_volume);

    // DEBUG1 DebugMsg() << "... loading audio record : ok";
  }

  // DEBUG1 DebugMsg() << "loading audio record : exit point";
}

/*______________________________________________________________________________

  SourceZone::readingmode_aAct__buttonpressed()

  connected to readingmode_aAct::triggered()
______________________________________________________________________________*/
void SourceZone::readingmode_aAct__buttonpressed(void) {
  // if necessary, the function cleans the "lmode" :
  if (this->readingmode == READINGMODE_LMODE) {
    this->audiocontrols_stop();
  }

  this->readingmode = READINGMODE_AMODE;
  this->readingmode_details = READINGMODEDETAIL_AMODE;
  // DEBUG1 DebugMsg() << "switched to AMODE mode";
  // SIGNAL #S010 (confer documentation)
  emit this->signal__update_icons();
}

/*______________________________________________________________________________

  SourceZone::readingmode_rAct__buttonpressed()

  connected to readingmode_rAct::triggered()
______________________________________________________________________________*/
void SourceZone::readingmode_rAct__buttonpressed(void) {
  // if necessary, the function cleans the "lmode" :
  if (this->readingmode == READINGMODE_LMODE) {
    this->audiocontrols_stop();
  }

  this->readingmode = READINGMODE_RMODE;
  this->readingmode_details = READINGMODEDETAIL_RMODE;
  // DEBUG1 DebugMsg() << "switched to RMODE mode";
  // SIGNAL #S011 (confer documentation)
  emit this->signal__update_icons();

  /* SourceEditor::focused_syntagma_in_amode isn't relevant anymore since
     this attribute has a sense only in A-mode.
  */
  this->editor->focused_syntagma_in_amode = nullptr;
}

/*______________________________________________________________________________

  SourceZone::readingmode_lAct__buttonpressed()

  connected to readingmode_lAct::triggered()
______________________________________________________________________________*/
void SourceZone::readingmode_lAct__buttonpressed(void) {
  this->readingmode = READINGMODE_LMODE;
  this->readingmode_details = READINGMODEDETAIL_LMODE_STOP;
  // DEBUG1 DebugMsg() << "switched to LMODE mode";
  // SIGNAL #S012 (confer documentation)
  emit this->signal__update_icons();

  /* SourceEditor::focused_syntagma_in_amode isn't relevant anymore since
     this attribute has a sense only in A-mode.
  */
  this->editor->focused_syntagma_in_amode = nullptr;
}


/*______________________________________________________________________________

  SourceZone::update_icons()

  Function called by SCSplitter::update_icons().

  Whether the icons will be display is controlled by visible_toolbars and by
  SCSplitter::update_icons .
________________________________________________________________________________*/
void SourceZone::update_icons(void) {
  // DEBUG1 DebugMsg() << "SourceZone::update_icons";

  switch (this->readingmode) {
    case READINGMODE_AMODE: {
      // main icons :
      this->readingmode_aAct->setIcon(QIcon(":resources/images/icons/readingmode_amode_on.png"));
      this->readingmode_rAct->setIcon(QIcon(":resources/images/icons/readingmode_rmode_off.png"));
      this->readingmode_lAct->setIcon(QIcon(":resources/images/icons/readingmode_lmode_off.png"));

      // secondary icons :
      this->audiocontrols_playAct->setVisible(false);
      this->audiocontrols_stopAct->setVisible(false);
      this->levelupAct->setVisible(false);       //$$$ true
      this->levelAct->setVisible(false);         //$$$ true
      this->leveldownAct->setVisible(false);    //$$$ true
      break;
    }

    case READINGMODE_LMODE: {
      // main icons :
      this->readingmode_aAct->setIcon(QIcon(":resources/images/icons/readingmode_amode_off.png"));
      this->readingmode_rAct->setIcon(QIcon(":resources/images/icons/readingmode_rmode_off.png"));
      this->readingmode_lAct->setIcon(QIcon(":resources/images/icons/readingmode_lmode_on.png"));

      // secondary icons :

      // audio control icons :
      if ((this->dipydoc->well_initialized() == false) ||
          (this->dipydoc->audiorecord.found == false)) {
        // special cases : a problem occurs, let's hide the audio icons.
        this->audiocontrols_playAct->setVisible(false);
        this->audiocontrols_stopAct->setVisible(false);
      } else {
        // normal case : let's show the audio icons.
        this->audiocontrols_playAct->setVisible(true);
        this->audiocontrols_stopAct->setVisible(true);
      }

      this->levelupAct->setVisible(false);
      this->levelAct->setVisible(false);
      this->leveldownAct->setVisible(false);
      break;
    }

    case READINGMODE_RMODE: {
      // main icons :
      this->readingmode_aAct->setIcon(QIcon(":resources/images/icons/readingmode_amode_off.png"));
      this->readingmode_rAct->setIcon(QIcon(":resources/images/icons/readingmode_rmode_on.png"));
      this->readingmode_lAct->setIcon(QIcon(":resources/images/icons/readingmode_lmode_off.png"));

      // secondary icons :
      this->audiocontrols_playAct->setVisible(false);
      this->audiocontrols_stopAct->setVisible(false);
      this->levelupAct->setVisible(false);
      this->levelAct->setVisible(false);
      this->leveldownAct->setVisible(false);
      break;
    }

    default : {
      break;
    }
  }
}

/*______________________________________________________________________________

  SourceZone::textversiondownAct__buttonpressed()
______________________________________________________________________________*/
void SourceZone::textversiondownAct__buttonpressed(void) {
  // DEBUG1 DebugMsg() << "SourceZone::textversiondownAct__buttonpressed";

  if (this->dipydoc->current_textversion > 0) {
    // DEBUG1 DebugMsg() << "... number_of_textversions=" << this->dipydoc->number_of_textversions;
    this->dipydoc->current_textversion--;

    #ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
    #endif
    this->dipydoc->load_a_textversion(this->dipydoc->path,
                                    this->dipydoc->current_textversion);
    #ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
    #endif

    // SIGNAL #S014 (confer documentation)
    emit this->signal__update_due_to_a_dipydoc_newly_reloaded();
  }
}

/*______________________________________________________________________________

  SourceZone::textversioninfoAct__buttonpressed()
______________________________________________________________________________*/
void SourceZone::textversioninfoAct__buttonpressed(void) {
}

/*______________________________________________________________________________

  SourceZone::textversionupAct__buttonpressed()
______________________________________________________________________________*/
void SourceZone::textversionupAct__buttonpressed(void) {
  // DEBUG1 DebugMsg() << "SourceZone::textversionupAct__buttonpressed";

  // DEBUG1 DebugMsg() << "SourceZone::textversioninfoAct__buttonpressed";

  if (this->dipydoc->current_textversion < this->dipydoc->number_of_textversions) {
    // DEBUG1 DebugMsg() << "... number_of_textversions=" << this->dipydoc->number_of_textversions;
    this->dipydoc->current_textversion++;

    #ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
    #endif
    this->dipydoc->load_a_textversion(this->dipydoc->path,
                                    this->dipydoc->current_textversion);
    #ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
    #endif

    // SIGNAL #S015 (confer documentation)
    emit this->signal__update_due_to_a_dipydoc_newly_reloaded();
  }
}
