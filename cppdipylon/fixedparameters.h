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

/*______________________________________________________________________________

    general informations
______________________________________________________________________________*/

// code source :
const QString   CODESOURCE_ADDRESS = "http://github.com/suizokukan/dipylonreader/";
// code source's author :
const QString   CODESOURCE_AUTHOR = "Xavier Faure";
// license's name :
const QString   CODESOURCE_LICENSE = "GPLv3";
// license's address :
const QString   CODESOURCE_LICENSE_ADDRESS= "http://www.gnu.org/copyleft/gpl.html";

/*
  data used to initialize the QApplication object.

  see http://qt-project.org/doc/qt-5/qcoreapplication.html
*/
const QString organization_name   = "suizokukanfactory";
const QString organization_domain = "94.23.197.37";
const QString application_name    = "dipylonreader";
const QString application_name_for_the_user = "Dipylon-R";
// line read by build_dipylonreader_*.py : do not change its format !
const QString application_version = "0.5.0";
const QString application_style   = "CleanLooks";

/*______________________________________________________________________________

    DipyDocs
______________________________________________________________________________*/
const QStringList known_doctypes = { QString("text"), };

/*
  minimal/maximal DipyDoc's versions allowed :
*/
const int min_dipydocformat_version = 34;
const int max_dipydocformat_version = 34;

/*
   default path to the dipydocs.
*/
const QString default__path_to_dipydocs  = QDir::homePath() + "/dipydocs/";

/*
  Demonstration's Dipydocs :
*/

// source site with '%1' for the version string.
#if defined DOWNLOAD_OGG_VERSION_OF_DIPYDOCS
const QString DEMODIPYDOCS__SOURCE_SITE = "http://94.23.197.37/dipylon/freedipydocs/%1/ogg";
#elif defined DOWNLOAD_MP3_VERSION_OF_DIPYDOCS
const QString DEMODIPYDOCS__SOURCE_SITE = "http://94.23.197.37/dipylon/freedipydocs/%1/mp3";
#else
const QString DEMODIPYDOCS__SOURCE_SITE = "http://94.23.197.37/dipylon/freedipydocs/%1/ogg";
#endif

// regex used to detect 'demo' dipydocs's names :
const QString DEMODIPYDOCS__REGEX_FOR_DIRECTORIES_NAME = "_demo_*";
// name of the contact file :
const QString DEMODIPYDOCS__CONTACT_FILENAME = "contact";
// name of the summary file :
const QString DEMODIPYDOCS__SUMMARY_FILENAME = "summary";
// separatator characters in the summary file :
const QString DEMODIPYDOCS__SUMMARY_SEP = " :: ";

// name of the main file in a dipydoc directory :
const QString   DIPYDOC__MAIN_FILENAME = "main.xml";
// name of the 'menu name' file  in a dipydoc directory :
const QString   DIPYDOC__MENUNAME_FILENAME = "menuname";

/*______________________________________________________________________________

    UI : general parameters
______________________________________________________________________________*/

/*
  default__editors_size_in_main_splitter = sourceeditor / commentaryeditor size.
*/
const QList<int> default__editors_size_in_main_splitter = {{500,100}};

/*
  space between lines in source editor (100% = no space)

  there are 2 constants since a different line height may be applied
  to the text BEFORE the source text (title, introduction) and to
  the source text itself.
*/
const int default__sourceeditor__line_height__anything_but_text = 100;
const int default__sourceeditor__line_height__text = 120;

// arrows' thickness :
const int default_value_for_arrows_thickness = 2;

// default zoom value for both editors :
const int default__zoom_value = 1;

// maximum length in tab names.
const int maxlen_in_tab_name = 25;

// splash screen
const int splashscreen_maximal_duration = 9000;
const bool default__display_splashscreen = true;
// toolbars
const bool default__visible_toolbars = true;

// constant used to limit the number of items displayed in submenu 'open' :
const int maximum_number_of_items_in_submenu_open = 10;

/*
  in l-mode, when the source editor has to be scrolled down to display the
  current range of text, it may be usefull to add some characters ahead
  to be displayed :
*/
const int default__sourcezone__jump_ahead = 150;

/*______________________________________________________________________________

  UI : default style sheets and parameters
______________________________________________________________________________*/
const QString default__mainwindow_stylesheet = "";

const QString default__tabwiget_stylesheet = "background-color: #ffffcc;";

/* If fixedparameters::default__sourceeditor_verticalscrollbar_width is equal to -1,
   the default value is applied : by consequence, the function ::setMinimumWidth()
   will not be called. See the code using this const int.

   The reason explaining why this option isn't defined in default__sourceeditor_stylesheet
   and in default__commentaryeditor_stylesheet is explained in the code using this
   constant
*/
const int     default__texteditor_verticalscrollbar_width = -1;

const QString default__sourceeditor_stylesheet = "background-color: #ffffcc;"
                                                 "selection-color: white;"
                                                 "selection-background-color: blue;";

const QString default__commentaryeditor_stylesheet = "color: white;"
                                                     "background-color: #ffcc99;"
                                                     "selection-color: yellow;"
                                                     "selection-background-color: red;";

const QString default__sourcetoolbar_stylesheet = "background-color: #efebe7;";

const QString default__commentarytoolbar_stylesheet = "background-color: #efebe7;";

/*______________________________________________________________________________

  constants used by QMediaPlayer object.
______________________________________________________________________________*/
// http://qt-project.org/doc/qt-5/qmediaobject.html#notifyInterval-prop
const int default__audio_notify_interval = 500;
// http://qt-project.org/doc/qt-5/qmediaplayer.html#volume-prop
const int default__audio_player_volume = 50;
}

#endif  // CPPDIPYLON_FIXEDPARAMETERS_H_
