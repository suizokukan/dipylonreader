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

    o PSLauncher class

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

/*______________________________________________________________________________

______________________________________________________________________________*/
class PSLauncher {

 public:
  QSplashScreen* splashscreen = nullptr;
  bool           busy = false;

 public:
                 PSLauncher(void);
                ~PSLauncher(void);
  void           launch(const QString& text, const QRect& parent_geometry);
};

class PresentationScreen : public QSplashScreen {
friend PSLauncher;

    Q_OBJECT

  PSLauncher* presentation_screen = nullptr;
  PresentationScreen(PSLauncher* _presentation_screen, const QPixmap & pixmap, Qt::WindowFlags f);

private slots:
  void hideEvent(QHideEvent*e);
};

#endif
