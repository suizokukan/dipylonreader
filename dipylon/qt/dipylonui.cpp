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
  QApplication app( this->cmdline_argc, this->cmdline_argv);
  app.setOrganizationName( parameters::organization_name );
  app.setOrganizationDomain( parameters::organization_domain );
  app.setApplicationName(parameters::application_name );
  app.setApplicationVersion( parameters::application_version );

  // application's look :
  app.setStyle( parameters::application_style );

  // i18n :
  QTranslator qtTranslator;
  qtTranslator.load("qt_" + QLocale::system().name(),
          QLibraryInfo::location(QLibraryInfo::TranslationsPath));
  app.installTranslator(&qtTranslator);

  QTranslator myappTranslator;
  myappTranslator.load("myapp_" + QLocale::system().name());
  app.installTranslator(&myappTranslator);

  // current DipyDoc :
  // $$$ fake initialization :
  this->current_dipydoc = DipyDoc("../texts/Ovid_M_I_452_465/");

  // main window creation :
  MainWindow mainWin(*this);
  mainWin.show();

  // $$$ fake initialization :
  const QString& source_text = this->current_dipydoc.source_text;
  mainWin.load_text(source_text);

  /*
  from the doc of QCoreApplication::exec:

  We recommend that you connect clean-up code to the aboutToQuit() signal, instead of putting it in your application's main() function because on some platforms the QCoreApplication::exec() call may not return. For example, on Windows when the user logs off, the system terminates the process after Qt closes all top-level windows. Hence, there is no guarantee that the application will have time to exit its event loop and execute code at the end of the main() function after the QCoreApplication::exec() call.

    see e.g. http://stackoverflow.com/questions/8165487/how-to-do-cleaning-up-on-exit-in-qt

  */
  QObject::connect(&app, SIGNAL(aboutToQuit()), &mainWin, SLOT(closing()));

  // main loop :
  return app.exec();
}

/*______________________________________________________________________________

  DipylonUI destructor
______________________________________________________________________________*/
DipylonUI::~DipylonUI(void) {
}
