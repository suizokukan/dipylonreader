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

    ❏Dipylon❏ : fixedparameters.h

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
static const QString organization_name   = "suizokukan's factory";
static const QString organization_domain = "94.23.197.37";
static const QString application_name    = "Dipylon";
static const QString application_version = "0.2.5";
static const QString application_style   = "CleanLooks";

/*
  editors_size_in_main_splitter = sourceeditor / commentaryeditor size.
*/
static const QList<int> editors_size_in_main_splitter = {{500,100}};

/*
  static constant used by QMediaPlayer object.
*/
// http://qt-project.org/doc/qt-5/qmediaobject.html#notifyInterval-prop
static const int audio_notify_interval = 500;
// http://qt-project.org/doc/qt-5/qmediaplayer.html#volume-prop
static const int audio_player_volume = 50;

/* default path to the dipydocs.
*/
//$$$static const QString default_path_to_dipydocs  = QDir::homePath() + "/dipydocs/";
static const QString default_path_to_dipydocs  = QDir::homePath() + "/projets/freedipydocs/";

/*
  editors' default style sheets :
*/
const QString sourceeditor_default_stylesheet = "background-color: #4169E1;"
                                                "selection-color: white;"
                                                "selection-background-color: blue;";

const QString commentaryeditor_default_stylesheet = "color: white;"
                                                    "background-color: #191970;"
                                                    "selection-color: yellow;"
                                                    "selection-background-color: red;";

/*
  source editor text formats :

  text format : see textformat.h::TEXTFORMAT_SRCSTRING_FORMAT format.
*/
const QString sourceeditor_default_textformat  = "color=white;";
const QString sourceeditor_karaoke_textformat  = "color=red;";
}
#endif
