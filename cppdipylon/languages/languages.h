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

    ❏DipylonReader❏ : languages/languages.h

    General definitions about the languages the program is dealing about.

*******************************************************************************/

#ifndef CPPDIPYLON_LANGUAGES_LANGUAGES_H_
#define CPPDIPYLON_LANGUAGES_LANGUAGES_H_

#include <QString>
#include <QObject>

#include <map>

/*______________________________________________________________________________

  known_languages : name of the languages recognized by the program with
                    their short names (ISO 639-3) and their English long names.

                    If no ISO 639-3 exists, use whatever string.

______________________________________________________________________________*/
namespace languages {
    const std::map<QString, QString> known_languages = {
      // ISO 639-3 names :
      { QString("ang"), QString(QObject::tr("Old English")) },
      { QString("bod"), QString(QObject::tr("Tibetan")) },
      { QString("deu"), QString(QObject::tr("German")) },
      { QString("fra"), QString(QObject::tr("French")) },
      { QString("grc"), QString(QObject::tr("Ancient Greek")) },
      { QString("hbo"), QString(QObject::tr("Biblical Hebrew")) },
      { QString("jpn"), QString(QObject::tr("Japan")) },
      { QString("lat"), QString(QObject::tr("Latin")) },
      { QString("san"), QString(QObject::tr("Sanskrit")) },

      // non-ISO 639-3 names :
      { QString("haut_marnais"), QString(QObject::tr("haut-marnais")) },
    };
}  // namespace languages

#endif  // CPPDIPYLON_LANGUAGES_LANGUAGES_H_
