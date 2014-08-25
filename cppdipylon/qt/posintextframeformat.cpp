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

    ❏Dipylon❏ : qt/positionintextframeformat.cpp

    See positionintextframeformat.h for the documentation

    ____________________________________________________________________________

*******************************************************************************/

#include "qt/posintextframeformat.h"

/*______________________________________________________________________________

        PosInTextFrameFormat::constructor from a source string.

        See positionintextframeformat.h for a description of the POSITIONINTEXTFRAMEFORMAT_SRCSTRING_FORMAT
______________________________________________________________________________*/
PosInTextFrameFormat::PosInTextFrameFormat(const QString& source_string) {
  this->_internal_state = this->init_from_string(source_string);
  this->_well_initialized = (this->_internal_state == PosInTextFrameFormat::INTERNALSTATE::OK);
}

/*______________________________________________________________________________

        PosInTextFrameFormat::init_from_string() : initialize "this" from a
                                                 source string.

        The function returns an "internal state". See positionintextframeformat.h for
        the available values.
______________________________________________________________________________*/
int PosInTextFrameFormat::init_from_string(const QString& source_string) {
    this->_well_initialized = true;

    this->_repr = source_string;

    QStringList list_of_keywords = source_string.split(this->SEPARATOR);

    int res = PosInTextFrameFormat::INTERNALSTATE::OK;

    for (auto &keyword : list_of_keywords) {
      // spaces are not taken in account :
      keyword.replace(" ", "");

      if( keyword.length() == 0) {
        continue;
      }

      if (keyword == "inflow") {
        this->_position = QTextFrameFormat::InFlow;
        continue;
      }

      if (keyword == "floatleft") {
        this->_position = QTextFrameFormat::FloatLeft;
        continue;
      }

      if (keyword == "floatright") {
        this->_position = QTextFrameFormat::FloatRight;
        continue;
      }

      this->_well_initialized = false;
      res = PosInTextFrameFormat::INTERNALSTATE::BADSRCSTRING_UNKNOWNKEYWORD;
    }

    return res;
}
