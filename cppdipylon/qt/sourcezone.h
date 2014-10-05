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

#include "debugmsg/debugmsg.h"
#include "qt/sourceeditor.h"
#include "qt/sourcetoolbar.h"
#include "qt/ui.h"

class MainWindow;

/*______________________________________________________________________________

  SourceZone class
______________________________________________________________________________*/
class SourceZone : public QFrame {
friend MainWindow;

    Q_OBJECT

 private:
  // UI object linked to the editor :
  UI& ui;
  // object's layout :
  QLayout* layout = nullptr;

 public:
  explicit SourceZone(UI& _ui);
};

#endif  // CPPDIPYLON_QT_SOURCEZONE_H_
