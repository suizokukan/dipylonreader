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

    o debug_messages : list of debug messages
    o DebugMsg class

    Each call to DebugMsg() adds a message into 'debug_messages'.

    code adapted from http://stackoverflow.com/questions/2179623

*******************************************************************************/

#ifndef CPPDIPYLON_DEBUGMSG_DEBUGMSG_H_
#define CPPDIPYLON_DEBUGMSG_DEBUGMSG_H_

#include <QStringList>

/*
  even if, according to cpplint, "streams are highly discouraged", it seems
  reasonnable to use them here.
*/
#include <iostream>  // NOLINT(readability/streams)
#include <sstream>

static QStringList debug_messages;

/*______________________________________________________________________________

  DebugMsg class : the main idea is to add the successive paramaters in a stream
                   and to display this stream when the object is deleted.

______________________________________________________________________________*/
class DebugMsg {
 public:
                    DebugMsg(void);
                    ~DebugMsg(void);

                    DebugMsg& operator<<(const int& argument);
  template<class T> DebugMsg& operator<<(const T& argument);

 private:
                    std::ostringstream stream;
};

DebugMsg::DebugMsg() {
}

DebugMsg::~DebugMsg() {
  std::cerr << stream.str() << std::endl;
}

DebugMsg& DebugMsg::operator<<(const int& argument) {
  stream << argument;
  debugmsg << QString().setNum(argument);
  return *this;
}

template<class T> DebugMsg& DebugMsg::operator<<(const T& argument) {
  stream << argument;
  debugmsg << argument;
  return *this;
}


#endif  // CPPDIPYLON_DEBUGMSG_DEBUGMSG_H_
