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

#ifndef CPPDIPYLON_POS_POSINTEXT_VECTORPOSINTEXTRANGES_H_
#define CPPDIPYLON_POS_POSINTEXT_VECTORPOSINTEXTRANGES_H_

#include <QString>

#include <algorithm>
#include <vector>

#include "pos/posintext/posintextranges.h"

/*
  type used by the main object of VectorPosInTextRanges, a vector of PosInTextRanges.
*/
typedef std::vector<PosInTextRanges> VPosInTextRanges;
typedef std::vector<PosInTextRanges>::const_iterator VPosInTextRangesCI;

/*______________________________________________________________________________


  VectorPosInTextRanges class

  wrapper around a VPosInTextRanges object named "vposintextranges".

______________________________________________________________________________*/
struct VectorPosInTextRanges {
        VPosInTextRanges vposintextranges;

                               VectorPosInTextRanges(void);
                               VectorPosInTextRanges(const VectorPosInTextRanges&);
                               VectorPosInTextRanges(VPosInTextRanges);
        VectorPosInTextRanges& operator=(const VectorPosInTextRanges&);
        VPosInTextRangesCI     begin(void) const;
        void                   clear(void);
        VPosInTextRangesCI     end(void) const;
        std::size_t            size(void) const;
        void                   sort(void);
        QString                to_str(void) const;

        const char* MAIN_SEPARATOR = "/";

        /*
                Functor used to sort VectorPosInTextRanges.
        */
        struct VectorPosInTextRangesCMP {
                VectorPosInTextRanges* m;

                VectorPosInTextRangesCMP(VectorPosInTextRanges* p) : m(p) {}

                // is (PosInTextRanges)ii < (PosInTextRanges)jj ?
                bool operator() (PosInTextRanges ii, PosInTextRanges jj) {
                  auto i = ii.begin();
                  auto j = jj.begin();

                  while (i != ii.end() && j != jj.end()) {
                    if (i->first < j->first) {
                        return true;
                    }
                    if (i->first > j->first) {
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

inline VectorPosInTextRanges::VectorPosInTextRanges(VPosInTextRanges v) : vposintextranges(v)
{}

inline VectorPosInTextRanges::VectorPosInTextRanges(const VectorPosInTextRanges& other)  : \
                       vposintextranges(other.vposintextranges)
{}

inline VectorPosInTextRanges& VectorPosInTextRanges::operator=(const VectorPosInTextRanges& other) {
  if (this != &other) {
    this->vposintextranges = other.vposintextranges;
  }
  return *this;
}

inline VPosInTextRangesCI VectorPosInTextRanges::begin(void) const {
  return this->vposintextranges.begin();
}

inline VPosInTextRangesCI VectorPosInTextRanges::end(void) const {
  return this->vposintextranges.end();
}

inline std::size_t VectorPosInTextRanges::size(void) const {
  return this->vposintextranges.size();
}

#endif  // CPPDIPYLON_POS_POSINTEXT_VECTORPOSINTEXTRANGES_H_
