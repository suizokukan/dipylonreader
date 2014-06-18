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

    ❏Dipylon❏ : tests/testposinpos2posintext.cpp

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

#include "testposinaudio2posintext.h"

/*
  A PosInAudio2PosInText object is created without any error.
*/
void TestPosInAudio2PosInText::test0(void) {

   PosInText2PosInAudio text2audio = {
        { {{ {1,2}, {3,4} },},  {1500, 1598} },
        { {{ {5,6}, {9,12} },},  {1750, 1790} },
        { {{ {15,16}, {19,112} },},  {1950, 1999} },
     };
   PosInAudio2PosInText audio2text = PosInAudio2PosInText(text2audio);

   QCOMPARE( audio2text.well_initialized() , true );
   QCOMPARE( audio2text.internal_state() , text2audio.INTERNALSTATE_OK );
   QCOMPARE( audio2text.size() == 3, true );
}

/*
  test of [] access
*/
void TestPosInAudio2PosInText::test1(void) {

   PosInText2PosInAudio text2audio = {
        { {{ {1,2}, {3,4} },},  {1500, 1598} },
        { {{ {5,6}, {9,12} },},  {1750, 1790} },
        { {{ {15,16}, {19,112} },},  {1950, 1999} },
     };
   PosInAudio2PosInText audio2text = PosInAudio2PosInText(text2audio);

   QCOMPARE( ((audio2text[ {1500, 1598} ].to_str())), QString("1-2+3-4") );
   QCOMPARE( ((audio2text[ {1501, 1598} ].to_str())), QString("") );
}

/*
  test of the contains() method.
*/
void TestPosInAudio2PosInText::test2(void) {

   PosInText2PosInAudio text2audio = {
        { {{ {1,2}, {3,4} },},  {1500, 1598} },
        { {{ {5,6}, {9,12} },},  {1750, 1790} },
        { {{ {15,16}, {19,112} },},  {1950, 1999} },
     };
   PosInAudio2PosInText audio2text = PosInAudio2PosInText(text2audio);

   QCOMPARE( audio2text.contains(1500).to_str(), QString("1-2+3-4") );
   QCOMPARE( audio2text.contains(1400).to_str(), QString("") );
}
