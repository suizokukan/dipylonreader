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

#include <QMessageBox>
#include <QSplitter>
#include <QString>

#include "dipydoc/dipydoc.h"
#include "qt/commentaryzone.h"
#include "qt/sourcezone.h"

/*______________________________________________________________________________

  SourceCommentarySplitter class

  Splitter bewteen a SourceZone object and a CommentaryZone object.
______________________________________________________________________________*/
class SourceCommentarySplitter : public QSplitter {
friend class MainWindow;

    Q_OBJECT

 private:
  bool & visible_toolbars;
  bool  _well_initialized = false;               // object state
  bool  blocked_commentaries = false;

  DipyDoc dipydoc = DipyDoc();

  SourceZone* source_zone = nullptr;            // (ui) source zone
  CommentaryZone* commentary_zone = nullptr;    // (ui) commentary zone

 public:
  bool well_initialized(void);
  explicit SourceCommentarySplitter(const QString& directoryName,
                                    bool & _visible_toolbars,
                                    QWidget *_parent);
};

#endif
