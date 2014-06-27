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

    ❏Dipylon❏ : tests/testlanguagefromto.cpp

    ⇨ tests for LanguageFromTo objects.

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

#include "testlanguagefromto.h"

/*
  A LanguageFromTo object is created from a normal string.
*/
void TestLanguageFromTo::test0(void)
{
  LanguageFromTo l("lat->fra");

  QCOMPARE( l.well_initialized() , true );
  QCOMPARE( l.internal_state() , static_cast<int>(LanguageFromTo::INTERNALSTATE::OK) );
  QCOMPARE( l.from(), QString("lat") );
  QCOMPARE( l.to(), QString("fra") );
}

/*
  error : "from" langage doesnt' exist
*/
void TestLanguageFromTo::test1a(void)
{
  LanguageFromTo l("XXX->fra");

  QCOMPARE( l.well_initialized() , false );
  QCOMPARE( l.internal_state() , static_cast<int>(LanguageFromTo::INTERNALSTATE::UNDEFINED_FROMLANGUAGE) );
}

/*
  error : "to" langage doesnt' exist
*/
void TestLanguageFromTo::test1b(void)
{
  LanguageFromTo l("lat->XXX");

  QCOMPARE( l.well_initialized() , false );
  QCOMPARE( l.internal_state() , static_cast<int>(LanguageFromTo::INTERNALSTATE::UNDEFINED_TOLANGUAGE) );
}

/*
  error : ill-formed source string.
*/
void TestLanguageFromTo::test2a(void)
{
  LanguageFromTo l("lat-fra");

  QCOMPARE( l.well_initialized() , false );
  QCOMPARE( l.internal_state() , static_cast<int>(LanguageFromTo::INTERNALSTATE::ILLFORMED_SOURCE_STRING) );
}

/*
  error : ill-formed source string.
*/
void TestLanguageFromTo::test2b(void)
{
  LanguageFromTo l("lat->fra->eng");

  QCOMPARE( l.well_initialized() , false );
  QCOMPARE( l.internal_state() , static_cast<int>(LanguageFromTo::INTERNALSTATE::ILLFORMED_SOURCE_STRING) );
}
