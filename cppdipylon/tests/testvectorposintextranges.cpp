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

    ❏Dipylon❏ : tests/testvectorposintextranges.cpp

    ⇨ tests for VectorPosInTextRanges objects.

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

#include "testvectorposintextranges.h"

/*
  A normal VectorPosInTextRanges object is created :
*/
void TestVectorPosInTextRanges::test0(void)
{
  VectorPosInTextRanges vposintextranges = \
    VectorPosInTextRanges( std::vector<PosInTextRanges>( { PosInTextRanges( { {10,20}, {150,250} } ),
                                                           PosInTextRanges( { {50,70}, {190,191} } ),
                                                       }));

  QCOMPARE( vposintextranges.size() == 2 , true );
  QCOMPARE( vposintextranges.repr(), QString("10-20+150-250/50-70+190-191"));
}

/*
  An empty VectorPosInTextRanges object is created :
*/
void TestVectorPosInTextRanges::test1(void)
{
  VectorPosInTextRanges vposintextranges = VectorPosInTextRanges( std::vector<PosInTextRanges>() );

  QCOMPARE( vposintextranges.size() == 0 , true );
  QCOMPARE( vposintextranges.repr(), QString(""));
}

/*
  test of the sort functor.
*/
void TestVectorPosInTextRanges::test2(void)
{
  VectorPosInTextRanges vposintextranges = \
    VectorPosInTextRanges( std::vector<PosInTextRanges>( { PosInTextRanges( { {10,20}, {150,250} } ),
                                                           PosInTextRanges( { {0,5}, {11, 20} } ),
                                                           PosInTextRanges( { {8, 9}, {91,92} } ),
                                                           PosInTextRanges( { {1, 2}, {190,191} } ),
                                                           PosInTextRanges( { {0,5}, {10, 20} } ),
                                                       }));
  vposintextranges.sort();

  QCOMPARE( vposintextranges.size() == 5 , true );
  QCOMPARE( vposintextranges.repr(), QString("0-5+10-20/0-5+11-20/1-2+190-191/8-9+91-92/10-20+150-250"));
}

/*
  test of the toPosInTextRanges()
*/
void TestVectorPosInTextRanges::test3(void)
{
  // no error, simple VectorPosInTextRanges transformed into PosInTextRanges :
  VectorPosInTextRanges vposintextranges = \
    VectorPosInTextRanges( std::vector<PosInTextRanges>( { PosInTextRanges( { {10,20}, {150,250} } ),
                                                           PosInTextRanges( { {0,5}, {7, 8} } ),
                                                       }));
  vposintextranges.sort();

  PosInTextRanges posintextranges = vposintextranges.toPosInTextRanges();
  QCOMPARE( posintextranges.well_initialized() == true, true );
  QCOMPARE( posintextranges.internal_state() == PosInTextRanges::INTERNALSTATE::OK, true );
  QCOMPARE( posintextranges.size() == 4 , true );
  QCOMPARE( posintextranges.repr(), QString("0-5+7-8+10-20+150-250"));

  // error, overlapping segments :
  vposintextranges = \
    VectorPosInTextRanges( std::vector<PosInTextRanges>( { PosInTextRanges( { {10,20}, {150,250} } ),
                                                           PosInTextRanges( { {800,900}, {4, 5} } ),
                                                           PosInTextRanges( { {0,5}, {7, 8} } ),
                                                       }));
  posintextranges = vposintextranges.toPosInTextRanges();
  QCOMPARE( posintextranges.well_initialized() == false, true );
  QCOMPARE( posintextranges.internal_state() == PosInTextRanges::INTERNALSTATE::OVERLAPPING, true );
}
