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

    ❏DipylonReader❏ : fixedparameters.h

    Fixed parameters used throughout the program.

*******************************************************************************/

#ifndef FIXEDPARAMETERS_H
#define FIXEDPARAMETERS_H

#include <QList>
#include <QString>
#include <QDir>

namespace fixedparameters {

/*
  data used to initialize the QApplication object.

  see http://qt-project.org/doc/qt-5/qcoreapplication.html
*/
static const QString organization_name   = "suizokukanfactory";
static const QString organization_domain = "94.23.197.37";
static const QString application_name    = "dipylonreader";
static const QString application_version = "0.4.0";
static const QString application_style   = "CleanLooks";

/*
  default__editors_size_in_main_splitter = sourceeditor / commentaryeditor size.
*/
static const QList<int> default__editors_size_in_main_splitter = {{500,100}};

/*
  static constant used by QMediaPlayer object.
*/
// http://qt-project.org/doc/qt-5/qmediaobject.html#notifyInterval-prop
static const int default__audio_notify_interval = 500;
// http://qt-project.org/doc/qt-5/qmediaplayer.html#volume-prop
static const int default__audio_player_volume = 50;

/*
   default path to the dipydocs.
*/
static const QString default__path_to_dipydocs  = QDir::homePath() + "/dipydocs/";

/*
  editors' default style sheets :
*/
const QString default__sourceeditor_stylesheet = "background-color: #4169E1;"
                                                 "selection-color: white;"
                                                 "selection-background-color: blue;";

const QString default__commentaryeditor_stylesheet = "color: white;"
                                                     "background-color: #191970;"
                                                     "selection-color: yellow;"
                                                     "selection-background-color: red;";

const QStringList known_doctypes = { QString("text"), };

/*
  splash screen
*/
static const int splashscreen_maximal_duration = 9000;
static const bool default__display_splashscreen = true;
}
#endif
