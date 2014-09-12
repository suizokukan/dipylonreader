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

    ❏DipylonReader❏ : tests/testhash.cpp

    ⇨ tests of the hash function

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

#include "testhash.h"

/*
  creating two (hopefully) different hashes from two different pairs of integers.
*/
void TestHash::test1a()
{
  int v1 = 1;
  int v2 = 2;
  std::size_t hash1 = 0;
  hash_combine( hash1, v1 );
  hash_combine( hash1, v2 );

  v1 = 10;
  v2 = 20;
  std::size_t hash2 = 0;
  hash_combine( hash2, v1 );
  hash_combine( hash2, v2 );

  QVERIFY( hash1 != hash2 );
}

/*
  creating two (hopefully) different hashes from two different pairs of integers.
*/
void TestHash::test1b()
{
  int v1 = 1;
  int v2 = 2;
  std::size_t hash1 = 0;
  hash_combine( hash1, v1 );
  hash_combine( hash1, v2 );

  std::size_t hash2 = 0;
  hash_combine( hash2, v2 );
  hash_combine( hash2, v1 );

  QVERIFY( hash1 != hash2 );
}
