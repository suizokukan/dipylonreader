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

    ❏Dipylon❏ : main.cpp

*******************************************************************************/

#include "qt/dipylonui.h"

#include <QApplication>

//$$$
#include "pos/posinaudio2posintext.h"
#include "pos/posintext/posintextranges.h"
#include "pos/posintext/vectorposintextranges.h"
#include "pos/posintext2posinaudio.h"
#include "languages/languagefromto.h"
#include <QDebug>
#include <vector>

/*______________________________________________________________________________

  Main entry point.

  See http://qt-project.org/doc/qt-5/qapplication.html#QApplication about "argc"
  and "argv".
______________________________________________________________________________*/
int main(int argc, char **argv)
{
    Q_INIT_RESOURCE(dipylon);

    DipylonUI myapp = DipylonUI(argc, argv);
    int resvalue = myapp.go();

    return resvalue;
}
