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

    ❏DipylonReader❏ : qt/sourcetoolbar.cpp

    See sourcetoolbar.h for the documentation.

*******************************************************************************/

#include "qt/sourcetoolbar.h"

/*______________________________________________________________________________

  SourceToolBar::constructor
______________________________________________________________________________*/
SourceToolBar::SourceToolBar(UI& _ui) : ui(_ui) {
  DebugMsg() << "SourceToolBar::SourceToolBar : entry point";

  this->setOrientation(Qt::Vertical);

  this->addAction(this->ui.mainWin->readingmode_rAct);
  this->addSeparator();
  this->addAction(this->ui.mainWin->readingmode_lAct);
  this->addAction(this->ui.mainWin->audiocontrols_playAct);
  this->addAction(this->ui.mainWin->audiocontrols_stopAct);
  this->addSeparator();
  this->addAction(this->ui.mainWin->readingmode_aAct);
  this->addSeparator();
  this->addAction(this->ui.mainWin->source_textplusAct);
  this->addAction(this->ui.mainWin->source_textminusAct);

  QObject::connect(this->ui.mainWin->source_textminusAct, &QAction::triggered,
                   this,                                  &SourceToolBar::textminusAct__buttonpressed);
  QObject::connect(this->ui.mainWin->source_textplusAct,  &QAction::triggered,
                   this,                                  &SourceToolBar::textplusAct__buttonpressed);

  DebugMsg() << "SourceToolBar::SourceToolBar : exit point";
}

/*______________________________________________________________________________

  SourceToolBar::textminusAct__buttonpressed
______________________________________________________________________________*/
void SourceToolBar::textminusAct__buttonpressed(void) {
  DebugMsg() << "SourceToolBar::textminusAct__buttonpressed";
}
/*______________________________________________________________________________

  SourceToolBar::textplusAct__buttonpressed
______________________________________________________________________________*/
void SourceToolBar::textplusAct__buttonpressed(void) {
  DebugMsg() << "SourceToolBar::textplusAct__buttonpressed";
}
