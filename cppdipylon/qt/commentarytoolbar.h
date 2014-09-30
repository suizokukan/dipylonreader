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

    ❏DipylonReader❏ : qt/commentarytoolbar.h

    o CommentaryToolBar class

*******************************************************************************/

#ifndef CPPDIPYLON_QT_COMMENTARYTOOLBAR_H_
#define CPPDIPYLON_QT_COMMENTARYTOOLBAR_H_

#include <QToolBar>

#include "debugmsg/debugmsg.h"
#include "qt/ui.h"

class UI;

/*______________________________________________________________________________

  CommentaryToolBar class
______________________________________________________________________________*/
class CommentaryToolBar : public QToolBar {

    Q_OBJECT

 private:
 // UI object linked to the editor :
 UI& ui;

 private slots:
   void textminusAct__buttonpressed(void);
   void textplusAct__buttonpressed(void);

 public:
  CommentaryToolBar(UI& _ui);
};
#endif  // CPPDIPYLON_QT_COMMENTARYTOOLBAR_H_
