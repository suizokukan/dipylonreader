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

    ❏Dipylon❏ : posintxt/vectorposranges.h

    Simple wrapper around vector<PosRanges>.
    ____________________________________________________________________________

    HOW TO USE :

    VectorPosRanges v1 = \
    VectorPosRanges(  { PosRanges( { {10,20}, {150,250} } ),
                        PosRanges( { {0,5}, {11, 20} } ),
                        PosRanges( { {8, 9}, {91,92} } ),
                        PosRanges( { {1, 2}, {190,191} } ),
                        PosRanges( { {0,5}, {10, 20} } ),
                   });
    qDebug() << v1.to_str();
    v1.sort();
    qDebug() << v1.to_str();

*******************************************************************************/

#ifndef VECTORPOSRANGES_H
#define VECTORPOSRANGES_H

#include "posranges.h"

#include <vector>

#include <QString>

/*______________________________________________________________________________


  VectorPosRanges class

  wrapper around a std::vector<PosRanges> object named "vposranges".

______________________________________________________________________________*/
struct VectorPosRanges
{
        std::vector<PosRanges> vposranges;

                         VectorPosRanges(void);
                         VectorPosRanges(const VectorPosRanges&);
                         VectorPosRanges(std::vector<PosRanges>);
        VectorPosRanges& operator=(const VectorPosRanges&);
        std::size_t size(void) const;
        void        sort(void);
        QString     to_str(void) const;

        const char* MAIN_SEPARATOR = "/";

        /* 
                Functor used to sort VectorPosRanges.
        */
	struct VectorPosRangesCMP {

		VectorPosRanges* m;

		VectorPosRangesCMP(VectorPosRanges* p) : m(p) {};

                // is (PosRanges)ii < (PosRanges)jj ?
                bool operator() ( PosRanges ii, PosRanges jj ) {
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

inline VectorPosRanges::VectorPosRanges(void)
{}

inline VectorPosRanges::VectorPosRanges(std::vector<PosRanges> v) : vposranges(v)
{}

inline VectorPosRanges::VectorPosRanges( const VectorPosRanges& other )  : \
                       vposranges(other.vposranges)
{}

inline VectorPosRanges& VectorPosRanges::operator=(const VectorPosRanges& other) {

  if( this != &other) {
    this->vposranges = other.vposranges;
  }
  return *this;
}

inline std::size_t VectorPosRanges::size(void) const {
  return this->vposranges.size();
}

#endif


