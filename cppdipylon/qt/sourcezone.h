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

#include <QAction>
#include <QFrame>
#include <QHBoxLayout>
#include <QMediaPlayer>
#include <QSettings>

#include "debugmsg/debugmsg.h"
#include "dipydoc/dipydoc.h"
#include "qt/readingmodes.h"
#include "qt/sourceeditor.h"
#include "qt/sourcetoolbar.h"

class MainWindow;

/*______________________________________________________________________________

  SourceZone class
______________________________________________________________________________*/
class SourceZone : public QFrame {
friend class MainWindow;

    Q_OBJECT

 private slots:  // NOLINT(whitespace/indent)
    void audiocontrols_play(void);
    void audiocontrols_stop(void);
    void audio_position_changed(PosInAudio);
    void readingmode_aAct__buttonpressed(void);
    void readingmode_rAct__buttonpressed(void);
    void readingmode_lAct__buttonpressed(void);

 private:
  void update_icons(void);
  const DipyDoc& dipydoc = DipyDoc();

  bool & selected_text_and_blocked_commentaries;
  bool & visible_toolbars;

  ReadingMode        readingmode;
  ReadingModeDetails readingmode_details;

  QAction* readingmode_aAct = nullptr;
  QAction* readingmode_rAct = nullptr;
  QAction* readingmode_lAct = nullptr;
  QAction* audiocontrols_playAct = nullptr;
  QAction* audiocontrols_stopAct = nullptr;

  QAction* textminusAct = nullptr;
  QAction* textplusAct = nullptr;

  QMediaPlayer* audio_player = nullptr;
  QLayout* layout = nullptr;
  SourceEditor* editor = nullptr;
  SourceToolBar* toolbar = nullptr;

 public:
  explicit SourceZone(const QString & splitter_name,
                      const DipyDoc & _dipydoc,
                      bool          & _selected_text_and_blocked_commentaries,
                      bool          & _visible_toolbars,
                      QWidget *_parent);
};

#endif  // CPPDIPYLON_QT_SOURCEZONE_H_
