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

    ❏Dipylon❏ : tests/testvectorposranges.cpp

    ⇨ tests for VectorPosRanges objects.

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

#include "testvectorposranges.h"

/*
  A normal VectorPosRanges object is created :
*/
void TestVectorPosRanges::test0(void)
{ 
  VectorPosRanges vposranges = \
    VectorPosRanges( std::vector<PosRanges>( { PosRanges( { {10,20}, {150,250} } ),
                                               PosRanges( { {50,70}, {190,191} } ),
                                             }));

  QCOMPARE(vposranges.size(), (std::size_t)2 );
  QCOMPARE(vposranges.to_str(), QString("10-20+150-250/50-70+190-191"));
}

/*
  An empty VectorPosRanges object is created :
*/
void TestVectorPosRanges::test1(void)
{ 
  VectorPosRanges vposranges = VectorPosRanges( std::vector<PosRanges>() );

  QCOMPARE(vposranges.size(), (std::size_t)0 );
  QCOMPARE(vposranges.to_str(), QString(""));
}

/*
  test of the sort functor.
*/
void TestVectorPosRanges::test2(void)
{ 
  VectorPosRanges vposranges = \
    VectorPosRanges( std::vector<PosRanges>( { PosRanges( { {10,20}, {150,250} } ),
                                               PosRanges( { {0,5}, {11, 20} } ),
                                               PosRanges( { {8, 9}, {91,92} } ),
                                               PosRanges( { {1, 2}, {190,191} } ),
                                               PosRanges( { {0,5}, {10, 20} } ),
                                             }));
  vposranges.sort();

  QCOMPARE(vposranges.size(), (std::size_t)5 );
  QCOMPARE(vposranges.to_str(), QString("0-5+10-20/0-5+11-20/1-2+190-191/8-9+91-92/10-20+150-250"));
}
