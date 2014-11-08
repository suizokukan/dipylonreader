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

    ❏DipylonReader❏ : dipydoc/syntagmas.h

*******************************************************************************/

#ifndef CPPDIPYLON_DIPYDOC_SYNTAGMAS_H_
#define CPPDIPYLON_DIPYDOC_SYNTAGMAS_H_

#include <QList>
#include <QString>

#include <list>

#include "debugmsg/debugmsg.h"
#include "dipydoc/arrowtarget.h"
#include "pos/posintext/posintextranges.h"
#include "qt/textformat.h"

/*______________________________________________________________________________

  Syntagma class
______________________________________________________________________________*/
struct Syntagma {
  Syntagma*                             father;
  Syntagma*                             highest_ancestor;
  QList<Syntagma*>                      ancestors;
  PosInTextRanges                       posintextranges;
  QString                               name;
  QString                               type;
  QList<Syntagma*>                      soons;
  std::list<ArrowTarget>                arrows;
  QString                               textnote;

  QString                               repr(void);

                                        Syntagma(void);
                                       ~Syntagma(void);
                                        Syntagma(Syntagma* _father,
                                                 Syntagma* _highest_ancestor,
                                                 QList<Syntagma*> _ancestors,
                                                 PosInTextRanges _posintextranges,
                                                 QString _name,
                                                 QString _type,
                                                 QString _textnote);
  QString                               pretty_debugmsg(int hlevel);
};

#endif  // CPPDIPYLON_DIPYDOC_SYNTAGMAS_H
