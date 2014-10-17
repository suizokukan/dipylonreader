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

    ❏DipylonReader❏ : qt/commentaryzone.cpp

    See commentaryzone.h for the documentation.

*******************************************************************************/

#include "qt/commentaryzone.h"

/*______________________________________________________________________________

  CommentaryZone::constructor
______________________________________________________________________________*/
CommentaryZone::CommentaryZone(const QString & splitter_name,
                               const DipyDoc _dipydoc,
                               QWidget *_parent) : QFrame(_parent),
                                                   dipydoc(_dipydoc) {
  DebugMsg() << "CommentaryZone::CommentaryZone : entry point";

  QString object_name(splitter_name + "::commentary_zone");
  this->setObjectName(object_name);

  DebugMsg() << "CommentaryZone::CommentaryZone : creating CommentaryEditor object";
  this->editor = new CommentaryEditor(this);

  DebugMsg() << "CommentaryZone::CommentaryZone : creating CommentaryToolBar object";
  this->toolbar = new CommentaryToolBar(this);

  this->layout = new QHBoxLayout();
  this->layout->addWidget(this->editor);
  this->layout->addWidget(this->toolbar);

  this->setLayout(this->layout);

  /*
    (2) signals : signals between the editors and the toolbars :
  */
  QObject::connect(this->textminusAct, &QAction::triggered,
                   this->editor,       &CommentaryEditor::zoom_out);
  QObject::connect(this->textplusAct,  &QAction::triggered,
                   this->editor,       &CommentaryEditor::zoom_in);

  DebugMsg() << "CommentaryZone::CommentaryZone : exit point";
}
