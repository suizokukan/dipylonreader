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

    ❏DipylonReader❏ : qt/commentarytempdata.cpp

    see commentarytempdata.h for the documentation

*******************************************************************************/

#include "qt/commentarytempdata.h"

/*______________________________________________________________________________

        CommentaryTempData::CommentaryTempData()

        CommentaryTempData constructor
______________________________________________________________________________*/
CommentaryTempData::CommentaryTempData(SourceEditor * _source_zone__editor,
                                       QWidget * _parent) : QObject(_parent),
                                                            source_zone__editor(_source_zone__editor) {
}

/*______________________________________________________________________________

        CommentaryTempData::update()

        Initialize the informations stored in the CommentaryTempData object
        from the position in the text given as parameter.

        This informations will be used to display the translation and the
        commentary.
______________________________________________________________________________*/
void CommentaryTempData::update(const PosInTextRanges& _pos_in_text_ranges) {
  // DEBUG1 DebugMsg() << "CommentaryTempData::update() entry point " << _pos_in_text_ranges.repr();

  // setting the xy attribute :
  QTextCursor cur = this->source_zone__editor->textCursor();
  cur.setPosition(static_cast<int>(this->source_zone__editor->number_of_chars_before_source_text + \
                                   _pos_in_text_ranges.min()));
  QRect cur_rect = this->source_zone__editor->cursorRect(cur);
  cur_rect.translate(8, 30);
  this->xy = this->source_zone__editor->mapToGlobal(cur_rect.topLeft());

  // setting the text attribute :
  this->text = this->source_zone__editor->dipydoc->get_translations_for(_pos_in_text_ranges.min(),
                                                                        _pos_in_text_ranges.max());

  this->updated = true;
}
