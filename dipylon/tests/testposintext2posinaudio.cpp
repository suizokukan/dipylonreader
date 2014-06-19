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

    ❏Dipylon❏ : tests/testposintext2posinaudio.cpp

    ⇨ tests for PosInText2PosInAudio objects.

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

#include "testposintext2posinaudio.h"

/*
  A PosInText2PosInAudio object is created without any error.
*/
void TestPosInText2PosInAudio::test0(void) {

   PosInText2PosInAudio text2audio = {
        { {{ {1,2}, {3,4} },},  {1500, 1598} },
        { {{ {5,6}, {9,12} },},  {1750, 1790} },
        { {{ {15,16}, {19,112} },},  {1950, 1999} },
      };

   QCOMPARE( text2audio.well_initialized() , true );
   QCOMPARE( text2audio.internal_state() , static_cast<int>(PosInText2PosInAudio::INTERNALSTATE::OK) );
   QCOMPARE( text2audio.size() == 3, true );
}

/*
  test of the [] access.
*/
void TestPosInText2PosInAudio::test1(void) {

   PosInText2PosInAudio text2audio = {
        { {{ {1,2}, {3,4} },},  {1500, 1598} },
        { {{ {5,6}, {9,12} },},  {1750, 1790} },
        { {{ {15,16}, {19,112} },},  {1950, 1999} },
      };

   QCOMPARE( (text2audio[{{ {1,2}, {3,4} },}].first), 1500 );
   QCOMPARE( (text2audio[{{ {1,2}, {3,4} },}].second), 1598 );
   QCOMPARE( (text2audio[{{ {5,6}, {9,12} },}].first), 1750 );
   QCOMPARE( (text2audio[{{ {5,6}, {9,12} },}].second), 1790 );
   QCOMPARE( (text2audio[{{ {15,16}, {19,112} },}].first), 1950 );
   QCOMPARE( (text2audio[{{ {15,16}, {19,112} },}].second), 1999 );
}

/*
  test of the contains( posinauto ) method.
*/
void TestPosInText2PosInAudio::test2(void) {

   PosInText2PosInAudio text2audio = {
        { {{ {1,2}, {3,4} },},  {1500, 1598} },
        { {{ {5,6}, {9,12} },},  {1750, 1790} },
        { {{ {15,16}, {19,112} },},  {1950, 1999} },
      };

   QCOMPARE( text2audio.contains(6).to_str(), QString("5-6+9-12") );
   QCOMPARE( text2audio.contains(13).to_str(), QString("") );
}

/*
  test of the contains( posinauto, posinauto ) method.
*/
void TestPosInText2PosInAudio::test3(void) {

   PosInText2PosInAudio text2audio = {
        { {{ {1,2}, {3,4} },},  {1500, 1598} },
        { {{ {5,6}, {9,12} },},  {1750, 1790} },
        { {{ {15,16}, {19,112} },},  {1950, 1999} },
      };

   QCOMPARE( text2audio.contains(115, 120).to_str(), QString("") );
   QCOMPARE( text2audio.contains(5, 6).to_str() , QString("5-6+9-12") );
   // we sort the result in order to avoid to get "5-6+9-12/1-2+3-4" ...
   auto res = text2audio.contains(1, 12);
   res.sort();
   QCOMPARE( res.to_str() , QString("1-2+3-4/5-6+9-12") );
}

/*
  wrong initialization (wrong PosInTextRanges)
*/
void TestPosInText2PosInAudio::test4a(void) {

   PosInText2PosInAudio text2audio = {
        { {{ {1,2}, {3,4} },},  {1500, 1598} },
        { {{ {5,6}, {12, 9} },},  {1750, 1790} },
        { {{ {15,16}, {19,112} },},  {1950, 1999} },
      };

   QCOMPARE( text2audio.well_initialized() , false );
   QCOMPARE( text2audio.internal_state() , static_cast<int>(PosInText2PosInAudio::INTERNALSTATE::BADPOSINTEXTRANGES) );
}

/*
  wrong initialization (PosInAudio X0 > X1)
*/
void TestPosInText2PosInAudio::test4b(void) {

   PosInText2PosInAudio text2audio = {
        { {{ {1,2}, {3,4} },},  {1500, 1598} },
        { {{ {5,6}, {9, 12} },},  {54321, 12345} },
        { {{ {15,16}, {19,112} },},  {1950, 1999} },
      };

   QCOMPARE( text2audio.well_initialized() , false );
   QCOMPARE( text2audio.internal_state() , static_cast<int>(PosInText2PosInAudio::INTERNALSTATE::BADPOSINAUDIOX0X1) );
}
