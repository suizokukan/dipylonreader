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

    ❏Dipylon❏ : debug/debug.h

    o Debug class

*******************************************************************************/

#ifndef CPPDIPYLON_DEBUG_DEBUG_H_
#define CPPDIPYLON_DEBUG_DEBUG_H_

static QStringList debugmsg;

struct Debug {
  Debug(void);
  template<class T> Debug& operator<<(const T& m);
};

Debug::Debug(void) {}
template<class T> inline Debug& Debug::operator<<(const T& parameter) {
  qDebug() << parameter;
  return *this;
}

#endif
