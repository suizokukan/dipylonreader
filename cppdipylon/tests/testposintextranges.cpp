/*******************************************************************************

    DipylonReader Copyright (C) 2008 Xavier Faure
    Contact: faure dot epistulam dot mihi dot scripsisti at orange dot fr

    This file is part of DipylonReader.
    DipylonReader is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    DipylonReader is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with DipylonReader.  If not, see <http://www.gnu.org/licenses/>.

    ____________________________________________________________________________

    ❏DipylonReader❏ : tests/testposintextranges.cpp

    ⇨ tests for PosInTextRanges objects.

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

#include "testposintextranges.h"

/*
  A PosInTextRanges object is created from a normal string with two adjacent characters.
*/
void TestPosInTextRanges::test0(void)
{
  const QString& str = QString("0-1+1-2");
  PosInTextRanges g(str);

  QCOMPARE( g.well_initialized() , true );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInTextRanges::INTERNALSTATE::OK) );
  QCOMPARE( g.size() == 2 , true );
  QCOMPARE( g.repr(), str );
}

/*
  A PosInTextRanges object is created from a normal string.
*/
void TestPosInTextRanges::test1(void)
{
  const QString& str = QString("94-98+99-100+101-105+123-125");
  PosInTextRanges g(str);

  QCOMPARE( g.well_initialized() ,true );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInTextRanges::INTERNALSTATE::OK) );
  QCOMPARE( g.size() == 4 , true );
  QCOMPARE( g.repr(), str );

  QCOMPARE( g.contains(0) , false );
  QCOMPARE( g.contains(97) , true );
  QCOMPARE( g.contains(98) , true );
  QCOMPARE( g.contains(122) , false );
  QCOMPARE( g.contains(123) , true );
  QCOMPARE( g.contains(125) , true );
  QCOMPARE( g.contains(126) , false );
}

/*
  A PosInTextRanges object is created from a normal string with spaces
*/
void TestPosInTextRanges::test2(void)
{
  const QString& str = QString("  94- 95 +   97  -  98 +  101 -  105  ");
  PosInTextRanges g(str);
  QCOMPARE( g.repr(), QString("94-95+97-98+101-105") );

  QCOMPARE( g.well_initialized() , true );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInTextRanges::INTERNALSTATE::OK) );
  QCOMPARE( g.size() == 3 , true );

  QCOMPARE( g.contains(0) , false );
  QCOMPARE( g.contains(94) , true );
  QCOMPARE( g.contains(95) , true );
  QCOMPARE( g.contains(96) , false );
  QCOMPARE( g.contains(105) , true );
  QCOMPARE( g.contains(106) , false );
}

/*
  A PosInTextRanges object is created from an empty string -> error.
*/
void TestPosInTextRanges::test3(void)
{
  const QString& str = QString("");
  PosInTextRanges g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInTextRanges::INTERNALSTATE::EMPTY) );
}

/*
  A PosInTextRanges object is created from a ill-formed string -> error
*/
void TestPosInTextRanges::test4a(void)
{
  const QString& str = QString("49-");
  PosInTextRanges g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInTextRanges::INTERNALSTATE::EMPTY_STRING_FOR_NUMBER) );
}

/*
  A PosInTextRanges object is created from a ill-formed string -> error
*/
void TestPosInTextRanges::test4b(void)
{
  const QString& str = QString("-49");
  PosInTextRanges g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInTextRanges::INTERNALSTATE::EMPTY_STRING_FOR_NUMBER) );
}

/*
  A PosInTextRanges object is created from a ill-formed string -> error
*/
void TestPosInTextRanges::test4c(void)
{
  const QString& str = QString("49-89+145");
  PosInTextRanges g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInTextRanges::INTERNALSTATE::PROBLEM_WITH_SECOND_SEPARATOR) );
}

/*
  A PosInTextRanges object is created from a ill-formed string (x0==x1) -> error
*/
void TestPosInTextRanges::test4d(void)
{
  const QString& str = QString("49-89+144-144");
  PosInTextRanges g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInTextRanges::INTERNALSTATE::X0X1) );
}

/*
  A PosInTextRanges object is created from a ill-formed string (x0>x1) -> error
*/
void TestPosInTextRanges::test4e(void)
{
  const QString& str = QString("49-89+144-143");
  PosInTextRanges g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInTextRanges::INTERNALSTATE::X0X1) );
}

/*
  A PosInTextRanges object is created with overlapping posintextranges -> error
*/
void TestPosInTextRanges::test5a(void)
{
  const QString& str = QString("49-89+50-150");
  PosInTextRanges g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInTextRanges::INTERNALSTATE::OVERLAPPING) );
}

/*
  A PosInTextRanges object is created with overlapping posintextranges -> error
*/
void TestPosInTextRanges::test5b(void)
{
  const QString& str = QString("49-89+95-150+3-50");
  PosInTextRanges g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInTextRanges::INTERNALSTATE::OVERLAPPING) );
}

/*
  testing the == operator with two equivalent PosInTextRanges objects
*/
void TestPosInTextRanges::test6a(void)
{
  const QString& str1 = QString("  94- 95 +   97  -  98 +  101 -  105  ");
  PosInTextRanges g1(str1);
  const QString& str2 = QString("94-95+97-98+101-105");
  PosInTextRanges g2(str2);

  QCOMPARE( g1 , g2 );
}

/*
  testing the != operator with two different PosInTextRanges objects
*/
void TestPosInTextRanges::test6b(void)
{
  const QString& str1 = QString("  94- 95 +   97  -  98 +  101 -  105  ");
  PosInTextRanges g1(str1);
  const QString& str2 = QString("94-95+97-98+101-106");
  PosInTextRanges g2(str2);

  QVERIFY( g1 != g2 );
}

/*
  a PosInTextRanges object is created from a list of pair of integers, no problem.
*/
void TestPosInTextRanges::test7a(void)
{
  PosInTextRanges g( { {1,2}, {4,5}, {10,11}, {99,101} } );
  QCOMPARE( g.well_initialized() , true );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInTextRanges::INTERNALSTATE::OK) );
  QCOMPARE( g.size() == 4 , true );
}

/*
  a PosInTextRanges object is created from an empty list of pair of integers -> error
*/
void TestPosInTextRanges::test7b(void)
{
  PosInTextRanges g( {} );
  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInTextRanges::INTERNALSTATE::EMPTY) );
}

/*
  a PosInTextRanges object is created from a wrong list of pair of integers -> error
*/
void TestPosInTextRanges::test7c(void)
{
  PosInTextRanges g( { {10,20}, {15,25} } );
  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInTextRanges::INTERNALSTATE::OVERLAPPING) );
}

/*
  a PosInTextRanges object is created from a wrong list of pair of integers -> error
*/
void TestPosInTextRanges::test7d(void)
{
  PosInTextRanges g( { {20,10}, {150,250} } );
  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInTextRanges::INTERNALSTATE::X0X1) );
}

/*
  test of contains() functions : contains(x0)
*/
void TestPosInTextRanges::test8a(void)
{
  const QString& str = QString("94-98+99-100+101-105+123-125");
  PosInTextRanges g(str);

  QCOMPARE( g.contains(93) , false );
  QCOMPARE( g.contains(94) , true );
  QCOMPARE( g.contains(98) , true );
  QCOMPARE( g.contains(99) , true );
  QCOMPARE( g.contains(125) , true );
  QCOMPARE( g.contains(126) , false );
}

/*
  test of contains() functions : contains(x0, x1)
*/
void TestPosInTextRanges::test8b(void)
{
  const QString& str = QString("94-98+99-100+101-105+123-125");
  PosInTextRanges g(str);

  QCOMPARE( g.contains(122, 130) , true );
  QCOMPARE( g.contains(123, 125) , true );
  QCOMPARE( g.contains(110, 125) , true );
  QCOMPARE( g.contains(123, 130) , true );
  QCOMPARE( g.contains(126, 131) , false );
  QCOMPARE( g.contains(104, 106) , true );
}

/*
  test of get_hash() : same objects, same hash
*/
void TestPosInTextRanges::test9a(void)
{
  PosInTextRanges g1a(QString("94-98+99-100+101-105+123-125"));
  PosInTextRanges g1b(QString("94-98+99-100+101-105+123-125"));
  QCOMPARE( g1a.get_hash() , g1b.get_hash() );

  PosInTextRanges g2a(QString(""));
  PosInTextRanges g2b(QString(""));
  QCOMPARE( g2a.get_hash() , g2b.get_hash() );

  PosInTextRanges g3a(QString("1-2"));
  PosInTextRanges g3b(QString("1-2"));
  QCOMPARE( g3a.get_hash() , g3b.get_hash() );
}

/*
  test of get_hash() : different objects, different hash
*/
void TestPosInTextRanges::test9b(void)
{
  PosInTextRanges g1a(QString("94-98+99-100+101-105+123-125"));
  PosInTextRanges g1b(QString("94-98+99-100+101-104+123-125"));
  QVERIFY( g1a.get_hash() != g1b.get_hash() );

  PosInTextRanges g2a(QString(""));
  PosInTextRanges g2b(QString("1-2"));
  QVERIFY( g2a.get_hash() != g2b.get_hash() );

  PosInTextRanges g3a(QString("1-2"));
  PosInTextRanges g3b(QString("1-3"));
  QVERIFY( g3a.get_hash() != g3b.get_hash() );
}

/*
  test of PosInTextRanges::min(), PosInTextRanges::max()
*/
void TestPosInTextRanges::test10_minmax(void)
{
  const QString& str1 = QString("99-101+49-89+144-145");
  PosInTextRanges g1(str1);
  QCOMPARE( g1.min() , static_cast<unsigned int>(49) );
  QCOMPARE( g1.max() , static_cast<unsigned int>(145) );

  const QString& str2 = QString("");
  PosInTextRanges g2(str2);
  QCOMPARE( g2.min() , static_cast<unsigned int>( MAXIMAL_POSINTEXT ) );
  QCOMPARE( g2.max() , static_cast<unsigned int>( MINIMAL_POSINTEXT ) );
}
