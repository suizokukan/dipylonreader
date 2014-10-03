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
CommentaryToolBar::CommentaryToolBar(const UI& _ui) : ui(_ui) {
  DebugMsg() << "CommentaryToolBar::CommentaryToolBar : entry point";

  this->setObjectName("commentary zone::toolbar");

  this->setOrientation(Qt::Vertical);

  this->addAction(this->ui.mainWin->commentary_textplusAct);
  this->addAction(this->ui.mainWin->commentary_textminusAct);

  DebugMsg() << "CommentaryToolBar::CommentaryToolBar : exit point";
}
