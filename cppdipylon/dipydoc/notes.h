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

    ❏DipylonReader❏ : dipydoc/notes.h

    Notes class.

*******************************************************************************/

#ifndef CPPDIPYLON_DIPYDOC_NOTES_H_
#define CPPDIPYLON_DIPYDOC_NOTES_H_

#include <QString>

#include <list>
#include <map>
#include <memory>

#include "dipydoc/syntagmas.h"
#include "pos/posintext/posintextranges.h"
#include "qt/arrowformat.h"
#include "qt/textformat.h"

/*______________________________________________________________________________

  Notes class, used in the DipyDoc class.
______________________________________________________________________________*/
struct Notes {
  // syntagmas' names->aspects :
  std::map<QString, TextFormat>                        syntagmas_aspects;

  // syntagmas' names->levels :
  std::map<QString, int>                               syntagmas_levels;

  // syntagmas' names->types :
  std::map<QString, TextFormat>                        syntagmas_types;

  // all syntagmas objects :
  std::list< std::shared_ptr<Syntagma> >               _syntagmas;

  // syntagmas ordered by level :
  std::map<int, std::map<PosInTextRanges, Syntagma*> > syntagmas;

  // arrows
  std::map<QString, ArrowFormat> arrows_types;

  Syntagma*                                            contains(PosInText x0, int level) const;
  QString                                              repr(void) const;
};

#endif  // CPPDIPYLON_DIPYDOC_NOTES_H_
