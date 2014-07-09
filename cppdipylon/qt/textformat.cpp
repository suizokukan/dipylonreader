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

    ❏Dipylon❏ : qt/textformat.cpp

    See textformat.h for the documentation

    ____________________________________________________________________________

*******************************************************************************/

#include "textformat.h"

/*______________________________________________________________________________

        TextFormat::constructor from a source string.

        See textformat.h for a description of the TEXTFORMAT_SRCSTRING_FORMAT
______________________________________________________________________________*/
TextFormat::TextFormat(const QString& source_string) {
  this->_internal_state = this->init_from_string(source_string);
  this->_well_initialized = (this->_internal_state == TextFormat::INTERNALSTATE::OK);
}

/*______________________________________________________________________________

        TextFormat::init_from_string() : initialize "this" from a source string.

		The function returns an "internal state". See textformat.h for the
		available values.
______________________________________________________________________________*/
int TextFormat::init_from_string(const QString& source_string) {

    QStringList list_of_keywords = source_string.split(this->SEPARATOR);

    int res = TextFormat::INTERNALSTATE::OK;

    for( auto &keyword : list_of_keywords) {

      // background colors .....................................................
      if( keyword == "background=black") {
        this->qtextcharformat.setBackground( QBrush(Qt::black) );
        continue;
      }

      if (keyword == "background=blue") {
         this->qtextcharformat.setBackground( QBrush(Qt::blue) );
         continue;
      }

      if (keyword == "background=cyan") {
         this->qtextcharformat.setBackground( QBrush(Qt::cyan) );
         continue;
      }
      if (keyword == "background=gray") {
         this->qtextcharformat.setBackground( QBrush(Qt::gray) );
         continue;
      }
      if (keyword == "background=green") {
         this->qtextcharformat.setBackground( QBrush(Qt::green) );
         continue;
      }
      if (keyword == "background=magenta") {
         this->qtextcharformat.setBackground( QBrush(Qt::magenta) );
         continue;
      }
      if (keyword == "background=red") {
         this->qtextcharformat.setBackground( QBrush(Qt::red) );
         continue;
      }
      if (keyword == "background=white") {
         this->qtextcharformat.setBackground( QBrush(Qt::white) );
         continue;
      }
      if (keyword == "background=yellow") {
         this->qtextcharformat.setBackground( QBrush(Qt::yellow) );
         continue;
      }

      // bold ..................................................................
      if (keyword == "italic") {
         this->qtextcharformat.setFontWeight(QFont::Bold);
         continue;
      }

      // foreground colors .....................................................
      if (keyword == "foreground=black") {
         this->qtextcharformat.setForeground( QBrush(Qt::black) );
         continue;
      }
      if (keyword == "foreground=blue") {
         this->qtextcharformat.setForeground( QBrush(Qt::blue) );
         continue;
      }
      if (keyword == "foreground=cyan") {
         this->qtextcharformat.setForeground( QBrush(Qt::cyan) );
         continue;
      }
      if (keyword == "foreground=gray") {
         this->qtextcharformat.setForeground( QBrush(Qt::gray) );
         continue;
      }
      if (keyword == "foreground=green") {
         this->qtextcharformat.setForeground( QBrush(Qt::green) );
         continue;
      }
      if (keyword == "foreground=magenta") {
         this->qtextcharformat.setForeground( QBrush(Qt::magenta) );
         continue;
      }
      if (keyword == "foreground=red") {
         this->qtextcharformat.setForeground( QBrush(Qt::red) );
         continue;
      }
      if (keyword == "foreground=white") {
         this->qtextcharformat.setForeground( QBrush(Qt::white) );
         continue;
      }
      if (keyword == "foreground=yellow") {
         this->qtextcharformat.setForeground( QBrush(Qt::yellow) );
         continue;
      }

      // italic ................................................................
      if (keyword == "italic") {
         this->qtextcharformat.setFontItalic(true);
         continue;
      }

      // underline colors ......................................................
      if (keyword == "underlinecolor=black") {
         this->qtextcharformat.setUnderlineColor( Qt::black );
         continue;
      }
      if (keyword == "underlinecolor=blue") {
         this->qtextcharformat.setUnderlineColor( Qt::blue );
         continue;
      }
      if (keyword == "underlinecolor=cyan") {
         this->qtextcharformat.setUnderlineColor( Qt::cyan );
         continue;
      }
      if (keyword == "underlinecolor=gray") {
         this->qtextcharformat.setUnderlineColor( Qt::gray );
         continue;
      }
      if (keyword == "underlinecolor=green") {
         this->qtextcharformat.setUnderlineColor( Qt::green );
         continue;
      }
      if (keyword == "underlinecolor=magenta") {
         this->qtextcharformat.setUnderlineColor( Qt::magenta );
         continue;
      }
      if (keyword == "underlinecolor=red") {
         this->qtextcharformat.setUnderlineColor( Qt::red );
         continue;
      }
      if (keyword == "underlinecolor=white") {
         this->qtextcharformat.setUnderlineColor( Qt::white );
         continue;
      }
      if (keyword == "underlinecolor=yellow") {
         this->qtextcharformat.setUnderlineColor( Qt::yellow );
         continue;
      }

      // underline style .......................................................
      if (keyword == "underlinestyle=dashline") {
         this->qtextcharformat.setFontUnderline(QTextCharFormat::DashUnderline);
         continue;
      }
      if (keyword == "underlinestyle=dotline") {
         this->qtextcharformat.setFontUnderline(QTextCharFormat::DotLine);
         continue;
      }
      if (keyword == "underlinestyle=singleline") {
         this->qtextcharformat.setFontUnderline(QTextCharFormat::SingleUnderline);
         continue;
      }
      if (keyword == "underlinestyle=waveline") {
         this->qtextcharformat.setFontUnderline(QTextCharFormat::WaveUnderline);
         continue;
      }

      res = TextFormat::INTERNALSTATE::BADSRCSTRING_UNKNOWNKEYWORD;
    }

    return res;
}
