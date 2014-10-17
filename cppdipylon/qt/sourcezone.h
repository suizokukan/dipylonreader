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

    ❏DipylonReader❏ : qt/sourcezone.h

    o SourceZone class

*******************************************************************************/

#ifndef CPPDIPYLON_QT_SOURCEZONE_H_
#define CPPDIPYLON_QT_SOURCEZONE_H_

#include <QFrame>
#include <QHBoxLayout>
#include <QMediaPlayer>

#include "debugmsg/debugmsg.h"
#include "dipydoc/dipydoc.h"
#include "qt/readingmodes.h"
#include "qt/sourceeditor.h"
#include "qt/sourcetoolbar.h"

class MainWindow;
class UI;

/*______________________________________________________________________________

  SourceZone class
______________________________________________________________________________*/
class SourceZone : public QFrame {
friend MainWindow;

    Q_OBJECT

 private slots:  // NOLINT(whitespace/indent)
    void audiocontrols_play(void);
    void audiocontrols_stop(void);
    void audio_position_changed(PosInAudio);
    void readingmode_aAct__buttonpressed(void);
    void readingmode_rAct__buttonpressed(void);
    void readingmode_lAct__buttonpressed(void);

 private:
  const DipyDoc& dipydoc = DipyDoc();
  UI& ui;                                 // UI object linked to the editor

  ReadingMode        reading_mode = READINGMODE_UNDEFINED;
  ReadingModeDetails reading_mode_details = READINGMODEDETAIL_UNDEFINED;

  QAction* readingmode_aAct = nullptr;
  QAction* readingmode_rAct = nullptr;
  QAction* readingmode_lAct = nullptr;
  QAction* audiocontrols_playAct = nullptr;
  QAction* audiocontrols_stopAct = nullptr;

  QMediaPlayer* audio_player = nullptr;
  QLayout* layout = nullptr;
  SourceEditor* editor = nullptr;
  SourceToolBar* toolbar = nullptr;

 public:
  explicit SourceZone(const QString & splitter_name,
                      const DipyDoc& _dipydoc,
                      UI& _ui,
                      QWidget *_parent);
};

#endif  // CPPDIPYLON_QT_SOURCEZONE_H_
