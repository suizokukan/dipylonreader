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

    ❏DipylonReader❏ : dipydoc/menunames.h

    MenuNames class

*******************************************************************************/

#ifndef CPPDIPYLON_DIPYDOC_MENUNAMES_H_
#define CPPDIPYLON_DIPYDOC_MENUNAMES_H_

#include "debugmsg/debugmsg.h"

/*______________________________________________________________________________

  MenuNames class

  Store in MenuNames the 'menu name' and the directory's name. The constructor
  with a QString parameter searches in the default path to find every 'menu name'
  file.
______________________________________________________________________________*/
typedef std::map<QString, QString> MAP_STR2STR;
typedef std::map<QString, QString>::const_iterator MAP_STR2STR_CI;

struct MenuNames {
  // menu name -> directory's name (full path).
  MAP_STR2STR    menuname_to_directory;

                 MenuNames(void);
                 MenuNames(const QString& path);
  MAP_STR2STR_CI begin(void) const;
  MAP_STR2STR_CI end(void) const;
  static QString read_menu_name_from_a_file_within_a_directory(const QString& path);
         QString repr(void) const;
};

/*______________________________________________________________________________

  MenuNames constructors.
______________________________________________________________________________*/
// default constructor
inline MenuNames::MenuNames(void) {
  this->menuname_to_directory.clear();
}

// let's search in 'path' to find every 'menu name' :
inline MenuNames::MenuNames(const QString& path) {
  this->menuname_to_directory.clear();

  QDir dipydocs_path(path);
  dipydocs_path.setFilter( QDir::AllDirs );

  for( auto &directory_name: dipydocs_path.entryList()) {
    if ( (directory_name != ".") && (directory_name != "..") ) {
      QString menuname(this->read_menu_name_from_a_file_within_a_directory(path + "/" + directory_name));
      if (menuname.size() != 0) {
        this->menuname_to_directory[menuname] = path + "/" + directory_name;
      }
    }
  }
}

/*______________________________________________________________________________

  MenuNames::begin(), MenuNames::end()
________________________________________________________________________________*/
inline MAP_STR2STR_CI MenuNames::begin(void) const {
  return this->menuname_to_directory.begin();
}
inline MAP_STR2STR_CI MenuNames::end(void) const {
  return this->menuname_to_directory.end();
}

/*______________________________________________________________________________

  MenuNames::read_menu_name_from_a_file_within_a_directory

    Return an empty QString if path doesn't contain the expected file or if this
  file is empty.

  static method
________________________________________________________________________________*/
inline QString MenuNames::read_menu_name_from_a_file_within_a_directory(const QString& path) {
  QString res;
  QFile menuname_file(path + "/" + fixedparameters::DIPYDOC__MENUNAME_FILENAME);

  if (menuname_file.open(QFile::ReadOnly)) {
    res = menuname_file.readLine();
    res = res.trimmed();
  }

 return res;
}

/*______________________________________________________________________________

  MenuNames::repr()
________________________________________________________________________________*/
inline QString MenuNames::repr(void) const {
  QStringList resl;

  for(auto &item : this->menuname_to_directory) {
    resl.append( QString("'%1' -> '%2'").arg(item.first, item.second) );
  }

  return resl.join("\n");
}

#endif  // CPPDIPYLON_DIPYDOC_MENUNAMES_H_
