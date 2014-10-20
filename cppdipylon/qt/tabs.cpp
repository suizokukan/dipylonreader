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
Tabs::Tabs(QWidget *_parent) : QTabWidget(_parent) {
  this->setObjectName("main_window__tabwidget");

  DebugMsg() << "[MainWindow::init] this->setStyleSheet = " << fixedparameters::default__tabwiget_stylesheet;
  this->setStyleSheet(fixedparameters::default__tabwiget_stylesheet);

  this->setTabsClosable(true);

  QObject::connect(this->tabBar(), &QTabBar::tabCloseRequested,
                   this,           &Tabs::close_tab);
}

/*______________________________________________________________________________

  Tabs::close_tab

  Function called when the "closed button" of a the tab bar has been pressed.
______________________________________________________________________________*/
void Tabs::close_tab(int index) {
  DebugMsg() << "Tabs::close_tab" << index;
  delete this->widget(index);
}
