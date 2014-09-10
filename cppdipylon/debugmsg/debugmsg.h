/*******************************************************************************

    Dipylon Copyright (C) 2008 Xavier Faure
    Contact: faure dot epistulam dot mihi dot scripsisti at orange dot fr

    This file is part of Dipylon.
    Dipylon is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Dipylon is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Dipylon.  If not, see <http://www.gnu.org/licenses/>.

    ____________________________________________________________________________

    ❏Dipylon❏ : debugmsg/debugmsg.h

    o DebugMsg class

*******************************************************************************/

#ifndef CPPDIPYLON_DEBUGMSG_DEBUGMSG_H_
#define CPPDIPYLON_DEBUGMSG_DEBUGMSG_H_

//#include <QStringList>
//static QStringList debugmsg;

struct DebugMsg {
  DebugMsg(void);
  template<class T> DebugMsg& operator<<(const T& m);
};

// constructor
DebugMsg::DebugMsg(void) {}

// DebugMsg::operator<<
template<class T> inline DebugMsg& DebugMsg::operator<<(const T& parameter) {
  qDebug() << parameter;
  return *this;
}

#endif
