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

    ❏Dipylon❏ : gaps.h

    ⇨ Use Gaps objects to store a list of integers. Gaps objects are nothing
    but vector<pair<int,int>> .
      A Gaps object can be initialized from a QString (see GAPS_STR infra).
      After beeing initialized, check the (bool)well_initialized attribute.

    ⇨ about the implementation : std::vector<std::pair<int,int> > has not been
    derived to get the Gaps class. Deriving std containers isn't a good
    idea since these classes have no virtual destructor, hence no real
    polymorphic abilities.
    E.g. see discussion here : http://stackoverflow.com/questions/4353203

    ⇨ GAPS_STR format : "45-97", "45-97+123-136+999-1001", ...
        no spaces allowed.
        MAIN_SEPARATOR, SECONDARY_SEPARATOR : only one character.
        at least one gap must be defined (no empty string)
        x0 must be <= x1 (no "45-22")

    ⇨ how to use :
    #include "gaps.h"

    QString str = QString("94-95+97-98+101-105");
    Gaps *g = new Gaps(&str);
    if( g->well_initialized )
    {
        qDebug() << g->toStr() << endl;
        qDebug() << g->is_inside(100) << endl;
        qDebug() << g->is_inside(105) << endl;
        qDebug() << g->is_inside(106) << endl;
    }

*******************************************************************************/

#ifndef GAPS_H
#define GAPS_H

#include <QString>
#include <vector>

class Gaps
{
    public:
        Gaps(QString*);
        QString toStr(void);
        bool is_inside(int);

    private:
        bool well_initialized;
        std::vector<std::pair<int,int> > vec;

        // for more details, see the GAPS_STR format :
        const char* MAIN_SEPARATOR = "+";
        const char* SECONDARY_SEPARATOR = "-";
};

#endif
