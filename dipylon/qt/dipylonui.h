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

    ❏Dipylon❏ : qt/dipylonui.h

    Definition of the "user interface".

*******************************************************************************/

#ifndef DIPYLONUI_H
#define DIPYLONUI_H

#include "fixedparameters.h"
#include "qt/mainwindow.h"
#include "dipydoc/dipydoc.h"

#include <QApplication>
#include <QString>
#include <QTranslator>

/*
  reading modes
*/
typedef unsigned int ReadingMode;
enum ReadingModes : ReadingMode {
  undefined = 0,
  karaoke = 1,
};

/*______________________________________________________________________________

  DipylonUI class : a wrapper around the QApplication object.
________________________________________________________________________________*/
class DipylonUI {

friend class MainWindow;

private:
  // attributes used to initialize the QApplication constructor :
  int         cmdline_argc = 0;
  char**      cmdline_argv = nullptr;

  ReadingMode _reading_mode = ReadingModes::undefined;

  // current document displayed in the source zone :
  DipyDoc     current_dipydoc = DipyDoc();

public:
              DipylonUI(int argc, char **argv);
              ~DipylonUI(void);
  int         go(void);
  ReadingMode reading_mode(void);

};

inline ReadingMode DipylonUI::reading_mode(void) {
  return this->_reading_mode;
}

#endif
