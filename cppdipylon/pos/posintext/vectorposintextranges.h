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

    ❏Dipylon❏ : pos/posintext/vectorposintextranges.h

    Simple wrapper around vector<PosInTextRanges>.
    ____________________________________________________________________________

    HOW TO USE :

    VectorPosInTextRanges v1 = \
    VectorPosInTextRanges(  { PosInTextRanges( { {10,20}, {150,250} } ),
                              PosInTextRanges( { {0,5}, {11, 20} } ),
                              PosInTextRanges( { {8, 9}, {91,92} } ),
                              PosInTextRanges( { {1, 2}, {190,191} } ),
                              PosInTextRanges( { {0,5}, {10, 20} } ),
                         });
    qDebug() << v1.to_str();
    v1.sort();
    qDebug() << v1.to_str();

*******************************************************************************/

#ifndef VECTORPOSINTEXTRANGES_H
#define VECTORPOSINTEXTRANGES_H

#include "posintextranges.h"

#include <vector>

#include <QString>

/*______________________________________________________________________________


  VectorPosInTextRanges class

  wrapper around a std::vector<PosInTextRanges> object named "vposintextranges".

______________________________________________________________________________*/
struct VectorPosInTextRanges
{
        std::vector<PosInTextRanges> vposintextranges;

                         VectorPosInTextRanges(void);
                         VectorPosInTextRanges(const VectorPosInTextRanges&);
                         VectorPosInTextRanges(std::vector<PosInTextRanges>);
        VectorPosInTextRanges& operator=(const VectorPosInTextRanges&);
        void        clear(void);
        std::size_t size(void) const;
        void        sort(void);
        QString     to_str(void) const;

        const char* MAIN_SEPARATOR = "/";

        /*
                Functor used to sort VectorPosInTextRanges.
        */
	struct VectorPosInTextRangesCMP {

		VectorPosInTextRanges* m;

		VectorPosInTextRangesCMP(VectorPosInTextRanges* p) : m(p) {};

                // is (PosInTextRanges)ii < (PosInTextRanges)jj ?
                bool operator() ( PosInTextRanges ii, PosInTextRanges jj ) {
                  auto i = ii.begin();
                  auto j = jj.begin();

                  while(i != ii.end() && j != jj.end()) {

                    if( i->first < j->first ) {
   		      return true;
                    }
                    if( i->first > j->first ) {
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

inline VectorPosInTextRanges::VectorPosInTextRanges(void)
{}

inline VectorPosInTextRanges::VectorPosInTextRanges(std::vector<PosInTextRanges> v) : vposintextranges(v)
{}

inline VectorPosInTextRanges::VectorPosInTextRanges( const VectorPosInTextRanges& other )  : \
                       vposintextranges(other.vposintextranges)
{}

inline VectorPosInTextRanges& VectorPosInTextRanges::operator=(const VectorPosInTextRanges& other) {

  if( this != &other) {
    this->vposintextranges = other.vposintextranges;
  }
  return *this;
}

inline std::size_t VectorPosInTextRanges::size(void) const {
  return this->vposintextranges.size();
}

#endif
