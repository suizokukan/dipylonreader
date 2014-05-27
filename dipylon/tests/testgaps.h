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

    ❏Dipylon❏ : tests/testgaps.h

    ⇨ tests for Gaps objects.

*********************************************************************************/

#include "../gaps.h"

#include <QtTest/QtTest>

/*______________________________________________________________________________

        TestGaps class : test of Gaps module.

______________________________________________________________________________*/
class TestGaps: public QObject
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
  void test5a(void);
  void test5b(void);
  void test6a(void);
  void test6b(void);
  void test7a(void);
  void test7b(void);
  void test7c(void);
  void test7d(void);
};
