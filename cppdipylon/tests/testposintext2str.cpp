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

    ❏Dipylon❏ : tests/testposintext2str.cpp

    ⇨ tests for PosInText2Str objects.

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

#include "testposintext2str.h"

/*
  A PosInText2Str object is created without any error.
*/
void TestPosInText2Str::test0(void)
{
  PosInText2Str posintext2str = {
      { {{ {10,20}, {30,40} },}, QString("example1")},
      { {{ {25,36}, {45,55} },}, QString("example2")},
      { {{ {59,61}, {62,63} },}, QString("example3")},
  };

  QCOMPARE( posintext2str.well_initialized() , true );
  QCOMPARE( posintext2str.internal_state() == PosInText2Str::INTERNALSTATE::OK, true );
  QCOMPARE( posintext2str.size() == 3 , true );
  QCOMPARE( (posintext2str[{{ {59,61}, {62,63} }}]) , QString("example3") );

  posintext2str[ {{ {90,91}, {92,93} }} ] = QString("example4");

  QCOMPARE( (posintext2str[{{ {90,91}, {92,93} }}]) , QString("example4") );
}

/*
  A PosInText2Str object is created with an error in a PosInTextRanges object.
*/
void TestPosInText2Str::test1(void)
{
  PosInText2Str posintext2str = {
      { {{ {10,20}, {30,40} },}, QString("example1")},
      { {{ {25,36}, {45,55} },}, QString("example2")},
      { {{ {59,61}, {63,62} },}, QString("example3")},
  };

  QCOMPARE( posintext2str.well_initialized() , false );
  QCOMPARE( posintext2str.internal_state() , static_cast<int>(PosInText2Str::INTERNALSTATE::BAD_POS_IN_TEXTRANGES) );
}

/*
  test of PosInText2Str::contains(x0).
*/
void TestPosInText2Str::test2a(void)
{
  PosInText2Str posintext2str = {
      { {{ {1,2}, {3,4} },}, QString("example1")},
      { {{ {5,6}, {7,8} },}, QString("example2")},
      { {{ {10,11}, {12,23} },}, QString("example3")},
  };

  QCOMPARE( posintext2str.contains(1), PosInTextRanges( { {1,2}, {3,4}} ) );
  QCOMPARE( posintext2str.contains(20), PosInTextRanges( { {10,11}, {12,23}} ) );

  QCOMPARE( posintext2str.contains(100), PosInTextRanges() );
}

/*
  test of PosInText2Str::contains(x0, x1).
*/
void TestPosInText2Str::test2b(void)
{
  PosInText2Str posintext2str = {
      { {{ {5,6}, {7,8} },}, QString("example1")},
      { {{ {90,91}, {93,99} },}, QString("example2")},
      { {{ {80,81}, {83,89} },}, QString("example3")},
      { {{ {10,11}, {12,23} },}, QString("example4")},
      { {{ {1,2}, {3,4} },}, QString("example5")},
  };

  // only one PosInTextRanges expected : no need to sort.
  QCOMPARE( posintext2str.contains(24, 25).repr(),
            QString("") );
  QCOMPARE( posintext2str.contains(9, 12).repr(),
            QString("10-11+12-23") );
  QCOMPARE( posintext2str.contains(11, 12).repr(),
            QString("10-11+12-23") );
  QCOMPARE( posintext2str.contains(10, 23).repr(),
            QString("10-11+12-23") );
  QCOMPARE( posintext2str.contains(10, 25).repr(),
            QString("10-11+12-23") );

  /* the function sorts the results since the order of the PosInTextRanges elements
     in the vector isn't fixed. So, in order to compare the result, it's more
     easy to sort (=to fix the order) and then to compare.
  */
  VectorPosInTextRanges res;
  res = posintext2str.contains(1, 25);
  res.sort();
  QCOMPARE( res.repr(),
            QString("1-2+3-4/5-6+7-8/10-11+12-23") );

  res = posintext2str.contains(1, 99);
  res.sort();
  QCOMPARE( res.repr(),
            QString("1-2+3-4/5-6+7-8/10-11+12-23/80-81+83-89/90-91+93-99") );

}
