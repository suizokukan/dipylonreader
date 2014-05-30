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

    ❏Dipylon❏ : postxt/vectorposranges.h

    Simple wrapper around vector<PosRanges>.

*******************************************************************************/

#ifndef VECTORPOSRANGES_H
#define VECTORPOSRANGES_H

#include "posranges.h"
#include <QString>

struct VectorPosRanges
{
        std::vector<PosRanges> vposranges;

                    VectorPosRanges(std::vector<PosRanges>);
        std::size_t size(void) const;
        void        sort(void);
        QString     to_str(void) const;

        const char* MAIN_SEPARATOR = "/";

        /* 
                Functor used to sort VectorPosRanges.
        */
	struct VectorPosRangesCMP
	{
		VectorPosRanges* m;
		VectorPosRangesCMP(VectorPosRanges* p) : m(p) {};
 
                bool operator() ( PosRanges ii, PosRanges jj )
		{
                  auto i = ii.begin();
                  auto j = jj.begin();
                  while(i != ii.end() && j != jj.end())
                  {
                    if( i->first < j->first )
                    {
   		      return true;
                    }
                    if( i->first > j->first )
                    {
   		      return false;
                    }

                    // if i->first == j->first, the function goes further :
                    ++i;
                    ++j;
                  }

                  return false;
		}
	};
};
#endif
