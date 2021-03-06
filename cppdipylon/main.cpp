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

    ❏DipylonReader❏ : main.cpp

*******************************************************************************/

#include <QApplication>

#include "qt/ui.h"
#include "debugmsg/debugmsg.h"

/*______________________________________________________________________________

  Main entry point.

  See http://qt-project.org/doc/qt-5/qapplication.html#QApplication about "argc"
  and "argv".
______________________________________________________________________________*/
int main(int argc, char **argv) {
    // DEBUG1 DebugMsg() << "entry point; argc=" << argc << "; argv[0] =" << argv[0];

    Q_INIT_RESOURCE(dipylonreader);

    UI myapp = UI();
    int resvalue = myapp.go(argc, argv);

    return resvalue;
}
