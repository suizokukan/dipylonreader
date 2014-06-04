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
#include "posintxt/posranges.h"
#include "posintxt/vectorposranges.h"
#include <QDebug>

/*______________________________________________________________________________

  Main entry point.

  See http://qt-project.org/doc/qt-5/qapplication.html#QApplication about "argc"
  and "argv".
______________________________________________________________________________*/
int main(int argc, char **argv)
{
    Q_INIT_RESOURCE(dipylon);

    // $$$
    PosRanges p1 = PosRanges();
    PosRanges p2 = PosRanges("94-107+98-109");
    qDebug() << p2.to_str();
    qDebug() << p2.contains(95);
    qDebug() << p2.contains(95,109);
    qDebug() << p2.size();
    PosRanges p3 = PosRanges("94-107+97-109");
    qDebug() << (p2 == p3);
    qDebug() << (p2 != p3);

    VectorPosRanges v1 = \
    VectorPosRanges(  { PosRanges( { {10,20}, {150,250} } ),
                                               PosRanges( { {0,5}, {11, 20} } ),
                                               PosRanges( { {8, 9}, {91,92} } ),
                                               PosRanges( { {1, 2}, {190,191} } ),
                                               PosRanges( { {0,5}, {10, 20} } ),
          });
    qDebug() << v1.to_str();
    v1.sort();
    qDebug() << v1.to_str();
    qDebug() << v1.size(); 


    DipylonUI myapp(argc, argv);
    return myapp.go();
}
