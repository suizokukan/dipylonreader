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

    ❏DipylonReader❏ : qt/presentationscreen.cpp

    See presentationscreen.h for the documentation.

*******************************************************************************/

#include "qt/presentationscreen.h"

PresentationScreen::PresentationScreen(PSLauncher* _pslauncher,
         const QPixmap & _pixmap,
         Qt::WindowFlags _f) : QSplashScreen::QSplashScreen(_pixmap, _f), presentation_screen(_pslauncher) {
}

void PresentationScreen::hideEvent(QHideEvent* e) {
  DebugMsg() << "PresentationScreen::hideEvent";
  e->accept();

  this->close();

  presentation_screen->busy = false;
}

PSLauncher::PSLauncher(void) : splashscreen(nullptr), busy(false) {
}

PSLauncher::~PSLauncher(void) {
}

void PSLauncher::launch(const QString& text, const QRect& parent_geometry) {
  if (this->busy == true) {
    DebugMsg() << "PSLauncher::display_a_presentation_screen() : error #1";
    return;
  }

  this->busy = true;

  this->splashscreen = new PresentationScreen(this,
                                              QPixmap(":/ressources/images/splashscreen/splashscreen.png"),
                                              Qt::WindowStaysOnTopHint);

  // let's center the splashscreen exactly with the main window :
  int parent_x = parent_geometry.x();
  int parent_y = parent_geometry.y();
  int parent_width = parent_geometry.width();
  int parent_height = parent_geometry.height();
  this->splashscreen->move(parent_x + (parent_width / 2)  - (this->splashscreen->width() / 2),
                           parent_y + (parent_height / 2) - (this->splashscreen->height() / 2));

  this->splashscreen->showMessage(text, Qt::AlignLeft);

  this->splashscreen->show();

  QTimer::singleShot(fixedparameters::splashscreen_maximal_duration,
                     splashscreen, SLOT(close()));
}
