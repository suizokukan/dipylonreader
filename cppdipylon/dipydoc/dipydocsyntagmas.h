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

    ❏DipylonReader❏ : dipydoc/dipydocsyntagmas.h

*******************************************************************************/

#ifndef CPPDIPYLON_DIPYDOC_DIPYDOCSYNTAGMAS_H_
#define CPPDIPYLON_DIPYDOC_DIPYDOCSYNTAGMAS_H_

#include <QString>

#include <list>
#include <map>
#include <memory>
#include <utility>

#include "debugmsg/debugmsg.h"
#include "pos/posintext/posintextranges.h"

/*______________________________________________________________________________

  ArrowTarget class, part of the DipyDocNote class $$$
______________________________________________________________________________*/
struct ArrowTarget {
  QString type = "";
  PosInTextRanges final_position;

  ArrowTarget(const QString& _type, const PosInTextRanges& _final_position);
};
inline ArrowTarget::ArrowTarget(const QString& _type, const PosInTextRanges& _final_position) : \
type(_type), final_position(_final_position) {
}

/*______________________________________________________________________________

  Syntagma class
______________________________________________________________________________*/
struct Syntagma {
  Syntagma*                             father;
  int                                   level;
  PosInTextRanges                       posintextranges;
  QString                               name;
  QString                               type;
  std::list<Syntagma*>                  soons;
  std::list<ArrowTarget>                arrows;
  QString                               textnote;

  QString                               repr(void);

                                        Syntagma(void);
                                       ~Syntagma(void);
                                        Syntagma(Syntagma* _father,
                                                 int _level,
                                                 PosInTextRanges _posintextranges,
                                                 QString _name,
                                                 QString _type,
                                                 QString _textnote);
};

/*______________________________________________________________________________

  Notes class, used in the DipyDoc class.
______________________________________________________________________________*/
struct Notes {
  // syntagmas' names->aspects :
  std::map<QString, QString> syntagmas_names;
  // all syntagmas objects :
  std::list< std::shared_ptr<Syntagma> > _syntagmas;
  std::map<int, std::map<PosInTextRanges, Syntagma*> > syntagmas;

  QString repr(void) const;
};

inline QString Notes::repr(void) const {
  QString res;

  for (auto & syntagma : this->_syntagmas) {
    res += syntagma->repr() + "\n";
  }

  return res;
}
#endif
