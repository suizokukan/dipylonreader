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

    ❏DipylonReader❏ : qt/sourcecommentarysplitter.h

    * SourceCommentarySplitter class

*******************************************************************************/

#ifndef CPPDIPYLON_QT_SOURCECOMMENTARYSPLITTER_H_
#define CPPDIPYLON_QT_SOURCECOMMENTARYSPLITTER_H_

#include "debugmsg/debugmsg.h"
#include "qt/ui.h"

#include <QAction>
#include <QMessageBox>
#include <QSplitter>
#include <QString>

/*______________________________________________________________________________

  SourceCommentarySplitter class

  Splitter bewteen a SourceZone object and a CommentaryZone object.
______________________________________________________________________________*/
class SourceCommentarySplitter : public QSplitter {

    Q_OBJECT

 private:
  bool _well_initialized = false;               // object state
  UI& ui;                                       // UI object linked to the editor
  DipyDoc& dipydoc = DipyDoc();                 // Dipydoc doc. displayed
  SourceZone* source_zone = nullptr;            // (ui) source zone
  CommentaryZone commentary_zone = nullptr;     // (ui) commentary zone

 public:
  explicit SourceCommentarySplitter(const QString& directoryName, UI& _ui, QWidget *_parent);
};

#endif
