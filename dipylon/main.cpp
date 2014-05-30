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

// $$$ à supprimer
#include "postxt/pos2str.h"

int main(int argv, char **args)
{
  qDebug() << "Dipylon : entry point\n";

  Pos2Str pos2str = {
      { {{ {10,20}, {30,40} },}, QString("example1")},
      { {{ {25,36}, {45,55} },}, QString("example2")},
      { {{ {59,61}, {62,63} },}, QString("example3")},
  };
  qDebug() << pos2str.internal_state();

    DipylonUI app(argv, args);

    return app.exec();
}
