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

    ⇨ Use Gaps objects to store a list of integers.
      A Gaps object can be initialized from a QString (see GAPS_STR infra).
      After beeing initialized, check the (bool)well_initialized attribute.

    ⇨ about the implementation : std::vector<std::pair<int,int> > has not been
      derived to get the Gaps class. Deriving std containers isn't a good
      idea since these classes have no virtual destructor, hence no real
      polymorphic abilities.
      E.g. see discussion here : http://stackoverflow.com/questions/4353203

    ⇨ about the implementation : no virtual destructor has been added : Gaps
      objects can't be safely used to create subclasses.
      E.g. see discussion here : http://stackoverflow.com/questions/461203

    ⇨ overlapping is forbidden : "0…1+1…2" is ok, not "0…1+0…2", not "46…49+48…52"

    ⇨ GAPS_STR format : "45…97", "45…97+123…136+999…1001", ...
        no spaces allowed 
        overlapping is forbidden (vide  supra) 
        MAIN_SEPARATOR, SECONDARY_SEPARATOR : only one character.
        at least one gap must be defined (no empty string)
        x0 must be < x1 (no "45…22", no "45…45")

    ⇨ how to use :
    #include "gaps.h"
 
    // either...
    const QString& str = QString("94…95+97…98+101…105");
    Gaps *g = new Gaps(str);
    // ... either :
    Gaps g( { {94,95} , {97,98}, {101,105} } );

    if( g->well_initialized() )
    {
        qDebug() << g->to_str() << endl;
        qDebug() << g->is_inside(100) << endl;
        qDebug() << g->is_inside(105) << endl;
        qDebug() << g->is_inside(106) << endl;
    }
    delete g;

*******************************************************************************/

#ifndef GAPS_H
#define GAPS_H

#include <QString>
#include <vector>

class Gaps
{
  friend class GapsHasher;

    public:
        Gaps(const QString& src_qstring);
        Gaps(std::initializer_list< std::pair<int, int> >);
        QString to_str(void);
        int internal_state(void);
        bool is_inside(int);
        size_t size(void);
        bool well_initialized(void);
        void checks(void);

        bool operator==(const Gaps& aliud);
        bool operator!=(const Gaps& aliud);

        // constants used to define the internal_state attribute :
        const int INTERNALSTATE_OK = 0;
        const int INTERNALSTATE_NOMAINSEP = 1;
        const int INTERNALSTATE_SECONDSEP = 2;
        const int INTERNALSTATE_X0X1 = 3;
        const int INTERNALSTATE_EMPTY = 4;
        const int INTERNALSTATE_OVERLAPPING = 5;

    private:
        std::vector<std::pair<int,int> > vec;
        int _internal_state;
        bool _well_initialized;

        // for more details, see the GAPS_STR format :
        const char* MAIN_SEPARATOR = "+";
        const char* SECONDARY_SEPARATOR = "…";
};

struct GapsHasher
{
  std::size_t operator()(const Gaps& k) const;
};

#endif
