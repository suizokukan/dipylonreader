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

#include "qt/mainwindow.h"
#include "qt/parameters.h"
#include "dipydoc/dipydoc.h"

#include <QApplication>
#include <QString>
#include <QTranslator>

/*______________________________________________________________________________

  DipylonUI class : a wrapper around the QApplication object.
________________________________________________________________________________*/
class DipylonUI {

private:
  // attributes used to initialize the QApplication constructor :
  int cmdline_argc = 0;
  char** cmdline_argv = nullptr;

  // current document displayed in the source zone :
  DipyDoc* current_dipydoc = nullptr;

  /* 
        data used to initialize the QApplication object.

        see http://qt-project.org/doc/qt-5/qcoreapplication.html
  */
  const QString organization_name   = QString("suizokukan's factory");
  const QString organization_domain = QString("94.23.197.37");
  const QString application_name    = QString("Dipylon");
  const QString application_version = QString("0.1.9");
  const QString application_style   = QString("CleanLooks");

public:
      DipylonUI(int argc, char **argv);
      ~DipylonUI(void);
  int go(void);
};

#endif
