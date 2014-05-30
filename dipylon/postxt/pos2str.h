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

    ❏Dipylon❏ : postxt/pos2str.h

    Pos2Str links PosRanges objects to a QString.

*******************************************************************************/

#ifndef POS2STR_H
#define POS2STR_H

#include "postxt/posranges.h"
#include "postxt/vectorposranges.h"

#include <unordered_map>
#include <vector>

#include <QString>

/*
  Structure used to easily initialize Pos2Str objects. E.g. :

      Pos2Str pos2str = {
        { {{ {1,2}, {3,4} },}, "example1"},
        { {{ {1,2}, {3,5} },}, "example2"},
        { {{ {1,2}, {3,8} },}, "example3"},
      };
*/
struct IntegersAndAString
{
  VectorPairTextPos integers;
  QString string;
};

class Pos2Str
{
    private:
        std::unordered_map<PosRanges, QString, PosRangesHasher> map;
        bool _well_initialized;
        int  _internal_state;

        void            checks(void);

    public:
                               Pos2Str(void);
                               Pos2Str(std::initializer_list< IntegersAndAString >);

        QString&               operator[]( VectorPairTextPos key );

        size_t                 size(void) const;
        int                    internal_state(void) const;
        PosRanges              is_inside(TextPos) const;
        VectorPosRanges        is_inside(TextPos, TextPos) const;
        bool                   well_initialized(void) const;

        // constants used to define the internal_state attribute :
        const int INTERNALSTATE_OK = 0;
        const int INTERNALSTATE_BADPOSRANGES = 1;
};

#endif
