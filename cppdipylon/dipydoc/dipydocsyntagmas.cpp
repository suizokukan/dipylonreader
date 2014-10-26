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
  this->level = 0;
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
                   int _level,
                   PosInTextRanges _posintextranges,
                   QString _name,
                   QString _type,
                   QString _textnote) : father(_father),
                                        level(_level),
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
  DebugMsg() << "~Syntagma name=" << this->name << " type=" << this->type << " level=" << this->level;
}

/*______________________________________________________________________________

        Syntagma::repr

        debugging-oriented function
______________________________________________________________________________*/
QString Syntagma::repr(void) {
  if (this->father==nullptr) {
    return QString("(no father) name=%1; type=%2; textnote=%3").arg(this->name,
                                                                    this->type,
                                                                    this->textnote);
  } else {
   return QString("(father's name=%4) name=%1; type=%2; textnote=%3").arg(this->name,
                                                                          this->type,
                                                                          this->textnote,
                                                                          this->father->name);
  }
}
