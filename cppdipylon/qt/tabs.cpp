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

    ❏DipylonReader❏ : qt/tabs.cpp

    see tabs.h

*******************************************************************************/

#include "qt/tabs.h"

/*______________________________________________________________________________

  Tabs::Tabs

  Tabs' constructor.

______________________________________________________________________________*/
void Tabs::Tabs(QWidget *_parent) : QTabWidget(_parent),
  this->setObjectName("main_window__tabwidget");

  DebugMsg() << "[MainWindow::init] this->setStyleSheet = " << fixedparameters::default__tabwiget_stylesheet;
  this->tabs->setStyleSheet(fixedparameters::default__tabwiget_stylesheet);

  this->tabs->setTabsClosable(true);
}

/*______________________________________________________________________________

  Tabs::tabCloseRequested

  Function called when a close button is pressed.
______________________________________________________________________________*/
void Tabs::tabCloseRequested(int index) {
  DebugMsg() << "Tabs::tabCloseRequested; index=" << index;
  delete this->widget(index);
}
