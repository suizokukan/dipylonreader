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

    ❏DipylonReader❏ : dipydoc/arrowtarget.h

    ArrowTarget class, defining how an arrow links two group of words.

*******************************************************************************/

#ifndef CPPDIPYLON_DIPYDOC_ARROWTARGET_H_
#define CPPDIPYLON_DIPYDOC_ARROWTARGET_H_

#include <QString>

#include "pos/posintext/posintextranges.h"

/*______________________________________________________________________________

  ArrowTarget class, part of the DipyDocNote class

    This classe defines how an arrow links (1) the Syntagma object which possessing
  the ArrowTarget object (2) and the block of text described in
  ArrowTarget::final_position.
______________________________________________________________________________*/
struct ArrowTarget {
  QString type = "";                    // cf Notes::syntagmas_types
  PosInTextRanges final_position;

  ArrowTarget(const QString& _type,
              const PosInTextRanges& _final_position);
};

inline ArrowTarget::ArrowTarget(const QString& _type,
                                const PosInTextRanges& _final_position) : \
type(_type), final_position(_final_position) {
}

#endif  // CPPDIPYLON_DIPYDOC_ARROWTARGET_H
