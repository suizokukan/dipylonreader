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

    ❏DipylonReader❏ : qt/commentaryzone.h

    o CommentaryZone class

*******************************************************************************/

#ifndef CPPDIPYLON_QT_COMMENTARYZONE_H_
#define CPPDIPYLON_QT_COMMENTARYZONE_H_

#include <QAction>
#include <QFrame>
#include <QHBoxLayout>

#include "debugmsg/debugmsg.h"
#include "dipydoc/dipydoc.h"
#include "qt/commentaryeditor.h"
#include "qt/commentarytoolbar.h"
#include "qt/icons.h"

class MainWindow;

/*______________________________________________________________________________

  CommentaryZone class
______________________________________________________________________________*/
class CommentaryZone : public QFrame {
friend class MainWindow;

    Q_OBJECT

 private:
  // object's layout :
  QLayout* layout = nullptr;

  CommentaryEditor* editor = nullptr;
  CommentaryToolBar* toolbar = nullptr;

  const DipyDoc & dipydoc;
  bool & blocked_commentaries;

  QAction* textminusAct = nullptr;
  QAction* textplusAct = nullptr;

 public:
  explicit CommentaryZone(const QString & splitter_name,
                          const DipyDoc & _dipydoc,
                          bool & _blocked_commentaries,
                          QWidget* _parent);
};

#endif  // CPPDIPYLON_QT_COMMENTARYZONE_H_
