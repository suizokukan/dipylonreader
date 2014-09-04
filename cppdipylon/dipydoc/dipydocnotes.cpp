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

    ❏Dipylon❏ : dipydoc/dipydocnotes.cpp

*******************************************************************************/

#include <dipydoc/dipydocnotes.h>
#include <QDebug>

/*______________________________________________________________________________

        DipyDocNote::repr()

        Return a string representing the object.
______________________________________________________________________________*/
QString DipyDocNote::repr(void) {
  QString res = "";

  res += "level=" + QString().setNum(this->level);
  res += "; ";

  res += "PosInTextRanges=" + this->posintextranges.repr();
  res += "; ";

  res += "text='" + this->text + "'";
  res += "; ";

  res += "textformatname='" + this->textformatname + "'";
  res += "; ";

  res += "arrows' number=" + QString().setNum(this->arrows.size());
  res += "; ";

  return res;
}

/*______________________________________________________________________________

        DipyDocNotes::repr()

        Return a string representing the object.
______________________________________________________________________________*/
QString DipyDocNotes::repr(void) {
  QString res = "";
  for (auto &note_by_level : this->map) {
    // note_by_level.first : (int)level
    // note_by_level.second : std::map<PosInTextRanges, DipyDocNote>
    for (auto &pos_and_note : note_by_level.second) {
      // pos_and_note.first : PosInTextRanges
      // pos_and_note.second : DipyDocNote
      res += "\n * level= " + QString().setNum(note_by_level.first) + "; " + \
             "ranges= " + pos_and_note.first.repr() + "; " + \
             "note= " + pos_and_note.second.repr() + "; ";
    }
  }
  return res;
}

/*______________________________________________________________________________

        DipyDocNotes::insert()

        insert in map[level][pos] a 'note'.
______________________________________________________________________________*/
UMAPPosNoteI_BOOL DipyDocNotes::insert(int level, PosInTextRanges pos, DipyDocNote note) {
  if (this->map.count(level) == 0) {
    UMAP_PosNote empty_map;
    this->map[level] = empty_map;
    return this->map[level].insert( std::pair<PosInTextRanges, DipyDocNote>(pos, note) );
  }
  else {
    return this->map[level].insert( std::pair<PosInTextRanges, DipyDocNote>(pos, note) );
  }
}
