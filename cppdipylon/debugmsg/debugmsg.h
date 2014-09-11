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
#include <QPoint>
#include <QSize>

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
                    DebugMsg& operator<<(const QString& argument);
                    DebugMsg& operator<<(const bool& argument);
                    DebugMsg& operator<<(const QPoint& argument);
                    DebugMsg& operator<<(const QSize& argument);
  template<class T> DebugMsg& operator<<(const T& argument);

 private:
                    std::ostringstream stream;
};

inline DebugMsg::DebugMsg() {
}

inline DebugMsg::~DebugMsg() {
  //std::cerr << stream.str() << std::endl;
  qDebug() << stream;
}

inline DebugMsg& DebugMsg::operator<<(const int& argument) {
  stream << argument;
  debug_messages << QString().setNum(argument);
  return *this;
}

inline DebugMsg& DebugMsg::operator<<(const QString& argument) {
  stream << argument.toStdString();
  debug_messages << argument;
  return *this;
}

inline DebugMsg& DebugMsg::operator<<(const bool& argument) {
  if( argument == true ) {
    stream << "true";
    debug_messages << "true";
  } else {
    stream << "false";
    debug_messages << "false";
  }
  return *this;
}

inline DebugMsg& DebugMsg::operator<<(const QPoint& argument) {
   stream << "(" \
          << argument.x() \
          << "," \
          << argument.y() \
          << ")";

   debug_messages << "(" \
                  << QString().setNum(argument.x()) \
                  << "," \
                  << QString().setNum(argument.y()) \
                  << ")";
  return *this;
}

inline DebugMsg& DebugMsg::operator<<(const QSize& argument) {
   stream << "(" \
          << argument.width() \
          << ","                                 \
          << argument.height() \
          << ")";

   debug_messages << "(" \
                  << QString().setNum(argument.width()) \
                  << ","                                 \
                  << QString().setNum(argument.height()) \
                  << ")";
  return *this;
}

template<class T> inline DebugMsg& DebugMsg::operator<<(const T& argument) {
  stream << argument;
  debug_messages << argument;
  return *this;
}

#endif  // CPPDIPYLON_DEBUGMSG_DEBUGMSG_H_
