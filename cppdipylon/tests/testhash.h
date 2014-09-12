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

    ❏DipylonReader❏ : tests/testhash.h

    ⇨ tests of the hash function

    NB : Those tests are juste a way to check the hash function is "functional".
         Those tests doesn't deeply check that the hash function is ok, e.g.
         against collisions.

*********************************************************************************/

#ifndef TESTHASH_H
#define TESTHASH_H

#include "../misc/hash.h"

#include <QTest>

/*______________________________________________________________________________

        TestHash class : (minimal) test of the hash function

______________________________________________________________________________*/
class TestHash: public QObject
{
    Q_OBJECT

private slots:

   void test1a();
   void test1b();
};

#endif
