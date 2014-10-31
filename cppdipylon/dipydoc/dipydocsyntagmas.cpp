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

    ❏DipylonReader❏ : dipydoc/dipydocsyntagmas.cpp

    See dipydocsyntagmas.h for the documentation

*******************************************************************************/

#include "dipydoc/dipydocsyntagmas.h"

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
  DebugMsg() << "~Syntagma name=" << this->name << " type=" << this->type;
}

/*______________________________________________________________________________

        Syntagma::repr

        debugging-oriented function
______________________________________________________________________________*/
QString Syntagma::repr(void) {

  QString arrowsnumber = QString("arrows' number=%1").arg(QString().setNum(this->arrows.size()));

  if (this->father==nullptr) {
    return QString("(no father) name=%1; type=%2; textnote=%3 arrows'number=%4").arg(this->name,
                                                                                     this->type,
                                                                                     this->textnote,
                                                                                     QString().setNum(this->arrows.size()));
  } else {
    if (this->highest_ancestor==nullptr) {
      return QString("(no forefather)(father's name=%4) name=%1; type=%2; textnote=%3 arrows'num.=%5").arg(this->name,
                                                                                            this->type,
                                                                                            this->textnote,
                                                                                            this->father->name,
                                                                                            QString().setNum(this->arrows.size()));
    } else {
      return QString("(forefather's name=%5)(father's name=%4) name=%1; type=%2; textnote=%3 arrows'num.=%6").arg(this->name,
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
  for(int i=0; i<hlevel; ++i) {
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

/*______________________________________________________________________________

        Notes::contains

        Is there a note about x0 at "level".
        Return nullptr if "x0" doesn't match anything
______________________________________________________________________________*/
Syntagma* Notes::contains(PosInText x0, int level) const {
  // does the "level" exist in this->syntagmas ?
  if (this->syntagmas.find(level) == this->syntagmas.end()) {
    // ... no :
    return nullptr;
  }

  Syntagma* res = nullptr;
  for (auto & posintextranges_and_syntagma : this->syntagmas.at(level)) {
    if (posintextranges_and_syntagma.first.contains(x0) == true) {
      res = posintextranges_and_syntagma.second;
      break;
    }
  }

  return res;
}

/*______________________________________________________________________________

        Notes::repr

        debugging-oriented function
______________________________________________________________________________*/
QString Notes::repr(void) const {
  QString res;

  res += "* arrows_types = \n";
  for (auto &arrow : this->arrows_types) {
    res += QString("\n  name='%1' - arrowformat='%2'").arg(arrow.first,
                                                           arrow.second.repr());
  }

  res += "* syntagmas_levels = \n";
  for (auto & name_and_level : this->syntagmas_levels) {
    res += QString("** %1 -> %2\n").arg(name_and_level.first).arg(name_and_level.second);
  }

  res += "* syntagmas_aspects = \n";
  for (auto & name_and_aspect : this->syntagmas_aspects) {
    res += QString("** %1 -> foreground=%2 background=%3\n").arg(name_and_aspect.first,
                                                                 name_and_aspect.second.qtextcharformat().foreground().color().name(),
                                                                 name_and_aspect.second.qtextcharformat().background().color().name());
  }

  res += "* syntagmas_types = \n";
  for (auto & name_and_type : this->syntagmas_types) {
    res += QString("** %1 -> foreground=%2 background=%3\n").arg(name_and_type.first,
                                                                 name_and_type.second.qtextcharformat().foreground().color().name(),
                                                                 name_and_type.second.qtextcharformat().background().color().name());
  }

  res += "* _syntagmas = \n";
  for (auto & syntagma : this->_syntagmas) {
    res += "** " + syntagma->repr() + "\n";
  }

  // first way to display this->syntagmas :
  res += "* syntagmas(1/2) = \n";
  for(auto & level_and_syntagmasbylevel : this->syntagmas) {
    // for an unknown reason QString().arg(1,2) doesn't work, .arg(1).arg(2) does.
    res += QString("** at level=%1, %2 syntagma(s) :\n").arg(level_and_syntagmasbylevel.first).arg(this->syntagmas.at(level_and_syntagmasbylevel.first).size());
    for (auto & posintextranges_and_syntagma : level_and_syntagmasbylevel.second) {
      res += QString("** posintextranges=%1 : %2\n").arg(posintextranges_and_syntagma.first.repr(),
                                                         posintextranges_and_syntagma.second->repr());
    }
  }

  // second way to display this->syntagmas :
  res += "* syntagmas(2/2) =\n";
  for(auto & level_and_syntagmasbylevel : this->syntagmas) {
    for(auto & posintext_and_syntagma : level_and_syntagmasbylevel.second) {
      if (posintext_and_syntagma.second->father==nullptr) {
        res += posintext_and_syntagma.second->pretty_debugmsg(0);
      }
    }
  }

  return res;
}
