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

    ❏DipylonReader❏ : dipydoc/sctabs.h

    o SCTabs class, used to display DipyDoc(s).

*******************************************************************************/

#ifndef CPPDIPYLON_QT_SCTABS_H_
#define CPPDIPYLON_QT_SCTABS_H_

#include <QKeySequence>
#include <QShortcut>
#include <QTabBar>
#include <QTabWidget>
#include <QWidget>

#include "./fixedparameters.h"
#include "debugmsg/debugmsg.h"
#include "qt/scsplitter.h"

/*______________________________________________________________________________

  SCTabs class
______________________________________________________________________________*/
class SCTabs : public QTabWidget {

    Q_OBJECT

 signals:
  void signal__open_a_new_dipydoc(void);

 public slots:
  void close_current_tab(void);

 protected:
  void tabInserted(int index);

 public:
  SCTabs(QWidget *_parent);

 private:
  QShortcut*           shortcut_ctrl_t = nullptr;
  QShortcut*           shortcut_ctrl_w = nullptr;
};

#endif
