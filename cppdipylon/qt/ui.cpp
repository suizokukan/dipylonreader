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

    ❏DipylonReader❏ : qt/ui.cpp

    See ui.h for the documentation.

*******************************************************************************/

#include "qt/ui.h"

/*______________________________________________________________________________

  UI constructor : the real initialization is the go() method.

  See http://qt-project.org/doc/qt-5/qapplication.html#QApplication about
  "argc" and "argv".
______________________________________________________________________________*/
UI::UI(void) {
  // DEBUG1 DebugMsg() << "UI::UI() : entry point";
  // DEBUG1 DebugMsg() << "Qt version : " << QT_VERSION_STR;

  /*
     initialization of this->path_info :

     if it's possible, this attribute takes the value stored in fixedparameters::default_path_to_dipydocs :
  */
  // DEBUG1 DebugMsg() << "initialization of this->path_info :";
  QFileInfo path_info = QFileInfo(fixedparameters::default__path_to_dipydocs);
  if (path_info.exists() == false || path_info.isFile()) {
    /*
      Let's try to create the expected directory :
    */
    QDir new_d = path_info.dir();
    if (new_d.mkpath(new_d.absolutePath()) == false) {
      /*
        problem with the default value, the program has to use the current directory :
      */
      this->path_to_dipydocs = ".";

      // DEBUG1 DebugMsg() << "(can't create the expected folder). "
      // DEBUG1            << "Problem with the default path stored in fixedparameters.h, using the current directory."
      // DEBUG1            << " default path = " << fixedparameters::default__path_to_dipydocs
      // DEBUG1            << " (path_info.exists()=" << path_info.exists()
      // DEBUG1            << "path_info.isFile()=" << path_info.isFile()
      // DEBUG1            << ")";
    } else {
      /*
        ok, the default path has been created : let's use it.
      */

      // DEBUG1 DebugMsg() << "initialization of this->path_info : "
      // DEBUG1               "let's use fixedparameters::default__path_to_dipydocs "
      // DEBUG1            << "which has just been created; this->path_to_dipydocs="
      // DEBUG1            << fixedparameters::default__path_to_dipydocs;
      this->path_to_dipydocs = fixedparameters::default__path_to_dipydocs;
    }
  } else {
    /*
      ok, the default path exists : let's use it.
    */

    // DEBUG1 DebugMsg() << "initialization of this->path_info : let's use fixedparameters::default__path_to_dipydocs "
    // DEBUG1            << fixedparameters::default__path_to_dipydocs;
    this->path_to_dipydocs = fixedparameters::default__path_to_dipydocs;
  }

  /*
    initialization of this->available_menu_names
  */
  this->read_menu_names();
  // DEBUG1 DebugMsg() << "this->available_menu_names =\n" << this->available_menu_names.repr();

  // DEBUG1 DebugMsg() << "UI::UI() : exit point";
}

/*______________________________________________________________________________

  UI destructor
______________________________________________________________________________*/
UI::~UI(void) {
  // DEBUG1 DebugMsg() << "UI::~UI(#beginning)";

  // QNetworkAccessManager object :
  // DEBUG1 DebugMsg() << "... delete this->network_manager";
  delete this->network_manager;

  // DEBUG1 DebugMsg() << "UI::~UI(#fin)";
}

/*______________________________________________________________________________

  UI::go() : UI creation + main loop
______________________________________________________________________________*/
int UI::go(int argc, char **argv) {
  // DEBUG1 DebugMsg() << "enter in UI::go()";

  /*
    We want to use the system's standard settings.

    see http://qt-project.org/doc/qt-5/qguiapplication.html#setDesktopSettingsAware
  */
  QApplication::setDesktopSettingsAware(true);

  /*
    general parameters :
  */
  QApplication app(argc, argv);
  app.setOrganizationName(fixedparameters::organization_name);
  app.setOrganizationDomain(fixedparameters::organization_domain);
  app.setApplicationName(fixedparameters::application_name);
  app.setApplicationVersion(fixedparameters::application_version);

  /*
    application's look :
  */
  app.setStyle(fixedparameters::application_style);

  /*
     application's icon :
  */
  app.setWindowIcon(QIcon(":/resources/images/icons/application_icon.png"));

  /* i18n :

     o Qt translations stored in system files
     o Dipylon translation stored in dipylon_XXX files.

     see http://qt-project.org/doc/qt-5/internationalization.html
  */
  QLocale local_system = QLocale::system();
  // DEBUG1 DebugMsg() << "i18n : local_system.name()=" << local_system.name();  // language_COUNTRY
  // DEBUG1 DebugMsg() << "i18n : local_system.language()=" << QLocale::languageToString(local_system.language());

  /*
     global i18n (translations written by Qt)

     This translations are loaded from the ressource files, not from the system files
     since this project uses its own qt_*.ts files.

  */
  QTranslator qtTranslator;
  QString system_translations_filename("qt_" +QLocale::languageToString(local_system.language()));
  // DEBUG1 DebugMsg() << "i18n : loading the Qt translations : " << system_translations_filename;
  if (qtTranslator.load(system_translations_filename, ":/i18n") == false) {
    // DEBUG1 DebugMsg() << "i18n : can't load the Qt translations !";
  }
  app.installTranslator(&qtTranslator);

  /*
     Dipylon-i18n (translations specific to Dipylon)

     This translations are loaded from the ressource files.
  */
  QTranslator dipylonTranslator;
  QString dipylon_translations_filename(fixedparameters::application_name + \
                                        "_" + \
                                        QLocale::languageToString(local_system.language()));
  // DEBUG1 DebugMsg() << "i18n : loading the project's translations" << dipylon_translations_filename;
  if (dipylonTranslator.load(dipylon_translations_filename, ":/i18n") == false) {
    // DEBUG1 DebugMsg() << "i18n : can't load the project's translations !";
  }
  app.installTranslator(&dipylonTranslator);

  /*
    Displaying some usefull informations
  */
  // DEBUG1 DebugMsg() << "QGuiApplication::primaryScreen()->name() =" << QGuiApplication::primaryScreen()->name();
  // DEBUG1 DebugMsg() << "QGuiApplication::primaryScreen()->size() =" << QGuiApplication::primaryScreen()->size();

  /*
    main window creation :
  */
  this->mainWin = new MainWindow(*this);

  /*
    the main window is displayed :
  */
  this->mainWin->show();

  /*
  from the doc of QCoreApplication::exec:

  | We recommend that you connect clean-up code to the aboutToQuit() signal,
  | instead of putting it in your application's main() function because on
  | some platforms the QCoreApplication::exec() call may not return. For
  | example, on Windows when the user logs off, the system terminates the
  | process after Qt closes all top-level windows. Hence, there is no guarantee
  | that the application will have time to exit its event loop and execute code at
  | the end of the main() function after the QCoreApplication::exec() call.

    see e.g. http://stackoverflow.com/questions/8165487/how-to-do-cleaning-up-on-exit-in-qt

  */
  // connection #C036 (confer documentation)
  QObject::connect(&app, &QApplication::aboutToQuit,
                   this->mainWin, &MainWindow::closing);

  /*
    we display the list of the available fonts' families :
  */
  QFontDatabase qfontdatabase;
  // DEBUG1 DebugMsg() << "list of the available fonts' families : "
  // DEBUG1            << qfontdatabase.families().join("; ");

  /*
    saved settings :
  */
  this->read_settings();

  /*
    main window maximized ?

    On Linux/X11, the ::showMaximized() method doesn't work, hence the tricks used
    above.
    see http://qt-project.org/doc/qt-5/application-windows.html#window-geometry
  */
  #ifdef ALLOW_MAXIMIZE_MAINWINDOW
  // DEBUG1 DebugMsg() << "maximize the main window";

  #ifdef MAXIMIZE_MAINWINDOW_TRUE_METHOD
  if (this->first_launch == true) {
    // DEBUG1 DebugMsg() << "... call to this->mainWin->showMaximized() .";
    this->mainWin->showMaximized();
  }
  #endif

  #ifdef MAXIMIZE_MAINWINDOW_LINUXDESKTOPX11_METHOD
  if (this->first_launch == true) {
    // Since the ::showMaximized() method doesn't work on X11,
    // let's resize and move the main window "artistically" :

    // DEBUG1 DebugMsg() << "... using a specific way to X11 platforms to maximize the main window.";
    QSize size = QGuiApplication::primaryScreen()->size();
    size.setWidth(size.width() / 2);
    size.setHeight(size.height() / 2);
    this->mainWin->move((size.width() / 2), (size.height() / 2));
    this->mainWin->resize(size);
  }
  #endif

  #endif

  /*
    splash screen
  */
  #ifdef ALLOW_SPLASHSCREEN_AT_START
  if (this->first_launch == true || this->display_splashscreen == true) {
    // message displayed on the presentation screen :
    QString msg(QString("<span style=\"color:#000000\">") + \
                QObject::tr("<b>%1</b> - version %2 -"));

    this->presentation_screen_launcher.launch(msg.arg(fixedparameters::application_name_for_the_user,
                                                      fixedparameters::application_version),
                                              this->mainWin->geometry());
  }
  #endif

  /*
    Is there a dipydoc to load on the command line ?
  */
  #ifdef ALLOW_LOADING_DIPYDOC_FROM_THE_COMMAND_LINE
  QStringList args = QCoreApplication::arguments();
  // args.at(0) si nothing but the name of the application : we start with 1.
  for (int i = 1; i < args.size(); i++) {
    if (i + 1 != argc) {
      if (args.at(i) == "--load") {
        // let's open what lies in args.at(i+1), after the "--load" parameter :
        this->mainWin->loadDipyDoc(args.at(i+1));
      }
    }
  }
  #endif

  /*
    main loop :
  */
  return app.exec();
}

/*______________________________________________________________________________

  UI::read_menu_names

  Initialize this->available_menu_names.
______________________________________________________________________________*/
void UI::read_menu_names(void) {
  this->available_menu_names = MenuNames(this->path_to_dipydocs);
}


/*______________________________________________________________________________

  UI::read_settings() : read the settings and initialize the application's
                        parameters
______________________________________________________________________________*/
void UI::read_settings(void) {
  /*
    By calling QSettings::setting() without any parameter, we initialize settings
    with :
        o QCoreApplication::organizationName
        o QCoreApplication::organizationDomain,
        o QCoreApplication::applicationName
        ... all previously defined (see ui.cpp)

    (see http://qt-project.org/doc/qt-5/QSettings.html)
  */
  QSettings settings;
  // DEBUG1 DebugMsg() << "UI::read_settings() from " << settings.fileName();

  /*
    first launch ?
  */
  this->first_launch = !settings.contains("application/firstlaunch");
  // DEBUG1 DebugMsg() << "first_launch= " << this->first_launch;

  /*
    we read the settings only if there are settings to be read :
  */
  if (this->first_launch == false) {
    /*
      main window's geometry :
    */
    #ifdef ALLOW_RESIZING_AND_MOVING_THE_MAINWINDOW
    this->mainWin->restoreGeometry(settings.value("mainwindow/geometry").toByteArray());
    #endif

    if (settings.value("mainwindow/fullscreen") == true) {
      // DEBUG1 DebugMsg() << "call to this->mainWin->showFullScreen()";
      this->mainWin->showFullScreen();
    }

    /*
      display splashscreen ?
    */
    this->display_splashscreen = settings.value("application/displaysplashscreen") == true;

    /*
      visible toolbars ?
    */
    this->mainWin->visible_toolbars = settings.value("mainwindow/visible_toolbars") == true;
  }
}

/*______________________________________________________________________________

  UI::write_settings() : write the settings
______________________________________________________________________________*/
void UI::write_settings(void) {
  /*
    By calling QSettings::setting() without any parameter, we initialize settings
    with :
        o QCoreApplication::organizationName
        o QCoreApplication::organizationDomain,
        o QCoreApplication::applicationName
        ... all previously defined (see ui.cpp)

    (see http://qt-project.org/doc/qt-5/QSettings.html)
  */
  QSettings settings;
  // DEBUG1 DebugMsg() << "UI::write_settings() to " << settings.fileName();

  /*
    If 'application/firstlaunch' is defined, it means that the program
    has been launched, hence the boolean value set to 'false'.
  */
  settings.setValue("application/firstlaunch", false);

  #ifdef ALLOW_RESIZING_AND_MOVING_THE_MAINWINDOW
  settings.setValue("mainwindow/geometry", this->mainWin->saveGeometry());
  #endif

  settings.setValue("mainwindow/fullscreen", this->mainWin->isFullScreen());

  /*
    display splashscreen ?
  */
  settings.setValue("application/displaysplashscreen", this->display_splashscreen);

  /*
    visible toolbars ?
  */
  settings.setValue("mainwindow/visible_toolbars", this->mainWin->visible_toolbars);
}
