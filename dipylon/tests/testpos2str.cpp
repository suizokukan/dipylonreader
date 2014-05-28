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

    ❏Dipylon❏ : tests/testpos2str.cpp

    ⇨ tests for Pos2Str objects.

    | Beware !
    | http://stackoverflow.com/questions/14198972
    | The two arguments to the QCOMPARE macro — i.e., the two template arguments to the
    | qCompare function — must have exactly the same type. You get an error, for example,
    | if one is an int and the other is a size_t.

    | Beware !
    | http://stackoverflow.com/questions/23913298
    | QCOMPARE( (xxx), yyy ) for some objects to avoid the error message :
    |   "the macro 'QCOMPARE' got x arguments but it takes only 2"
    |
    | see http://stackoverflow.com/questions/13842468/comma-in-c-c-macro

*********************************************************************************/

#include "testpos2str.h"
#include "../pos2str.h"

#include <QTest>

/*
  A Pos2Str object is created without any error.
*/
void TestPos2Str::test0(void)
{ 
  Pos2Str pos2str = {
      { {{ {1,2}, {3,4} },}, QString("example1")},
      { {{ {1,2}, {3,5} },}, QString("example2")},
      { {{ {1,2}, {3,8} },}, QString("example3")},
  };

  QCOMPARE( pos2str.well_initialized() , true );
  QCOMPARE( pos2str.internal_state() , pos2str.INTERNALSTATE_OK );
  QCOMPARE( pos2str.size() , (std::size_t)3 );
  QCOMPARE( (pos2str[{{ {1,2}, {3,8} }}]) , QString("example3") );

  pos2str[ {{ {1,2}, {3,9} }} ] = QString("example4");

  QCOMPARE( (pos2str[{{ {1,2}, {3,9} }}]) , QString("example4") );
}

/*
  A Pos2Str object is created with an error in a PosRanges object.
*/
void TestPos2Str::test1a(void)
{ 
  Pos2Str pos2str = {
      { {{ {1,2}, {3,4} },}, QString("example1")},
      { {{ {1,2}, {5,3} },}, QString("example2")},
      { {{ {1,2}, {3,8} },}, QString("example3")},
  };

  QCOMPARE( pos2str.well_initialized() , false );
  QCOMPARE( pos2str.internal_state() , pos2str.INTERNALSTATE_WRONGPOSRANGES );
}
