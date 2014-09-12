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

    code adapted from http://stackoverflow.com/questions/2179623

*******************************************************************************/

#ifndef CPPDIPYLON_DEBUGMSG_DEBUGMSG_H_
#define CPPDIPYLON_DEBUGMSG_DEBUGMSG_H_

#include <QDebug>
#include <QPoint>
#include <QSize>
#include <QStringList>

/*
  even if, according to cpplint, "streams are highly discouraged", it seems
  reasonnable to use them here.
*/
#include <iostream>  // NOLINT(readability/streams)
#include <sstream>

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

  static QStringList          messages;

 private:
                    std::ostringstream stream;
};

inline DebugMsg::DebugMsg() {
}

inline DebugMsg::~DebugMsg() {
  #ifdef DEBUG_MESSAGES_TO_CERR
  std::cerr << stream.str() << std::endl;
  #endif

  #ifdef STORE_DEBUG_MESSAGES
  DebugMsg::messages << QString::fromStdString(stream.str());
  #endif

  /*
    use QT_NO_DEBUG_OUTPUT to allow/disallow the qDebug() output :
  */
  qDebug() << QString::fromStdString(stream.str());
}

inline DebugMsg& DebugMsg::operator<<(const int& argument) {
  stream << argument;
  return *this;
}

inline DebugMsg& DebugMsg::operator<<(const QString& argument) {
  stream << argument.toStdString();
  return *this;
}

inline DebugMsg& DebugMsg::operator<<(const bool& argument) {
  if( argument == true ) {
    stream << "true";
  } else {
    stream << "false";
  }
  return *this;
}

inline DebugMsg& DebugMsg::operator<<(const QPoint& argument) {
   stream << "(" \
          << argument.x() \
          << "," \
          << argument.y() \
          << ")";
  return *this;
}

inline DebugMsg& DebugMsg::operator<<(const QSize& argument) {
   stream << "(" \
          << argument.width() \
          << ","                                 \
          << argument.height() \
          << ")";
  return *this;
}

template<class T> inline DebugMsg& DebugMsg::operator<<(const T& argument) {
  stream << argument;
  return *this;
}

#endif  // CPPDIPYLON_DEBUGMSG_DEBUGMSG_H_
