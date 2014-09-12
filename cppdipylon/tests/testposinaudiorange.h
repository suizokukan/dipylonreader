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

    ❏DipylonReader❏ : tests/testposinaudioranges.h

    ⇨ tests for PosInAudioRange objects.

*********************************************************************************/

#ifndef TESTPOSINAUDIORANGE_H
#define TESTPOSINAUDIORANGE_H

#include "../pos/posinaudio/posinaudiorange.h"

#include <QTest>
#include <QString>

/*______________________________________________________________________________

        TestPosInAudioRange class : test of PosInAudioRange module.

______________________________________________________________________________*/
class TestPosInAudioRange: public QObject
{
    Q_OBJECT

private slots:

  void test0(void);
  void test1(void);
  void test2(void);
  void test3a(void);
  void test3b(void);
  void test3c(void);
  void test3d(void);
  void test3e(void);
  void test4a(void);
  void test4b(void);
  void test5a(void);
  void test5b(void);
  void test5c(void);
  void test5d(void);
};

#endif
