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

    ❏DipylonReader❏ : qt/sctabs.cpp

    see tabs.h

*******************************************************************************/

#include "qt/sctabs.h"

/*______________________________________________________________________________

  SCTabs::SCTabs

  SCTabs' constructor.
______________________________________________________________________________*/
SCTabs::SCTabs(QWidget *_parent) : QTabWidget(_parent) {
  this->setObjectName("main_window__tabwidget");

  DebugMsg() << "[MainWindow::init] this->setStyleSheet = " << fixedparameters::default__tabwiget_stylesheet;
  this->setStyleSheet(fixedparameters::default__tabwiget_stylesheet);

  this->setTabsClosable(true);

  // connection #C010 (confer documentation)
  QObject::connect(this->tabBar(), &QTabBar::tabCloseRequested,
                   this,           &SCTabs::close_current_tab);

  /*
    shortcuts
  */
  // (shortcut) CTRL + T :
  this->shortcut_ctrl_t = new QShortcut(QKeySequence(tr("Ctrl+T")), this);
  // connection #C011 (confer documentation)
  QObject::connect(this->shortcut_ctrl_t, &QShortcut::activated,
                   this,                  &SCTabs::signal__open_a_new_dipydoc);

  // (shortcut) CTRL + W :
  this->shortcut_ctrl_w = new QShortcut(QKeySequence(tr("Ctrl+W")), this);
  // connection #C012 (confer documentation)
  QObject::connect(this->shortcut_ctrl_w, &QShortcut::activated,
                   this,                  &SCTabs::close_current_tab);
}

/*______________________________________________________________________________

  SCTabs::close_current_tab

  Function called when the "closed button" of a the tab bar has been pressed.
______________________________________________________________________________*/
void SCTabs::close_current_tab(void) {
  DebugMsg() << "SCTabs::close_current_tab";
  delete this->widget(this->currentIndex());
}

/*______________________________________________________________________________

  SCTabs::tabInserted
______________________________________________________________________________*/
void SCTabs::tabInserted(int index) {
  SCSplitter* new_tab = qobject_cast<SCSplitter*>(this->widget(index));

  // connection #C013 (confer documentation)
  QObject::connect(new_tab, &SCSplitter::signal__close_the_current_dipydoc,
                   this,    &SCTabs::close_current_tab);

  // connection #C014 (confer documentation)
  QObject::connect(new_tab, &SCSplitter::signal__open_a_new_dipydoc,
                   this,    &SCTabs::signal__open_a_new_dipydoc);

  /*
    Since we're sure that at least one Dipydoc is displayed, let's display
    the "hidetoolbar" icon :
  */
  // SIGNAL #S005 (confer documentation)
  emit this->signal__display_hidetoolbar_icon(true);
}
