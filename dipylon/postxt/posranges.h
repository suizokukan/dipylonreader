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

    ❏Dipylon❏ : postxt/posranges.h

    ⇨ Use PosRanges objects to store a list of (TextPos)integers.
      A PosRanges object can be initialized from a QString (see POSRANGES_STR infra).
      After beeing initialized, check the (bool)well_initialized attribute.

    ⇨ about the implementation : std::vector<std::pair<int,int> > has not been
      derived to get the PosRanges class. Deriving std containers isn't a good
      idea since these classes have no virtual destructor, hence no real
      polymorphic abilities.
      E.g. see discussion here : http://stackoverflow.com/questions/4353203

    ⇨ about the implementation : no virtual destructor has been added : PosRanges
      objects can't be safely used to create subclasses.
      E.g. see discussion here : http://stackoverflow.com/questions/461203

    ⇨ overlapping is forbidden : "0…1+1…2" is ok, not "0…1+0…2", not "46…49+48…52"

    ⇨ POSRANGES_STR format : "45…97", "45…97+123…136+999…1001", ...
        no spaces allowed 
        overlapping is forbidden (vide  supra) 
        MAIN_SEPARATOR, SECONDARY_SEPARATOR : only one character.
        at least one gap must be defined (no empty string)
        x0 must be < x1 (no "45…22", no "45…45")

    ⇨ how to use :
    #include "posranges.h"
 
    // either...
    const QString& str = QString("94…95+97…98+101…105");
    PosRanges *g = new PosRanges(str);
    // ... either :
    PosRanges g( { {94,95} , {97,98}, {101,105} } );

    if( g->well_initialized() )
    {
        qDebug() << g->to_str() << endl;
        qDebug() << g->is_inside(100) << endl;
        qDebug() << g->is_inside(105) << endl;
        qDebug() << g->is_inside(106) << endl;
    }
    delete g;

*******************************************************************************/

#ifndef POSRANGES_H
#define POSRANGES_H

#include "../hash.h"

#include <vector>

#include <QString>
#include <QStringList>


typedef int TextPos;

class PosRanges
{
  friend class PosRangesHasher;
  friend class Pos2Str;

    public:
        PosRanges(void);
        PosRanges(const QString& src_qstring);
        PosRanges(std::initializer_list< std::pair<TextPos, TextPos> >);
        PosRanges(std::vector< std::pair<TextPos, TextPos> >);

        int     internal_state(void) const;
        bool    is_inside(TextPos) const;
        bool    is_inside(TextPos, TextPos) const;
        size_t  size(void) const;
        QString to_str(void) const;
        bool    well_initialized(void) const;

        bool    operator==(const PosRanges& other) const
        {
          return (this->_well_initialized == other._well_initialized) && (this->vec == other.vec); 
        }
        bool    operator!=(const PosRanges& other) const
        {
          return !(this->operator==(other));
        }

        // constants used to define the internal_state attribute :
        const int INTERNALSTATE_OK = 0;
        const int INTERNALSTATE_NOMAINSEP = 1;
        const int INTERNALSTATE_SECONDSEP = 2;
        const int INTERNALSTATE_X0X1 = 3;
        const int INTERNALSTATE_EMPTY = 4;
        const int INTERNALSTATE_OVERLAPPING = 5;

    private:
        // for more details, see the POSRANGES_STR format :
        const char* MAIN_SEPARATOR = "+";
        const char* SECONDARY_SEPARATOR = "…";

        std::vector<std::pair<TextPos, TextPos> > vec;
        int _internal_state;
        bool _well_initialized;

        void    checks(void);
};

struct PosRangesHasher
{
  std::size_t operator()(const PosRanges& k) const;
};

#endif
