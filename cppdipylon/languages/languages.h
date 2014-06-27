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

    ❏Dipylon❏ : languages/languages.h

    General definitions about the languages the program is dealing about.

*******************************************************************************/

#ifndef LANGUAGES_H
#define LANGUAGES_H

#include <map>
#include <QString>
#include <QObject>

/*______________________________________________________________________________

  known_languages : name of the languages recognized by the program with
                    their short names (ISO 639-3) and their long names.

______________________________________________________________________________*/
namespace {
  std::map<QString, QString> known_languages = \
    {
      { QString("lat"), QString(QObject::tr("TR_Latin")) },
      { QString("fra"), QString(QObject::tr("TR_French")) },
    };
}

#endif
