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

    ❏DipylonReader❏ : qt/textformat.cpp

    See textformat.h for the documentation

    ____________________________________________________________________________

*******************************************************************************/

#include "debugmsg/debugmsg.h"
#include "qt/textformat.h"

const QString TextFormat::SEPARATOR = ";";

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
  this->_well_initialized = true;

  this->_repr = source_string;

  QStringList list_of_keywords = source_string.split(this->SEPARATOR);

  int res = TextFormat::INTERNALSTATE::OK;

  for (auto &keyword : list_of_keywords) {
    /*
      A special case : "font-family" expects an argument which may have
      a space within like "Liberation Mono". So this special case is
      treated before the other ones.
    */
    if (keyword.contains("font-family")) {
      QString fontfamily = keyword.replace("font-family", "");
      fontfamily.replace(":", "");
      fontfamily = fontfamily.trimmed();
      this->_qtextcharformat.setFontFamily(fontfamily);
      continue;
    }

    // spaces are not taken in account :
    keyword.replace(" ", "");

    if (keyword.length() == 0) {
      continue;
    }

    /*
      background colors
    */
    // background color with hexadecimal value ?
    if (keyword.startsWith("background-color:#") == true) {
      QString str_value = keyword.right(keyword.length() - QString("background-color:#").length());
      bool ok;
      int value = str_value.toInt(&ok, 16);
      if (ok == true) {
        this->_qtextcharformat.setBackground(QBrush(static_cast<unsigned int>(value)));
      } else {
        res = TextFormat::INTERNALSTATE::WRONG_HEX_VALUE_FOR_BACKGROUND_COLORS;
        this->_well_initialized = false;
      }
      continue;
    }

    // background colors with a keyword like "black", ... ?
    if (keyword == "background-color:black") {
      this->_qtextcharformat.setBackground(QBrush(Qt::black));
      continue;
    }

    if (keyword == "background-color:blue") {
       this->_qtextcharformat.setBackground(QBrush(Qt::blue));
       continue;
    }

    if (keyword == "background-color:cyan") {
       this->_qtextcharformat.setBackground(QBrush(Qt::cyan));
       continue;
    }
    if (keyword == "background-color:gray") {
       this->_qtextcharformat.setBackground(QBrush(Qt::gray));
       continue;
    }
    if (keyword == "background-color:green") {
       this->_qtextcharformat.setBackground(QBrush(Qt::green));
       continue;
    }
    if (keyword == "background-color:magenta") {
       this->_qtextcharformat.setBackground(QBrush(Qt::magenta));
       continue;
    }
    if (keyword == "background-color:red") {
       this->_qtextcharformat.setBackground(QBrush(Qt::red));
       continue;
    }
    if (keyword == "background-color:white") {
       this->_qtextcharformat.setBackground(QBrush(Qt::white));
       continue;
    }
    if (keyword == "background-color:yellow") {
       this->_qtextcharformat.setBackground(QBrush(Qt::yellow));
       continue;
    }

    /*
       bold
    */
    if (keyword == "bold") {
       this->_qtextcharformat.setFontWeight(QFont::Bold);
       continue;
    }

    /*
       foreground colors
    */

    // foreground color with hexadecimal value ?
    if (keyword.startsWith("color:#") == true) {
      QString str_value = keyword.right(keyword.length() - QString("color:#").length());
      bool ok;
      int value = str_value.toInt(&ok, 16);
      if (ok == true) {
        this->_qtextcharformat.setForeground(QBrush(static_cast<unsigned int>(value)));
      } else {
        res = TextFormat::INTERNALSTATE::WRONG_HEX_VALUE_FOR_FOREGROUND_COLORS;
        this->_well_initialized = false;
      }
      continue;
    }

    if (keyword == "color:black") {
       this->_qtextcharformat.setForeground(QBrush(Qt::black));
       continue;
    }
    if (keyword == "color:blue") {
       this->_qtextcharformat.setForeground(QBrush(Qt::blue));
       continue;
    }
    if (keyword == "color:cyan") {
       this->_qtextcharformat.setForeground(QBrush(Qt::cyan));
       continue;
    }
    if (keyword == "color:gray") {
       this->_qtextcharformat.setForeground(QBrush(Qt::gray));
       continue;
    }
    if (keyword == "color:green") {
       this->_qtextcharformat.setForeground(QBrush(Qt::green));
       continue;
    }
    if (keyword == "color:magenta") {
       this->_qtextcharformat.setForeground(QBrush(Qt::magenta));
       continue;
    }
    if (keyword == "color:red") {
       this->_qtextcharformat.setForeground(QBrush(Qt::red));
       continue;
    }
    if (keyword == "color:white") {
       this->_qtextcharformat.setForeground(QBrush(Qt::white));
       continue;
    }
    if (keyword == "color:yellow") {
       this->_qtextcharformat.setForeground(QBrush(Qt::yellow));
       continue;
    }

    /*
      italic
    */
    if (keyword == "italic") {
       this->_qtextcharformat.setFontItalic(true);
       continue;
    }

    /*
      underline colors
    */
    // underline color with hexadecimal value ?
    if (keyword.startsWith("underlinecolor:#") == true) {
      QString str_value = keyword.right(keyword.length() - QString("underlinecolor:#").length());
      bool ok;
      int value = str_value.toInt(&ok, 16);
      if (ok == true) {
        this->_qtextcharformat.setUnderlineColor(static_cast<unsigned int>(value));
      } else {
        res = TextFormat::INTERNALSTATE::WRONG_HEX_VALUE_FOR_UNDERLINE_COLORS;
        this->_well_initialized = false;
      }
      continue;
    }

    if (keyword == "underlinecolor:black") {
       this->_qtextcharformat.setUnderlineColor(Qt::black);
       continue;
    }
    if (keyword == "underlinecolor:blue") {
       this->_qtextcharformat.setUnderlineColor(Qt::blue);
       continue;
    }
    if (keyword == "underlinecolor:cyan") {
       this->_qtextcharformat.setUnderlineColor(Qt::cyan);
       continue;
    }
    if (keyword == "underlinecolor:gray") {
       this->_qtextcharformat.setUnderlineColor(Qt::gray);
       continue;
    }
    if (keyword == "underlinecolor:green") {
       this->_qtextcharformat.setUnderlineColor(Qt::green);
       continue;
    }
    if (keyword == "underlinecolor:magenta") {
       this->_qtextcharformat.setUnderlineColor(Qt::magenta);
       continue;
    }
    if (keyword == "underlinecolor:red") {
       this->_qtextcharformat.setUnderlineColor(Qt::red);
       continue;
    }
    if (keyword == "underlinecolor:white") {
       this->_qtextcharformat.setUnderlineColor(Qt::white);
       continue;
    }
    if (keyword == "underlinecolor:yellow") {
       this->_qtextcharformat.setUnderlineColor(Qt::yellow);
       continue;
    }

    /*
       underline style
    */
    if (keyword == "underlinestyle=dashline") {
       this->_qtextcharformat.setFontUnderline(QTextCharFormat::DashUnderline);
       continue;
    }
    if (keyword == "underlinestyle=dotline") {
       this->_qtextcharformat.setFontUnderline(QTextCharFormat::DotLine);
       continue;
    }
    if (keyword == "underlinestyle=singleline") {
       this->_qtextcharformat.setFontUnderline(QTextCharFormat::SingleUnderline);
       continue;
    }
    if (keyword == "underlinestyle=waveline") {
       this->_qtextcharformat.setFontUnderline(QTextCharFormat::WaveUnderline);
       continue;
    }

    // DEBUG1 DebugMsg() << "TextFormat::init_from_string() : unknown keyword=" << keyword
    // DEBUG1                << "keyword.length()=" << keyword.length();

    res = TextFormat::INTERNALSTATE::BADSRCSTRING_UNKNOWNKEYWORD;
    this->_well_initialized = false;
  }

  return res;
}

/*______________________________________________________________________________

        TextFormat::modify_for_distant_appearance

        see A-mode for more details
______________________________________________________________________________*/
void TextFormat::modify_for_distant_appearance(void) {
  QBrush background = this->_qtextcharformat.background();
  int background_blue = background.color().blue() * 0.7;
  int background_green = background.color().green() * 0.7;
  int background_red = background.color().red() * 0.7;
  background.setColor(QColor(background_red,
                             background_green,
                             background_blue));
  this->_qtextcharformat.setBackground(background);
}

/*______________________________________________________________________________

        TextFormat::modify_for_family_appearance

        see A-mode for more details
______________________________________________________________________________*/
void TextFormat::modify_for_family_appearance(void) {
  QBrush background = this->_qtextcharformat.background();
  int background_blue = background.color().blue() * 0.9;
  int background_green = background.color().green() * 0.9;
  int background_red = background.color().red() * 0.9;
  background.setColor(QColor(background_red,
                             background_green,
                             background_blue));
  this->_qtextcharformat.setBackground(background);
}

/*______________________________________________________________________________

        TextFormat::modify_for_focused_appearance

        see A-mode for more details
______________________________________________________________________________*/
void TextFormat::modify_for_focused_appearance(void) {
  this->_qtextcharformat.setProperty(QTextFormat::FontWeight, QFont::Bold);
  this->_qtextcharformat.setProperty(QTextFormat::FontItalic, true);
  this->_qtextcharformat.setProperty(QTextFormat::TextUnderlineStyle, QTextCharFormat::SingleUnderline);
}
