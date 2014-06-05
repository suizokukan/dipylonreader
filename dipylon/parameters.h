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

    ❏Dipylon❏ : parameters.h

    Parameters used throughout the program.

*******************************************************************************/

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QList>
#include <QString>

/*______________________________________________________________________________
  
  struct where the parameters are stored. Its unique instance is "parameters"
______________________________________________________________________________*/
struct {

  /* 
        data used to initialize the QApplication object.

        see http://qt-project.org/doc/qt-5/qcoreapplication.html
  */
  const QString organization_name   = QString("suizokukan's factory");
  const QString organization_domain = QString("94.23.197.37");
  const QString application_name    = QString("Dipylon");
  const QString application_version = QString("0.1.9");
  const QString application_style   = QString("CleanLooks");

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

  /* 
     constant used by QMediaPlayer object.
     see http://qt-project.org/doc/qt-5/qmediaobject.html#notifyInterval-prop
  */
  const int audio_notify_interval = 500;
} parameters;

#endif
