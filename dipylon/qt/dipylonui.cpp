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

    ❏Dipylon❏ : qt/dipylonui.cpp

    See dipylonui.h for the documentation.

*******************************************************************************/

#include "qt/dipylonui.h"

/*______________________________________________________________________________

  DipylonUI constructor

  See http://qt-project.org/doc/qt-5/qapplication.html#QApplication about
  "argc" and "argv".  
______________________________________________________________________________*/
DipylonUI::DipylonUI(int argc, char **argv) {
  this->cmdline_argc = argc;
  this->cmdline_argv = argv;
}

/*______________________________________________________________________________

  DipylonUI::go() : UI creation + main loop
______________________________________________________________________________*/
int DipylonUI::go(void) {

  /*
    We want to use the system's standard settings.

    see http://qt-project.org/doc/qt-5/qguiapplication.html#setDesktopSettingsAware
  */
  QApplication::setDesktopSettingsAware(true);

  // general settings :
  QApplication app(this->cmdline_argc, this->cmdline_argv);
  app.setOrganizationName( this->organization_name );
  app.setOrganizationDomain( this->organization_domain );
  app.setApplicationName(this->application_name );
  app.setApplicationVersion( this->application_version );

  // application's look :
  app.setStyle( this->application_style );

  // i18n :
  QTranslator qtTranslator;
  qtTranslator.load("qt_" + QLocale::system().name(),
          QLibraryInfo::location(QLibraryInfo::TranslationsPath));
  app.installTranslator(&qtTranslator);

  QTranslator myappTranslator;
  myappTranslator.load("myapp_" + QLocale::system().name());
  app.installTranslator(&myappTranslator);

  // current DipyDoc :
  this->current_dipydoc = new DipyDoc();

  // main window creation :
  MainWindow mainWin(current_dipydoc);
  mainWin.show();

  // main loop :
  return app.exec();
}

/*______________________________________________________________________________

  DipylonUI destructor
______________________________________________________________________________*/
DipylonUI::~DipylonUI(void) {
  delete current_dipydoc;
}
