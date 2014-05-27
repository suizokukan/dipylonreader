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

*********************************************************************************/

#include "testposranges.h"

#include <QTest>

/*
  A PosRanges object is created from a normal string with two adjacent characters.
*/
void TestPosRanges::test0(void)
{ 
  const QString& str = QString("0…1+1…2");
  PosRanges g(str);

  QVERIFY( g.well_initialized() == true );
  QVERIFY( g.internal_state() == g.INTERNALSTATE_OK );
  QVERIFY( g.size() == 2 );
  QCOMPARE( g.to_str(), str );
}

/*
  A PosRanges object is created from a normal string.
*/
void TestPosRanges::test1(void)
{ 
  const QString& str = QString("94…98+99…100+101…105+123…125");
  PosRanges g(str);

  QVERIFY( g.well_initialized() == true );
  QVERIFY( g.internal_state() == g.INTERNALSTATE_OK );
  QVERIFY( g.size() == 4 );
  QCOMPARE( g.to_str(), str );

  QVERIFY( g.is_inside(0) == false );
  QVERIFY( g.is_inside(97) == true );
  QVERIFY( g.is_inside(98) == true );
  QVERIFY( g.is_inside(125) == true );
  QVERIFY( g.is_inside(126) == false );
}

/*
  A PosRanges object is created from a normal string with spaces
*/
void TestPosRanges::test2(void)
{ 
  const QString& str = QString("  94… 95 +   97  …  98 +  101 …  105  ");
  PosRanges g(str);
  QCOMPARE( g.to_str(), QString("94…95+97…98+101…105") );

  QVERIFY( g.well_initialized() == true );
  QVERIFY( g.internal_state() == g.INTERNALSTATE_OK );
  QVERIFY( g.size() == 3 );

  QVERIFY( g.is_inside(0) == false );
  QVERIFY( g.is_inside(94) == true );
  QVERIFY( g.is_inside(95) == true );
  QVERIFY( g.is_inside(96) == false );
  QVERIFY( g.is_inside(105) == true );
  QVERIFY( g.is_inside(106) == false );
}

/*
  A PosRanges object is created from an empty string -> error.
*/
void TestPosRanges::test3(void)
{ 
  const QString& str = QString("");
  PosRanges g(str);

  QVERIFY( g.well_initialized() == false );
  QVERIFY( g.internal_state() == g.INTERNALSTATE_EMPTY );
}

/*
  A PosRanges object is created from a ill-formed string -> error
*/
void TestPosRanges::test4a(void)
{ 
  const QString& str = QString("49…");
  PosRanges g(str);

  QVERIFY( g.well_initialized() == false );
  QVERIFY( g.internal_state() == g.INTERNALSTATE_X0X1 );
}

/*
  A PosRanges object is created from a ill-formed string -> error
*/
void TestPosRanges::test4b(void)
{ 
  const QString& str = QString("49…89+145");
  PosRanges g(str);

  QVERIFY( g.well_initialized() == false );
  QVERIFY( g.internal_state() == g.INTERNALSTATE_SECONDSEP );
}

/*
  A PosRanges object is created from a ill-formed string (x0==x1) -> error
*/
void TestPosRanges::test4c(void)
{ 
  const QString& str = QString("49…89+144…144");
  PosRanges g(str);

  QVERIFY( g.well_initialized() == false );
  QVERIFY( g.internal_state() == g.INTERNALSTATE_X0X1 );
}

/*
  A PosRanges object is created from a ill-formed string (x0>x1) -> error
*/
void TestPosRanges::test4d(void)
{ 
  const QString& str = QString("49…89+144…143");
  PosRanges g(str);

  QVERIFY( g.well_initialized() == false );
  QVERIFY( g.internal_state() == g.INTERNALSTATE_X0X1 );
}

/*
  A PosRanges object is created with overlapping posranges -> error
*/
void TestPosRanges::test5a(void)
{ 
  const QString& str = QString("49…89+50…150");
  PosRanges g(str);

  QVERIFY( g.well_initialized() == false );
  QVERIFY( g.internal_state() == g.INTERNALSTATE_OVERLAPPING );
}

/*
  A PosRanges object is created with overlapping posranges -> error
*/
void TestPosRanges::test5b(void)
{ 
  const QString& str = QString("49…89+95…150+3…50");
  PosRanges g(str);

  QVERIFY( g.well_initialized() == false );
  QVERIFY( g.internal_state() == g.INTERNALSTATE_OVERLAPPING );
}

/*
  testing the == operator with two equivalent PosRanges objects
*/
void TestPosRanges::test6a(void)
{ 
  const QString& str1 = QString("  94… 95 +   97  …  98 +  101 …  105  ");
  PosRanges g1(str1);
  const QString& str2 = QString("94…95+97…98+101…105");
  PosRanges g2(str2);

  QVERIFY( g1 == g2 );
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
  QVERIFY( g.well_initialized() == true );
  QVERIFY( g.internal_state() == g.INTERNALSTATE_OK );
  QVERIFY( g.size() == 4 );
}

/*
  a PosRanges object is created from an empty list of pair of integers -> error
*/
void TestPosRanges::test7b(void)
{ 
  PosRanges g( {} );
  QVERIFY( g.well_initialized() == false );
  QVERIFY( g.internal_state() == g.INTERNALSTATE_EMPTY );
}

/*
  a PosRanges object is created from a wrong list of pair of integers -> error
*/
void TestPosRanges::test7c(void)
{ 
  PosRanges g( { {10,20}, {15,25} } );
  QVERIFY( g.well_initialized() == false );
  QVERIFY( g.internal_state() == g.INTERNALSTATE_OVERLAPPING );
}

/*
  a PosRanges object is created from a wrong list of pair of integers -> error
*/
void TestPosRanges::test7d(void)
{ 
  PosRanges g( { {20,10}, {150,250} } );
  QVERIFY( g.well_initialized() == false );
  QVERIFY( g.internal_state() == g.INTERNALSTATE_X0X1 );
}

