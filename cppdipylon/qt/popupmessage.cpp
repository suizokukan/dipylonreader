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

    ❏DipylonReader❏ : qt/popupmessage.cpp

    see popupmessage.h for the documentation

*******************************************************************************/

#include "qt/popupmessage.h"

/*______________________________________________________________________________

        PopupMessage::PopupMessage()

        PopupMessage constructor.
______________________________________________________________________________*/
PopupMessage::PopupMessage(QWidget *_parent) : QLabel(_parent) {
  this->setWindowFlags(Qt::Tool);      // see http://doc.qt.io/qt-5/qt.html#WindowType-enum
  this->setFocusPolicy(Qt::NoFocus);  // see http://qt-project.org/doc/qt-4.8/qwidget.html#focusPolicy-prop
  this->setStyleSheet("border-radius: 9px; background-color: #12ffcc; color: red; border-width: 1px; border-style: solid;");
  
  this->setWindowFlags(Qt::CustomizeWindowHint);
  this->setWindowFlags(Qt::WindowStaysOnTopHint);
  this->setWindowFlags(Qt::X11BypassWindowManagerHint);
  
  this->hide();
}
