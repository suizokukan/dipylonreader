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
                       const DipyDoc& _dipydoc,
                       bool & _blocked_commentaries,
                       bool & _visible_toolbars,
                       QWidget *_parent) : QFrame(_parent),
                                           dipydoc(_dipydoc),
                                           blocked_commentaries(_blocked_commentaries),
                                           visible_toolbars(_visible_toolbars),
                                           readingmode(READINGMODE::READINGMODE_UNDEFINED),
                                           readingmode_details(READINGMODEDETAILS::READINGMODEDETAIL_UNDEFINED) {
  DebugMsg() << "SourceZone::SourceZone : entry point";

  QString object_name(splitter_name + "::source_zone");
  this->setObjectName(object_name);

  /*
    (0) actions
   */
  // audiocontrols_playAct
  this->audiocontrols_playAct = new QAction( *(icons.audio_play),
                                             tr("play"),
                                             this);
  this->audiocontrols_playAct->setStatusTip(tr("play..."));
  QObject::connect(this->audiocontrols_playAct, &QAction::triggered,
                   this,                        &SourceZone::audiocontrols_play);

  // audiocontrols_stopAct
  this->audiocontrols_stopAct = new QAction( *(icons.audio_stop),
                                             tr("stop"),
                                             this);
  this->audiocontrols_stopAct->setStatusTip(tr("stop..."));
  QObject::connect(this->audiocontrols_stopAct, &QAction::triggered,
                   this,                        &SourceZone::audiocontrols_stop);

  // readingmode_aAct
  this->readingmode_aAct = new QAction( *(icons.readingmode_amode_on),
                                        tr("change the mode$$$rl"),
                                        this);
  this->readingmode_aAct->setStatusTip(tr("change the mode to 'analyse'"));
  QObject::connect(this->readingmode_aAct, &QAction::triggered,
                   this,                   &SourceZone::readingmode_aAct__buttonpressed);

  // readingmode_lAct
  this->readingmode_lAct = new QAction( *(icons.readingmode_lmode_on),
                                        tr("change the mode$$$rl"),
                                        this);
  this->readingmode_lAct->setStatusTip(tr("change the mode to 'read & listen'"));
  QObject::connect(this->readingmode_lAct, &QAction::triggered,
                   this,                   &SourceZone::readingmode_lAct__buttonpressed);

  // readingmode_rAct
  this->readingmode_rAct = new QAction( *(icons.readingmode_rmode_on),
                                        tr("change the mode$$$r"),
                                        this);
  this->readingmode_rAct->setStatusTip(tr("change the mode to 'read'"));
  QObject::connect(this->readingmode_rAct, &QAction::triggered,
                   this,                   &SourceZone::readingmode_rAct__buttonpressed);

  /*
    (1) audio player
  */
  this->audio_player = new QMediaPlayer(this);

  if (this->dipydoc.audiorecord.found == true) {
    DebugMsg() << "loading audiofile" << this->dipydoc.audiorecord.filename;
    this->audio_player->setMedia(QUrl::fromLocalFile(this->dipydoc.audiorecord.filename));

    this->audio_player->setNotifyInterval(fixedparameters::default__audio_notify_interval);
    this->audio_player->setVolume(fixedparameters::default__audio_player_volume);
  }

  /*
    (1) setting the object : UI
  */
  DebugMsg() << "[SourceZone::SourceZone] this->setStyleSheet = " << QString("#%1 {border: 0px; padding: 0px}").arg(object_name);
  this->setStyleSheet(QString("#%1 {border: 0px; padding: 0px}").arg(object_name));

  this->editor = new SourceEditor(splitter_name,
                                  this->readingmode,
                                  this->readingmode_details,
                                  this->dipydoc,
                                  this->audio_player,
                                  this->audiocontrols_playAct,
                                  this->audiocontrols_stopAct,
                                  this->blocked_commentaries,
                                  this);
  this->toolbar = new SourceToolBar(splitter_name,
                                    this);

  // (confer doc.) connection #C005
  QObject::connect(this->editor, &SourceEditor::signal__source_zone_update_icons,
                   this,         &SourceZone::update_icons);

  this->layout = new QHBoxLayout();
  this->layout->addWidget(this->editor);
  this->layout->addWidget(this->toolbar);

  this->setLayout(this->layout);

  /*
    (2) actions
  */
  this->textminusAct = new QAction(*(icons.textminus), tr("$$$source/minus"), this);
  this->textplusAct  = new QAction(*(icons.textplus),  tr("$$$source/plus"), this);

  this->toolbar->addAction(this->readingmode_rAct);
  this->toolbar->addSeparator();
  this->toolbar->addAction(this->readingmode_lAct);
  this->toolbar->addAction(this->audiocontrols_playAct);
  this->toolbar->addAction(this->audiocontrols_stopAct);
  this->toolbar->addSeparator();
  this->toolbar->addAction(this->readingmode_aAct);
  this->toolbar->addSeparator();
  this->toolbar->addAction(this->textplusAct);
  this->toolbar->addAction(this->textminusAct);

  QObject::connect(this->textminusAct, &QAction::triggered,
                   this->editor,       &SourceEditor::zoom_out);

  QObject::connect(this->textplusAct,  &QAction::triggered,
                   this->editor,       &SourceEditor::zoom_in);

  QObject::connect(this->audio_player, &QMediaPlayer::positionChanged,
                   this,               &SourceZone::audio_position_changed);

  /*
    (3) default reading mode
  */
  this->readingmode         = READINGMODE::READINGMODE_RMODE;
  this->readingmode_details = READINGMODEDETAILS::READINGMODEDETAIL_RMODE;
  DebugMsg() << "now in RMODE mode";

  /*
    (4) zoom values for this document :
  */
  QSettings settings;
  QString setting_name;

  setting_name = QString("text/%1/sourceeditor/zoomvalue").arg(this->dipydoc.qsettings_name);
  if (settings.contains(setting_name) == true) {
    this->editor->set_zoom_value(settings.value(setting_name).toInt());
  } else {
    this->editor->set_zoom_value(fixedparameters::default__zoom_value);
  }

  setting_name = QString("text/%1/commentaryeditor/zoomvalue").arg(this->dipydoc.qsettings_name);
  if (settings.contains(setting_name) == true) {
    this->editor->set_zoom_value(settings.value(setting_name).toInt());
  } else {
    // (confer doc.) signal #S002 :
    emit this->signal__set_zoom_value_in_commentary_editor(fixedparameters::default__zoom_value);
  }

  /*
    (5) updating document aspect :
  */
  // update source editor aspect :
  this->editor->update_aspect_from_dipydoc_aspect_informations();

  // update commentary editor aspect :
  // (confer doc.) signal S001 :
  emit this->signal__in_commentary_editor_update_from_dipydoc_info();

  /*
    (6) updating the icons
  */
  this->update_icons();

  DebugMsg() << "SourceZone::SourceZone : exit point";
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
          this->audiocontrols_playAct->setIcon(*(icons.audio_pause));
          this->audio_player->pause();
          break;
        }

        // [1.2] LMODE + ON PAUSE -> LMODE + PLAYING
        case READINGMODEDETAIL_LMODE_ONPAUSE: {
          this->readingmode_details = READINGMODEDETAIL_LMODE_PLAYING;
          this->audiocontrols_playAct->setIcon(*(icons.audio_play));
          this->audio_player->play();
          break;
        }

        // [1.3] LMODE + STOP -> LMODE + PLAYING
        case READINGMODEDETAIL_LMODE_STOP: {
          this->readingmode_details = READINGMODEDETAIL_LMODE_PLAYING;
          this->audiocontrols_playAct->setIcon(*(icons.audio_play));
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
  DebugMsg() << "SourceZone::audiocontrols_stop";

  // LMODE + ON PAUSE ? we set the icon from "pause" to "play".
  if (this->readingmode == READINGMODE_LMODE &&
      this->readingmode_details == READINGMODEDETAIL_LMODE_ONPAUSE) {
    this->audiocontrols_playAct->setIcon(*(icons.audio_play));
  }

  this->readingmode_details = READINGMODEDETAIL_LMODE_STOP;

  audio_player->stop();

  this->editor->reset_all_text_format_to_default();
}

/*______________________________________________________________________________

  SourceZone::audio_position_changed

________________________________________________________________________________*/
void SourceZone::audio_position_changed(qint64 arg_pos) {
  /* LMODE + PLAYING :
   */
  if (this->readingmode == READINGMODE_LMODE &&
      this->readingmode_details == READINGMODEDETAIL_LMODE_PLAYING) {
      // where are the characters linked to "arg_pos" ?
      PosInTextRanges text_ranges = this->dipydoc.audio2text_contains(arg_pos);
      std::size_t text_ranges_hash = text_ranges.get_hash();

      if (text_ranges_hash != this->editor->modified_chars_hash) {
        // the function modifies the appearence of such characters :
        this->editor->modify_the_text_format(text_ranges);

        // hash update :
        this->editor->modified_chars_hash = text_ranges_hash;

        // (confer doc.) signal #S008 :
        emit this->signal__update_commentary_zone_content(text_ranges);
      }

      return;
  }

  /*
    this->readingmode == READINGMODE_LMODE &&
    this->readingmode_details == READINGMODEDETAIL_LMODE_ONPAUSE

    -> nothing to do.
  */
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
  DebugMsg() << "switched to AMODE mode";
  this->update_icons();
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
  DebugMsg() << "switched to RMODE mode";
  this->update_icons();
}

/*______________________________________________________________________________

  SourceZone::readingmode_lAct__buttonpressed()

  connected to readingmode_lAct::triggered()
______________________________________________________________________________*/
void SourceZone::readingmode_lAct__buttonpressed(void) {
  this->readingmode = READINGMODE_LMODE;
  this->readingmode_details = READINGMODEDETAIL_LMODE_STOP;
  DebugMsg() << "switched to LMODE mode";
  this->update_icons();
}

/*______________________________________________________________________________

  SourceZone::update_icons()

  Update the icons along the current Dipydoc and the reading mode.
________________________________________________________________________________*/
void SourceZone::update_icons(void) {
  DebugMsg() << "SourceZone::update_icons; readingmode=" << this->readingmode;

  /*............................................................................
    normal case : more than one Dipydoc has been loaded.
  ............................................................................*/
  if (this->visible_toolbars == false) {
    /*
      invisible toolbars :
    */
    this->toolbar->hide();
    // (confer doc.) signal #S003 :
    emit this->signal__hide_toolbar_in_the_commentary_zone();
  } else {
    /*
       visible toolbars :
    */

    // toolbars are visible :
    if (this->visible_toolbars == true && this->toolbar->isVisible() == false) {
      this->toolbar->show();
      // (confer doc.) signal #S004 :
      emit this->signal__show_toolbar_in_the_commentary_zone();
    }

    /*
      source zone.toolbar.readingmode_icons :
    */
    switch (this->readingmode) {
      case READINGMODE_AMODE: {
        this->readingmode_aAct->setIcon(*(icons.readingmode_amode_on));
        this->readingmode_rAct->setIcon(*(icons.readingmode_rmode_off));
        this->readingmode_lAct->setIcon(*(icons.readingmode_lmode_off));
        this->audiocontrols_playAct->setVisible(false);
        this->audiocontrols_stopAct->setVisible(false);
        break;
      }

      case READINGMODE_LMODE: {
        this->readingmode_aAct->setIcon(*(icons.readingmode_amode_off));
        this->readingmode_rAct->setIcon(*(icons.readingmode_rmode_off));
        this->readingmode_lAct->setIcon(*(icons.readingmode_lmode_on));

        // audio control icons :
        if ((this->dipydoc.well_initialized() == false) ||
            (this->dipydoc.audiorecord.found == false)) {
          // special cases : a problem occurs, let's hide the audio icons.
          this->audiocontrols_playAct->setVisible(false);
          this->audiocontrols_stopAct->setVisible(false);
        } else {
          // normal case : let's show the audio icons.
          this->audiocontrols_playAct->setVisible(true);
          this->audiocontrols_stopAct->setVisible(true);
        }
        break;
      }

      case READINGMODE_RMODE: {
        this->readingmode_aAct->setIcon(*(icons.readingmode_amode_off));
        this->readingmode_rAct->setIcon(*(icons.readingmode_rmode_on));
        this->readingmode_lAct->setIcon(*(icons.readingmode_lmode_off));
        this->audiocontrols_playAct->setVisible(false);
        this->audiocontrols_stopAct->setVisible(false);
        break;
      }

      default : {
        break;
      }
    }
  }
}
