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

    ❏DipylonReader❏ : tests/testposintext2str.h

    ⇨ tests of the PosInText2Str module.

*********************************************************************************/

#ifndef TESTPOS2STR_H
#define TESTPOS2STR_H

#include "../pos/posintext/posintextranges.h"
#include "../pos/posintext/posintext2str.h"

#include <QTest>

/*______________________________________________________________________________

        TestPosInText2Str class : test of the PosInText2Str module.

______________________________________________________________________________*/
class TestPosInText2Str: public QObject
{
    Q_OBJECT

private slots:
  void test0(void);
  void test1(void);
  void test2a(void);
  void test2b(void);
};

#endif
