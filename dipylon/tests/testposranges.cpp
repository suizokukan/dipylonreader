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

    ❏Dipylon❏ : tests/testposranges.cpp

    ⇨ tests for PosRanges objects.

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

#include "testposranges.h"

/*
  A PosRanges object is created from a normal string with two adjacent characters.
*/
void TestPosRanges::test0(void)
{ 
  const QString& str = QString("0…1+1…2");
  PosRanges g(str);

  QCOMPARE( g.well_initialized() , true );
  QCOMPARE( g.internal_state() , g.INTERNALSTATE_OK );
  QCOMPARE( g.size() , (std::size_t)2 );
  QCOMPARE( g.to_str(), str );
}

/*
  A PosRanges object is created from a normal string.
*/
void TestPosRanges::test1(void)
{ 
  const QString& str = QString("94…98+99…100+101…105+123…125");
  PosRanges g(str);

  QCOMPARE( g.well_initialized() ,true );
  QCOMPARE( g.internal_state() , g.INTERNALSTATE_OK );
  QCOMPARE( g.size() , (std::size_t)4 );
  QCOMPARE( g.to_str(), str );

  QCOMPARE( g.is_inside(0) , false );
  QCOMPARE( g.is_inside(97) , true );
  QCOMPARE( g.is_inside(98) , true );
  QCOMPARE( g.is_inside(122) , false );
  QCOMPARE( g.is_inside(123) , true );
  QCOMPARE( g.is_inside(125) , true );
  QCOMPARE( g.is_inside(126) , false );
}

/*
  A PosRanges object is created from a normal string with spaces
*/
void TestPosRanges::test2(void)
{ 
  const QString& str = QString("  94… 95 +   97  …  98 +  101 …  105  ");
  PosRanges g(str);
  QCOMPARE( g.to_str(), QString("94…95+97…98+101…105") );

  QCOMPARE( g.well_initialized() , true );
  QCOMPARE( g.internal_state() , g.INTERNALSTATE_OK );
  QCOMPARE( g.size() , (std::size_t)3 );

  QCOMPARE( g.is_inside(0) , false );
  QCOMPARE( g.is_inside(94) , true );
  QCOMPARE( g.is_inside(95) , true );
  QCOMPARE( g.is_inside(96) , false );
  QCOMPARE( g.is_inside(105) , true );
  QCOMPARE( g.is_inside(106) , false );
}

/*
  A PosRanges object is created from an empty string -> error.
*/
void TestPosRanges::test3(void)
{ 
  const QString& str = QString("");
  PosRanges g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , g.INTERNALSTATE_EMPTY );
}

/*
  A PosRanges object is created from a ill-formed string -> error
*/
void TestPosRanges::test4a(void)
{ 
  const QString& str = QString("49…");
  PosRanges g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , g.INTERNALSTATE_X0X1 );
}

/*
  A PosRanges object is created from a ill-formed string -> error
*/
void TestPosRanges::test4b(void)
{ 
  const QString& str = QString("49…89+145");
  PosRanges g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , g.INTERNALSTATE_SECONDSEP );
}

/*
  A PosRanges object is created from a ill-formed string (x0,x1) -> error
*/
void TestPosRanges::test4c(void)
{ 
  const QString& str = QString("49…89+144…144");
  PosRanges g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , g.INTERNALSTATE_X0X1 );
}

/*
  A PosRanges object is created from a ill-formed string (x0>x1) -> error
*/
void TestPosRanges::test4d(void)
{ 
  const QString& str = QString("49…89+144…143");
  PosRanges g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , g.INTERNALSTATE_X0X1 );
}

/*
  A PosRanges object is created with overlapping posranges -> error
*/
void TestPosRanges::test5a(void)
{ 
  const QString& str = QString("49…89+50…150");
  PosRanges g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , g.INTERNALSTATE_OVERLAPPING );
}

/*
  A PosRanges object is created with overlapping posranges -> error
*/
void TestPosRanges::test5b(void)
{ 
  const QString& str = QString("49…89+95…150+3…50");
  PosRanges g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , g.INTERNALSTATE_OVERLAPPING );
}

/*
  testing the , operator with two equivalent PosRanges objects
*/
void TestPosRanges::test6a(void)
{ 
  const QString& str1 = QString("  94… 95 +   97  …  98 +  101 …  105  ");
  PosRanges g1(str1);
  const QString& str2 = QString("94…95+97…98+101…105");
  PosRanges g2(str2);

  QCOMPARE( g1 , g2 );
}

/*
  testing the != operator with two equivalent PosRanges objects
*/
void TestPosRanges::test6b(void)
{ 
  const QString& str1 = QString("  94… 95 +   97  …  98 +  101 …  105  ");
  PosRanges g1(str1);
  const QString& str2 = QString("94…95+97…98+101…106");
  PosRanges g2(str2);

  QVERIFY( g1 != g2 );
}

/*
  a PosRanges object is created from a list of pair of integers, no problem.
*/
void TestPosRanges::test7a(void)
{ 
  PosRanges g( { {1,2}, {4,5}, {10,11}, {99,101} } );
  QCOMPARE( g.well_initialized() , true );
  QCOMPARE( g.internal_state() , g.INTERNALSTATE_OK );
  QCOMPARE( g.size() , (std::size_t)4 );
}

/*
  a PosRanges object is created from an empty list of pair of integers -> error
*/
void TestPosRanges::test7b(void)
{ 
  PosRanges g( {} );
  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , g.INTERNALSTATE_EMPTY );
}

/*
  a PosRanges object is created from a wrong list of pair of integers -> error
*/
void TestPosRanges::test7c(void)
{ 
  PosRanges g( { {10,20}, {15,25} } );
  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , g.INTERNALSTATE_OVERLAPPING );
}

/*
  a PosRanges object is created from a wrong list of pair of integers -> error
*/
void TestPosRanges::test7d(void)
{ 
  PosRanges g( { {20,10}, {150,250} } );
  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , g.INTERNALSTATE_X0X1 );
}

/*
  test of is_inside() functions : is_inside(x0)
*/
void TestPosRanges::test8a(void)
{ 
  const QString& str = QString("94…98+99…100+101…105+123…125");
  PosRanges g(str);

  QCOMPARE( g.is_inside(93) , false );
  QCOMPARE( g.is_inside(94) , true );
  QCOMPARE( g.is_inside(98) , true );
  QCOMPARE( g.is_inside(99) , true );
  QCOMPARE( g.is_inside(125) , true );
  QCOMPARE( g.is_inside(126) , false );
}

/*
  test of is_inside() functions : is_inside(x0, x1)
*/
void TestPosRanges::test8b(void)
{ 
  const QString& str = QString("94…98+99…100+101…105+123…125");
  PosRanges g(str);

  QCOMPARE( g.is_inside(122, 130) , true );
  QCOMPARE( g.is_inside(123, 125) , true );
  QCOMPARE( g.is_inside(110, 125) , true );
  QCOMPARE( g.is_inside(123, 130) , true );
  QCOMPARE( g.is_inside(126, 131) , false );
  QCOMPARE( g.is_inside(104, 106) , true );
}

