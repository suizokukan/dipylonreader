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

/*______________________________________________________________________________

        PresentationScreen::PresentationScreen()

        PresentationScreen constructor.
______________________________________________________________________________*/
PresentationScreen::PresentationScreen(bool* _the_launcher_is_busy,
                                       const QPixmap & _pixmap,
                                       Qt::WindowFlags _f) : QSplashScreen(_pixmap, _f),
                                                             the_launcher_is_busy(_the_launcher_is_busy) {
  /*
    I'm not sure if this line is required or not. Let's say it's a kind of
    guardrail !
  */
  this->setAttribute(Qt::WA_DeleteOnClose, true);
}

/*______________________________________________________________________________

        PresentationScreen::hideEvent

        It's the event called when the splash screen disappears (see Qt doc.)
        The closeEvent is called after, when the qwidget has been deleted.

        When this event is catched, the object is closed and the function
        allows a new PresentationScreen to be displayed (see the the_launcher_is_busy
        attribute).
______________________________________________________________________________*/
void PresentationScreen::hideEvent(QHideEvent* e) {
  // DEBUG1 DebugMsg() << "PresentationScreen::hideEvent";
  e->accept();

  this->close();

  // let's allow another future PresentationScreen :
  *(this->the_launcher_is_busy) = false;
}

/*______________________________________________________________________________

        PSLauncher::PSLauncher

        PSLauncher constructor.
______________________________________________________________________________*/
PSLauncher::PSLauncher(void) : presentation_screen(nullptr), busy(false) {
}

/*______________________________________________________________________________

        PSLauncher::launch
______________________________________________________________________________*/
void PSLauncher::launch(const QString& text, const QRect& parent_geometry) {
  // problem : a PresentationScreen object already exists :
  if (this->busy == true) {
    // DEBUG1 DebugMsg() << "PSLauncher::display_a_presentation_screen() : a PresentationScreen object already exists.";
    return;
  }

  // normal case : let's display a new PresentationScreen object :
  this->busy = true;

  this->presentation_screen = new PresentationScreen(&(this->busy),
                                                     QPixmap(":/resources/images/splashscreen/splashscreen.png"),
                                                     Qt::WindowStaysOnTopHint);

  // let's center the splashscreen exactly with the main window :
  int parent_x = parent_geometry.x();
  int parent_y = parent_geometry.y();
  int parent_width = parent_geometry.width();
  int parent_height = parent_geometry.height();
  this->presentation_screen->move(parent_x + (parent_width / 2)  - (this->presentation_screen->width() / 2),
                                  parent_y + (parent_height / 2) - (this->presentation_screen->height() / 2));

  this->presentation_screen->showMessage(text, Qt::AlignLeft);

  this->presentation_screen->show();

  QTimer::singleShot(fixedparameters::splashscreen_maximal_duration,
                     this->presentation_screen, SLOT(close()));
}
