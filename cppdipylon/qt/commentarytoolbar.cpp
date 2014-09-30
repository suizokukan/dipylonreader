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

    ❏DipylonReader❏ : qt/commentarytoolbar.cpp

    See commentarytoolbar.h for the documentation.

*******************************************************************************/

#include "qt/commentarytoolbar.h"

/*______________________________________________________________________________

  CommentaryToolBar::constructor
______________________________________________________________________________*/
CommentaryToolBar::CommentaryToolBar(UI& _ui) : ui(_ui) {
  DebugMsg() << "CommentaryToolBar::CommentaryToolBar : entry point";

  this->setOrientation(Qt::Vertical);

  this->addAction(this->ui.mainWin->commentary_textplusAct);
  this->addAction(this->ui.mainWin->commentary_textminusAct);

  QObject::connect(this->ui.mainWin->commentary_textminusAct, &QAction::triggered,
                   this,                                      &CommentaryToolBar::textminusAct__buttonpressed);
  QObject::connect(this->ui.mainWin->commentary_textplusAct,  &QAction::triggered,
                   this,                                      &CommentaryToolBar::textplusAct__buttonpressed);

  DebugMsg() << "CommentaryToolBar::CommentaryToolBar : exit point";
}

/*______________________________________________________________________________

  CommentaryToolBar::textminusAct__buttonpressed
______________________________________________________________________________*/
void CommentaryToolBar::textminusAct__buttonpressed(void) {
  DebugMsg() << "CommentaryToolBar::textminusAct__buttonpressed";
}
/*______________________________________________________________________________

  CommentaryToolBar::textplusAct__buttonpressed
______________________________________________________________________________*/
void CommentaryToolBar::textplusAct__buttonpressed(void) {
  DebugMsg() << "CommentaryToolBar::textplusAct__buttonpressed";
}
