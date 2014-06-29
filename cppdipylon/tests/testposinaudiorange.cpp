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

    ❏Dipylon❏ : tests/testposinaudiorange.cpp

    ⇨ tests for PosInAudioRange objects.

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

#include "testposinaudiorange.h"

/*
  A PosInAudioRange object is created from a normal string.
*/
void TestPosInAudioRange::test0(void)
{
  const QString& str = QString("0-1");
  PosInAudioRange g(str);

  QCOMPARE( g.well_initialized() , true );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInAudioRange::INTERNALSTATE::OK) );
  QCOMPARE( g.to_str(), str );
  QCOMPARE( g.first(), 0 );
  QCOMPARE( g.second(), 1 );
}

/*
  A PosInAudioRange object is created from a normal string with spaces
*/
void TestPosInAudioRange::test1(void)
{
  const QString& str = QString("  94- 95 ");
  PosInAudioRange g(str);
  QCOMPARE( g.to_str(), QString("94-95") );

  QCOMPARE( g.well_initialized() , true );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInAudioRange::INTERNALSTATE::OK) );

  QCOMPARE( g.first(), 94 );
  QCOMPARE( g.second(), 95 );
}

/*
  A PosInAudioRange object is created from an empty string -> error.
*/
void TestPosInAudioRange::test2(void)
{
  const QString& str = QString("");
  PosInAudioRange g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInAudioRange::INTERNALSTATE::EMPTY) );
}

/*
  A PosInAudioRange object is created from a ill-formed string -> error
*/
void TestPosInAudioRange::test3a(void)
{
  const QString& str = QString("49-");
  PosInAudioRange g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInAudioRange::INTERNALSTATE::ILL_FORMED_SRC_STRING) );
}

/*
  A PosInAudioRange object is created from a ill-formed string -> error
*/
void TestPosInAudioRange::test3b(void)
{
  const QString& str = QString("-49");
  PosInAudioRange g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInAudioRange::INTERNALSTATE::ILL_FORMED_SRC_STRING) );
}

/*
  A PosInAudioRange object is created from a ill-formed string -> error
*/
void TestPosInAudioRange::test3c(void)
{
  const QString& str = QString("49 50");
  PosInAudioRange g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInAudioRange::INTERNALSTATE::ILL_FORMED_SRC_STRING) );
}

/*
  A PosInAudioRange object is created from a ill-formed string (x0==x1) -> error
*/
void TestPosInAudioRange::test3d(void)
{
  const QString& str = QString("144-144");
  PosInAudioRange g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInAudioRange::INTERNALSTATE::X0X1) );
}

/*
  A PosInAudioRange object is created from a ill-formed string (x0>x1) -> error
*/
void TestPosInAudioRange::test3e(void)
{
  const QString& str = QString("144-143");
  PosInAudioRange g(str);

  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInAudioRange::INTERNALSTATE::X0X1) );
}

/*
  testing the == operator with two equivalent PosInAudioRange objects
*/
void TestPosInAudioRange::test4a(void)
{
  const QString& str1 = QString("  94- 95 ");
  PosInAudioRange g1(str1);
  const QString& str2 = QString("94-95");
  PosInAudioRange g2(str2);

  QCOMPARE( g1 , g2 );
}

/*
  testing the != operator with two different PosInAudioRange objects
*/
void TestPosInAudioRange::test4b(void)
{
  const QString& str1 = QString("  94- 95 ");
  PosInAudioRange g1(str1);
  const QString& str2 = QString("94-96");
  PosInAudioRange g2(str2);

  QVERIFY( g1 != g2 );
}

/*
  a PosInAudioRange object is created from a pair of integers, no problem.
*/
void TestPosInAudioRange::test5a(void)
{
  PosInAudioRange g( 1, 2 );
  QCOMPARE( g.well_initialized() , true );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInAudioRange::INTERNALSTATE::OK) );

  QCOMPARE( g.first(), 1 );
  QCOMPARE( g.second(), 2 );
}

/*
  a PosInAudioRange object is created from a wrong list of pair of integers -> error
*/
void TestPosInAudioRange::test5b(void)
{
  PosInAudioRange g( 350, 250 );
  QCOMPARE( g.well_initialized() , false );
  QCOMPARE( g.internal_state() , static_cast<int>(PosInAudioRange::INTERNALSTATE::X0X1) );
}

/*
  test of get_hash() : same objects, same hash
*/
void TestPosInAudioRange::test5c(void)
{
  PosInAudioRange g1a(QString("94-98"));
  PosInAudioRange g1b(QString(" 94 - 98"));
  QCOMPARE( g1a.get_hash() , g1b.get_hash() );

  PosInAudioRange g2a(QString(""));
  PosInAudioRange g2b(QString(""));
  QCOMPARE( g2a.get_hash() , g2b.get_hash() );

  PosInAudioRange g3a(QString("1-2"));
  PosInAudioRange g3b(QString("1-2"));
  QCOMPARE( g3a.get_hash() , g3b.get_hash() );
}

/*
  test of get_hash() : different objects, different hash
*/
void TestPosInAudioRange::test5d(void)
{
  PosInAudioRange g1a(QString("94-99"));
  PosInAudioRange g1b(QString("94-98"));
  QVERIFY( g1a.get_hash() != g1b.get_hash() );

  PosInAudioRange g2a(QString(""));
  PosInAudioRange g2b(QString("1-2"));
  QVERIFY( g2a.get_hash() != g2b.get_hash() );

  PosInAudioRange g3a(QString("1-2"));
  PosInAudioRange g3b(QString("1-3"));
  QVERIFY( g3a.get_hash() != g3b.get_hash() );
}
