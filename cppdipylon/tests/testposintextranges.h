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

    ❏DipylonReader❏ : tests/testposintextranges.h

    ⇨ tests for PosInTextRanges objects.

*********************************************************************************/

#ifndef TESTPOSINTEXTRANGES_H
#define TESTPOSINTEXTRANGES_H

#include "../pos/posintext/posintextranges.h"

#include <QTest>

/*______________________________________________________________________________

        TestPosInTextRanges class : test of PosInTextRanges module.

______________________________________________________________________________*/
class TestPosInTextRanges: public QObject
{
    Q_OBJECT

private slots:

  void test0(void);
  void test1(void);
  void test2(void);
  void test3(void);
  void test4a(void);
  void test4b(void);
  void test4c(void);
  void test4d(void);
  void test4e(void);
  void test5a(void);
  void test5b(void);
  void test6a(void);
  void test6b(void);
  void test7a(void);
  void test7b(void);
  void test7c(void);
  void test7d(void);
  void test8a(void);
  void test8b(void);
  void test9a(void);
  void test9b(void);
  void test10_minmax(void);
  void test11a(void);
  void test11b(void);
  void test12a(void);
  void test12b(void);
  void test12c(void);
  void test12d(void);
  void test12e(void);
};

#endif
