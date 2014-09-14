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
#include "debugmsg/debugmsg.h"

/*______________________________________________________________________________

  UI constructor : the real initialization is the go() method.

  See http://qt-project.org/doc/qt-5/qapplication.html#QApplication about
  "argc" and "argv".
______________________________________________________________________________*/
UI::UI(void) {
  /*
     initialization of this->path_info :

     if it's possible, this attribute takes the value stored in fixedparameters::default_path_to_dipydocs :
  */
  QFileInfo path_info = QFileInfo(fixedparameters::default__path_to_dipydocs);
  if (path_info.exists() == false || path_info.isFile()) {
    DebugMsg() << "UI::UI" \
               << "problem with the default path stored in fixedparameters.h, using the current directory." \
               << " default path = " << fixedparameters::default__path_to_dipydocs \
               << " (path_info.exists()=" << path_info.exists() \
               << "path_info.isFile()=" << path_info.isFile() \
               << ")";
    // problem with the default value, the program has to use the current directory :
    this->path_to_dipydocs = ".";
  } else {
    this->path_to_dipydocs = fixedparameters::default__path_to_dipydocs;
  }
}

/*______________________________________________________________________________

  UI destructor
______________________________________________________________________________*/
UI::~UI(void) {
  DebugMsg() << "UI::~UI(#beginning)";
  delete icon_new;
  delete icon_open;
  delete icon_save;
  delete icon_cut;
  delete icon_copy;
  delete icon_paste;
  delete icon_audio_pause;
  delete icon_audio_play;
  delete icon_audio_play_unavailable;
  delete icon_audio_stop;
  delete icon_audio_stop_unavailable;
  delete icon_readingmode_rmode;
  delete icon_readingmode_rlmode;
  delete icon_readingmode_amode;

  DebugMsg() << "UI::~UI(#fin)";
}

/*______________________________________________________________________________

  UI::at_least_one_dipydoc_has_been_loaded()
______________________________________________________________________________*/
bool UI::at_least_one_dipydoc_has_been_loaded(void) const {
  return this->current_dipydoc.well_initialized();
}

/*______________________________________________________________________________

  UI::get_translations_for() : return a QString with the translations
                                      matching the positions x0 to x1 in the
                                      source text.
______________________________________________________________________________*/
QString UI::get_translations_for(PosInText x0, PosInText x1) const {
  VectorPosInTextRanges vector_posintextranges = this->current_dipydoc.translation.translations.contains(x0, x1);

  QStringList strlist_of_translations;

  for (auto &posintextranges : vector_posintextranges) {
    strlist_of_translations.append(this->current_dipydoc.translation.translations[posintextranges]);
  }

  return strlist_of_translations.join(" ");
}

/*______________________________________________________________________________

  UI::go() : UI creation + main loop
______________________________________________________________________________*/
int UI::go(int argc, char **argv) {
  DebugMsg() << "enter in UI::go()";

  /*
    We want to use the system's standard settings.

    see http://qt-project.org/doc/qt-5/qguiapplication.html#setDesktopSettingsAware
  */
  QApplication::setDesktopSettingsAware(true);

  // general parameters :
  QApplication app(argc, argv);
  app.setOrganizationName(fixedparameters::organization_name);
  app.setOrganizationDomain(fixedparameters::organization_domain);
  app.setApplicationName(fixedparameters::application_name);
  app.setApplicationVersion(fixedparameters::application_version);

  // application's look :
  app.setStyle(fixedparameters::application_style);
  // application's icon :
  app.setWindowIcon(QIcon(":/ressources/images/icons/application_icon.png"));

  /* i18n :

     o Qt translations stored in system files
     o Dipylon translation stored in dipylon_XXX files.

     see http://qt-project.org/doc/qt-5/internationalization.html
  */
  QLocale local_system = QLocale::system();
  DebugMsg() << "i18n : local_system.name()=" << local_system.name();  // language_COUNTRY
  DebugMsg() << "i18n : local_system.language()=" << QLocale::languageToString(local_system.language());

  /*
     global i18n (translations written by Qt)

     This translations are loaded from the ressource files, not from the system files
     since this project uses its own qt_*.ts files.

  */
  QTranslator qtTranslator;
  QString system_translations_filename("qt_" +QLocale::languageToString(local_system.language()));
  bool system_translations_res = qtTranslator.load(system_translations_filename, ":/i18n");
  DebugMsg() << "i18n : loading " << system_translations_filename \
             << "success=" << system_translations_res;
  app.installTranslator(&qtTranslator);

  /*
     Dipylon-i18n (translations specific to Dipylon)

     This translations are loaded from the ressource files.
  */
  QTranslator dipylonTranslator;
  QString dipylon_translations_filename("dipylon_" + QLocale::languageToString(local_system.language()));
  bool dipylon_translations_res = dipylonTranslator.load(dipylon_translations_filename, ":/i18n");
  DebugMsg() << "i18n : loading " << dipylon_translations_filename \
             << "success=" << dipylon_translations_res;
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
  this->icon_audio_play_unavailable  = new QIcon(":ressources/images/icons/audio_play_unavailable.png");
  this->icon_audio_stop = new QIcon(":ressources/images/icons/audio_stop.png");
  this->icon_audio_stop_unavailable  = new QIcon(":ressources/images/icons/audio_stop_unavailable.png");
  this->icon_readingmode_rmode  = new QIcon(":ressources/images/icons/readingmode_rmode.png");
  this->icon_readingmode_rlmode = new QIcon(":ressources/images/icons/readingmode_rlmode.png");
  this->icon_readingmode_amode  = new QIcon(":ressources/images/icons/readingmode_amode.png");

  /*
    Displaying some usefull informations
  */
  DebugMsg() << "QGuiApplication::primaryScreen()->name() =" << QGuiApplication::primaryScreen()->name();
  DebugMsg() << "QGuiApplication::primaryScreen()->size() =" << QGuiApplication::primaryScreen()->size();

  /*
     default reading mode

     This parameter will be set again when a file will be opended. But the UI needs
     this information for the display, e.g. the icons.
  */
  this->reading_mode         = UI::READINGMODE::READINGMODE_AMODE;
  this->reading_mode_details = UI::READINGMODEDETAILS::READINGMODEDETAIL_AMODE;
  DebugMsg() << "now in AMODE mode";

  // main window creation :
  this->mainWin = new MainWindow(*this);

  /*
    main window maximized ?

    On Linux/X11, the ::showMaximized() method isn't ok, hence the tricks used
    above.
    see http://qt-project.org/doc/qt-5/application-windows.html#window-geometry
  */
  #ifdef ALLOW_MAXIMIZE_MAINWINDOW
  DebugMsg() << "maximize the main window";

  #ifdef MAXIMIZE_MAINWINDOW_TRUE_METHOD
  if (this->first_launch == true) {
    this->mainWin->showMaximized();
  }
  #endif

  #ifdef MAXIMIZE_MAINWINDOW_LINUXDESKTOPX11_METHOD
  if (this->first_launch == true) {
    /*
      Since the ::showMaximized() method doesn't work,
      let's resize and move the main window "artistically" :
    */
    QSize size = QGuiApplication::primaryScreen()->size();
    size.setWidth( size.width() / 2 );
    size.setHeight( size.height() / 2 );
    this->mainWin->move( (size.width() / 2), (size.height() / 2) );
    this->mainWin->resize(size);
  }
  #endif

  #endif

  // the main window is displayed :
  this->mainWin->show();

  /*
  from the doc of QCoreApplication::exec:

  We recommend that you connect clean-up code to the aboutToQuit() signal, instead of putting it in your application's main() function because on some platforms the QCoreApplication::exec() call may not return. For example, on Windows when the user logs off, the system terminates the process after Qt closes all top-level windows. Hence, there is no guarantee that the application will have time to exit its event loop and execute code at the end of the main() function after the QCoreApplication::exec() call.

    see e.g. http://stackoverflow.com/questions/8165487/how-to-do-cleaning-up-on-exit-in-qt

  */
  QObject::connect(&app, &QApplication::aboutToQuit,
                   this->mainWin, &MainWindow::closing);

  /*
    we display the list of the available fonts' families :
  */
  QFontDatabase qfontdatabase;
  DebugMsg() << "list of the available fonts' families : " \
             << qfontdatabase.families().join("; ");

  /*
    saved settings :
  */
  this->read_settings();

  /*
    splash screen
  */
  #ifdef ALLOW_SPLASHSCREEN
  // this variable can't be defined in the following block and must be defined here :
  QSplashScreen splashscreen(QPixmap(":/ressources/images/splashscreen/splashscreen.png"),
                             Qt::WindowStaysOnTopHint);

  if (this->first_launch == true || this->display_splashscreen == true) {
    QString msg("<span style=\"color:#000000\">" + \
                QObject::tr("<b>Δίπυλον project</b> : Dipylon Reader<br/>"
                            "- version %1 -<br/>"));

    splashscreen.showMessage(msg.arg(fixedparameters::application_version,
                             Qt::AlignLeft));

    splashscreen.show();
    QTimer::singleShot(fixedparameters::splashscreen_maximal_duration,
                       &splashscreen, SLOT(close()));
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

  // main loop :
  return app.exec();
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
  DebugMsg() << "UI::read_settings() from " << settings.fileName();

  /*
    first launch ?
  */
  this->first_launch = !settings.contains("application/firstlaunch");

  /*
    we read the settings only if there are settings to be read :
  */
  if (this->first_launch == false) {
    /*
      main window's geometry :
    */
    #ifdef ALLOW_RESIZING_THE_MAINWINDOW
    DebugMsg() << "resize main window :" << settings.value("mainwindow/size", QSize()).toSize();
    this->mainWin->resize(settings.value("mainwindow/size",
                                         QSize()).toSize());
    #endif

    #ifdef ALLOW_MOVING_THE_MAINWINDOW
    DebugMsg() << "move main window :" << settings.value("mainwindow/pos", QPoint()).toPoint();
    this->mainWin->move(settings.value("mainwindow/pos",
                                       QPoint()).toPoint());
    #endif

    if (settings.value("mainwindow/fullscreen") == true) {
      this->mainWin->showFullScreen();
    }

    /*
      display splashscreen ?
    */
    this->display_splashscreen = settings.value("application/displaysplashscreen") == true;
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
  DebugMsg() << "UI::write_settings() to " << settings.fileName();

  /*
    If 'application/firstlaunch' is defined, it means that the program
    has been launched, hence the boolean value set to 'false'.
  */
  settings.setValue("application/firstlaunch", false);

  #ifdef ALLOW_RESIZING_THE_MAINWINDOW
  settings.setValue("mainwindow/size", this->mainWin->size());
  #endif

  #ifdef ALLOW_MOVING_THE_MAINWINDOW
  settings.setValue("mainwindow/pos", this->mainWin->pos());
  #endif

  settings.setValue("mainwindow/fullscreen", this->mainWin->isFullScreen());

  /*
    display splashscreen ?
  */
  settings.setValue("application/displaysplashscreen", this->display_splashscreen);
}
