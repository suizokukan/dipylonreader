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
SourceZone::SourceZone(UI& _ui) : ui(_ui) {
  DebugMsg() << "SourceZone::SourceZone : entry point";

  DebugMsg() << "SourceZone::SourceZone : creating SourceEditor object";
  this->ui.mainWin->source_editor = new SourceEditor(this->ui);

  DebugMsg() << "SourceZone::SourceZone : creating SourceToolBar object";
  this->ui.mainWin->source_toolbar = new SourceToolBar(this->ui);

  this->layout = new QHBoxLayout();
  this->layout->addWidget(this->ui.mainWin->source_editor);
  this->layout->addWidget(this->ui.mainWin->source_toolbar);

  this->setLayout(this->layout);

  DebugMsg() << "SourceZone::SourceZone : exit point";
}
