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

// code source :
constexpr static const char*   CODESOURCE_ADDRESS = "http://github.com/suizokukan/dipylonreader/";
// code source's author :
constexpr static const char*   CODESOURCE_AUTHOR = "Xavier Faure";
// license's name :
constexpr static const char*   CODESOURCE_LICENSE = "GPLv3";
// license's address :
constexpr static const char*   CODESOURCE_LICENSE_ADDRESS= "http://www.gnu.org/copyleft/gpl.html";

/*
  data used to initialize the QApplication object.

  see http://qt-project.org/doc/qt-5/qcoreapplication.html
*/
static const QString organization_name   = "suizokukanfactory";
static const QString organization_domain = "94.23.197.37";
static const QString application_name    = "dipylonreader";
static const QString application_name_for_the_user = "Dipylon-R";
static const QString application_version = "0.4.5";
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
  default style sheets :
*/
const QString default__mainwindow_stylesheet = "";

const QString default__tabwiget_stylesheet = "background-color: #ffffcc;";

const QString default__sourceeditor_stylesheet = "background-color: #ffffcc;"
                                                 "selection-color: white;"
                                                 "selection-background-color: blue;";

const QString default__commentaryeditor_stylesheet = "color: white;"
                                                     "background-color: #ffcc99;"
                                                     "selection-color: yellow;"
                                                     "selection-background-color: red;";

const QStringList known_doctypes = { QString("text"), };

// default zoom value for both editors :
const int default__zoom_value = 1;

// maximum length in tab names.
const int maxlen_in_tab_name = 15;

/*
  settings
*/
// splash screen
static const int splashscreen_maximal_duration = 9000;
static const bool default__display_splashscreen = true;
// toolbars
static const bool default__visible_toolbars = true;

// name of the main file in a dipydoc directory :
constexpr static const char*   DIPYDOC__MAIN_FILENAME = "main.xml";
// name of the 'menu name' file  in a dipydoc directory :
constexpr static const char*   DIPYDOC__MENUNAME_FILENAME = "menuname";

// constant used to limit the number of items displayed in submenu 'open' :
static const int maximum_number_of_items_in_submenu_open = 10;

/*
  Demonstration's Dipydocs :
*/

// source site with '%1' for the version string.
#if defined DOWNLOAD_OGG_VERSION_OF_DIPYDOCS
constexpr static const char* DEMODIPYDOCS__SOURCE_SITE = "http://94.23.197.37/dipylon/freedipydocs/%1/ogg";
#elif defined DOWNLOAD_MP3_VERSION_OF_DIPYDOCS
constexpr static const char* DEMODIPYDOCS__SOURCE_SITE = "http://94.23.197.37/dipylon/freedipydocs/%1/mp3";
#else
constexpr static const char* DEMODIPYDOCS__SOURCE_SITE = "http://94.23.197.37/dipylon/freedipydocs/%1/ogg";
#endif

// regex used to detect 'demo' dipydocs's names :
constexpr static const char* DEMODIPYDOCS__REGEX_FOR_DIRECTORIES_NAME = "_demo_*";
// name of the summary file :
constexpr static const char* DEMODIPYDOCS__SUMMARY_FILENAME = "summary";
// separatator characters in the summary file :
constexpr static const char* DEMODIPYDOCS__SUMMARY_SEP = " :: ";
}
#endif
