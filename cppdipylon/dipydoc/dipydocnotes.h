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

    ❏Dipylon❏ : dipydoc/dipydocnotes.h

    DipyDocNote and ArrowTargetInANote classes

*******************************************************************************/

#ifndef CPPDIPYLON_DIPYDOC_DIPYDOCNOTES_H_
#define CPPDIPYLON_DIPYDOC_DIPYDOCNOTES_H_

#include <QString>

#include <unordered_map>
#include <map>

#include "pos/posintext/posintextranges.h"

/*______________________________________________________________________________

  ArrowTargetInANote class, part of the DipyDocNote class
______________________________________________________________________________*/
struct ArrowTargetInANote {
  QString textformatname = "";
  PosInTextRanges final_position;
};

/*______________________________________________________________________________

  DipyDocNote class
______________________________________________________________________________*/
struct DipyDocNote {
  int                                   level;
  PosInTextRanges                       posintextranges;
  QString                               text;
  QString                               textformatname;
  std::map<QString, ArrowTargetInANote> arrows;

                                        DipyDocNote(void);
                                        DipyDocNote(int, PosInTextRanges, QString, QString);
                           DipyDocNote& operator=(const DipyDocNote& other);
  QString                               repr(void);
};
inline DipyDocNote::DipyDocNote(void) {
  this->level = 0;
  this->posintextranges = PosInTextRanges();
  this->text = QString("");
  this->textformatname = QString("");
  this->arrows.clear();
}
inline DipyDocNote::DipyDocNote(int _level, PosInTextRanges _posintextranges, QString _text, QString _textformatname) : \
level(_level), posintextranges(_posintextranges), text(_text), textformatname(_textformatname) {
}
inline DipyDocNote& DipyDocNote::operator=(const DipyDocNote& other) {
  if (this != &other) {
    this->level = other.level;
    this->posintextranges = other.posintextranges;
    this->text = other.text;
    this->textformatname = other.textformatname;
    this->arrows = other.arrows;
  }
  return *this;
}

/*______________________________________________________________________________

  DipyDocNotes class

  This class is used to create an attribute of DipyDoc.

______________________________________________________________________________*/

typedef std::unordered_map<PosInTextRanges, DipyDocNote, PosInTextRangesHasher> UMAP_PosNote;

// (int)level -> (PosInTextRanges, DipyDocNote)
typedef std::map<int, UMAP_PosNote> MAP_Int2PosNote;
typedef MAP_Int2PosNote::const_iterator MAP_Int2PosNoteCI;

struct DipyDocNotes {

  MAP_Int2PosNote   map;

  void              insert(int level, PosInTextRanges pos, DipyDocNote note);

  void              clear(void);
  QString           repr(void);
  std::size_t       size(void);
};

inline void DipyDocNotes::clear(void) {
  this->map.clear();
}

inline std::size_t DipyDocNotes::size(void) {
  return this->map.size();
}

#endif  // CPPDIPYLON_DIPYDOC_NOTES_H_
