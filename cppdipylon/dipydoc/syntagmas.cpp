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

    ❏DipylonReader❏ : dipydoc/syntagmas.cpp

    See syntagmas.h for the documentation

*******************************************************************************/

#include "dipydoc/syntagmas.h"

/*______________________________________________________________________________

        Syntagma::Syntagma

        Syntagma class default constructor
______________________________________________________________________________*/
Syntagma::Syntagma(void) {
  this->father = nullptr;
  this->highest_ancestor = nullptr;
  this->posintextranges = PosInTextRanges();
  this->name = QString("");
  this->type = QString("");
  this->textnote = QString("");
}

/*______________________________________________________________________________

        Syntagma::Syntagma

        Syntagma class normal constructor
______________________________________________________________________________*/
Syntagma::Syntagma(Syntagma* _father,
                   Syntagma* _highest_ancestor,
                   QList<Syntagma*> _ancestors,
                   PosInTextRanges _posintextranges,
                   QString _name,
                   QString _type,
                   QString _textnote) : father(_father),
                                        highest_ancestor(_highest_ancestor),
                                        ancestors(_ancestors),
                                        posintextranges(_posintextranges),
                                        name(_name),
                                        type(_type),
                                        textnote(_textnote) {
}

/*______________________________________________________________________________

        Syntagma::~Syntagma

        Syntagma class destructor
______________________________________________________________________________*/
Syntagma::~Syntagma(void) {
  // DEBUG1 DebugMsg() << "~Syntagma name=" << this->name << " type=" << this->type;
}

/*______________________________________________________________________________

        Syntagma::repr

        debugging-oriented function
______________________________________________________________________________*/
QString Syntagma::repr(void) {
  QString arrowsnumber = QString("arrows' number=%1").arg(QString().setNum(this->arrows.size()));

  if (this->father == nullptr) {
    return QString("(no father)"
                   "name=%1; type=%2; textnote=%3 arrows'number=%4").arg(this->name,
                                                                         this->type,
                                                                         this->textnote,
                                                                         QString().setNum(this->arrows.size()));
  } else {
    if (this->highest_ancestor==nullptr) {
      return QString("(no forefather)(father's name=%4)"
                     "name=%1; type=%2; textnote=%3 arrows'num.=%5").arg(this->name,
                                                                         this->type,
                                                                         this->textnote,
                                                                         this->father->name,
                                                                         QString().setNum(this->arrows.size()));
    } else {
      return QString("(forefather's name=%5)(father's name=%4)"
                     "name=%1; type=%2; textnote=%3 arrows'num.=%6").arg(this->name,
                                                                         this->type,
                                                                         this->textnote,
                                                                         this->father->name,
                                                                         this->highest_ancestor->name,
                                                                         QString().setNum(this->arrows.size()));
    }
  }
}

/*______________________________________________________________________________

        Syntagma::pretty_debugmsg

        Debug-oriented function : display the current Syntagma and its soons.

______________________________________________________________________________*/
QString Syntagma::pretty_debugmsg(int hlevel) {
  QString res;

  QString spacer("");
  for (int i = 0; i < hlevel; ++i) {
    spacer += QString("  ");
  }

  res += spacer + QString("%1 %2 %3").arg(this->name,
                                          this->type,
                                          this->posintextranges.repr()) + "\n";

  for (auto & soon : this->soons) {
    res += soon->pretty_debugmsg(hlevel+1);
  }

  return res;
}
