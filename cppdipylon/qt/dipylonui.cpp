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
  app.setOrganizationName( fixedparameters::organization_name );
  app.setOrganizationDomain( fixedparameters::organization_domain );
  app.setApplicationName(fixedparameters::application_name );
  app.setApplicationVersion( fixedparameters::application_version );

  // application's look :
  app.setStyle( fixedparameters::application_style );

  /* i18n :

     o Qt translations stored in system files
     o Dipylon translation stored in dipylon_XXX files.
  */
  QLocale local_system = QLocale::system();
  qDebug() << "i18n : local_system.name()=" << local_system.name();  // language_COUNTRY
  qDebug() << "i18n : local_system.language()=" << QLocale::languageToString(local_system.language());

  QTranslator qtTranslator;
  QString system_translations_filename( "qt_" + local_system.name() );
  QString system_translations_path( QLibraryInfo::location(QLibraryInfo::TranslationsPath) );
  bool system_translations_res = qtTranslator.load(system_translations_filename,
                                                   system_translations_path);
  qDebug() << "i18n : loading " << system_translations_filename << "from" << system_translations_path << "success=" << system_translations_res;
  app.installTranslator(&qtTranslator);

  QTranslator dipylonTranslator;
  QString dipylon_translations_filename("dipylon_" + QLocale::languageToString(local_system.language()));
  bool dipylon_translations_res = dipylonTranslator.load("dipylon_" + QLocale::languageToString(local_system.language()));
  qDebug() << "i18n : loading " << dipylon_translations_filename << "success=" << dipylon_translations_res;
  app.installTranslator(&dipylonTranslator);

  // creating the icons :
  this->icon_new  = new QIcon(":ressources/images/icons/new.png");
  this->icon_open = new QIcon(":ressources/images/icons/open.png");
  this->icon_save = new QIcon(":ressources/images/icons/save.png");
  this->icon_cut  = new QIcon(":ressources/images/icons/cut.png");
  this->icon_copy = new QIcon(":ressources/images/icons/copy.png");
  this->icon_paste = new QIcon(":ressources/images/icons/paste.png");
  this->icon_audio_pause = new QIcon(":ressources/images/icons/audio_pause.png");
  this->icon_audio_play  = new QIcon(":ressources/images/icons/audio_play.png");
  this->icon_audio_stop = new QIcon(":ressources/images/icons/audio_stop.png");

  // current DipyDoc :
  // $$$ fake initialization :
  QString path = QString("../texts/Ovid_M_I_452_465/");
  this->current_dipydoc = DipyDoc( path );

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

  delete icon_new;
  delete icon_open;
  delete icon_save;
  delete icon_cut;
  delete icon_copy;
  delete icon_paste;
  delete icon_audio_pause;
  delete icon_audio_play;
  delete icon_audio_stop;
}