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

    ❏Dipylon❏ : qt/parameters.h

    Parameters used to define the UI.

*******************************************************************************/

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QList>
#include <QString>

/*______________________________________________________________________________
  
  struct where the parameters are stored. Its unique instance is "ui_parameters"
______________________________________________________________________________*/
struct {

  /*
    editors_size_in_main_splitter = sourceeditor / commentaryeditor size.
  */
  const QList<int> editors_size_in_main_splitter = {{500,100}};

  const QString commentary_editor_stylesheet = "color: white;"
                                               "background-color: #DE8ABC;"
                                               "selection-color: yellow;"
                                               "selection-background-color: blue;";

  const QString source_editor_stylesheet = "color: white;"
                                           "background-color: #9ABCDE;"
                                           "selection-color: yellow;"
                                           "selection-background-color: blue;";
} ui_parameters;

#endif
