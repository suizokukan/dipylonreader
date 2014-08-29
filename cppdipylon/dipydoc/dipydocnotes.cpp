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

/*______________________________________________________________________________

        DipyDocNote::repr()

        Return a string representing the object.
______________________________________________________________________________*/
QString DipyDocNote::repr(void) {
  QString res = "";

  res += "level=" + QString().setNum(this->level);
  res += "; ";

  res += "PosInTextRanges=" + this->posintextranges.to_str();
  res += "; ";

  res += "text=" + this->text;
  res += "; ";

  res += "textformatname=" + this->textformatname;
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
      res += "* level= " + QString().setNum(note_by_level.first) + "; " + \
             "ranges= " + pos_and_note.first.to_str() + "; " + \
             "note= " + pos_and_note.second.repr() + "; " + \
             "\n";
    }
  }
  return res;
}
