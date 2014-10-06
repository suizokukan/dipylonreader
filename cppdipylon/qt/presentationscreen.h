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

    ❏DipylonReader❏ : qt/presentationscreen.h

    The unique instance of the PSLauncher class allows to displays one
    splashscreen (not two or more). The QSplashScreen displayed is
    a ScreenPresentation object.

    o PSLauncher class
    o PresentationScreen class

*******************************************************************************/

#ifndef CPPDIPYLON_QT_PRESENTATIONSCREEN_H_
#define CPPDIPYLON_QT_PRESENTATIONSCREEN_H_

#include "./fixedparameters.h"
#include "debugmsg/debugmsg.h"

#include <QCloseEvent>
#include <QHideEvent>
#include <QObject>
#include <QPixmap>
#include <QRect>
#include <QSplashScreen>
#include <QString>
#include <QTimer>
#include <Qt>

class PresentationScreen;

/*______________________________________________________________________________

  PSLauncher class

  P[resentation]S[creen]Launcher

  Use this class to display("launch() method") a PresentationScreen object.
______________________________________________________________________________*/
class PSLauncher {

 public:
  // pointer to the current PresentationScreen object :
  PresentationScreen* presentation_screen = nullptr;
  // is there already a PresentationScreen object displayed ?
  bool           busy = false;

 public:
                 PSLauncher(void);
  void           launch(const QString& text, const QRect& parent_geometry);
};

/*______________________________________________________________________________

  PresentationScreen class

  A PresentationScreen is displayed through a call to PSLauncher::launch().
______________________________________________________________________________*/
class PresentationScreen : public QSplashScreen {
friend PSLauncher;

    Q_OBJECT

  // may the launcher allow to display another PresentationScreen object ?
  bool* the_launcher_is_busy = nullptr;

        PresentationScreen(bool* _the_launcher_is_busy,
                           const QPixmap & _pixmap,
                           Qt::WindowFlags _f);

private slots:
  void  hideEvent(QHideEvent*e);
};

#endif
