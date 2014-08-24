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

    ❏Dipylon❏ : qt/blockformat.cpp

    See blockformat.h for the documentation

    ____________________________________________________________________________

*******************************************************************************/

#include "qt/blockformat.h"

/*______________________________________________________________________________

        BlockFormat::constructor from a source string.

        See blockformat.h for a description of the BLOCKFORMAT_SRCSTRING_FORMAT
______________________________________________________________________________*/
BlockFormat::BlockFormat(const QString& source_string) {
  this->_internal_state = this->init_from_string(source_string);
  this->_well_initialized = (this->_internal_state == BlockFormat::INTERNALSTATE::OK);
}

/*______________________________________________________________________________

        BlockFormat::init_from_string() : initialize "this" from a source string.

        The function returns an "internal state". See blockformat.h for the
	available values.
______________________________________________________________________________*/
int BlockFormat::init_from_string(const QString& source_string) {
    this->_well_initialized = true;

    this->_repr = source_string;

    QStringList list_of_keywords = source_string.split(this->SEPARATOR);

    int res = BlockFormat::INTERNALSTATE::OK;

    for (auto &keyword : list_of_keywords) {
      // spaces are not taken in account :
      keyword.replace(" ", "");

      // alignment .............................................................
      if (keyword == "alignment:left") {
        this->_qtextblockformat.setAlignment(Qt::AlignLeft);
        continue;
      }

      if (keyword == "alignment:right") {
        this->_qtextblockformat.setAlignment(Qt::AlignRight);
        continue;
      }

      if (keyword == "alignment:hcenter") {
        this->_qtextblockformat.setAlignment(Qt::AlignHCenter);
        continue;
      }

      if (keyword == "alignment:justify") {
        this->_qtextblockformat.setAlignment(Qt::AlignJustify);
        continue;
      }

      res = BlockFormat::INTERNALSTATE::BADSRCSTRING_UNKNOWNKEYWORD;
      this->_well_initialized = false;
    }

    return res;
}
