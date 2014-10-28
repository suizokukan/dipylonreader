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

    ❏DipylonReader❏ : qt/arrowformat.cpp

    See arrowformat.h for the documentation

    ____________________________________________________________________________

*******************************************************************************/

#include "qt/arrowformat.h"
#include "debugmsg/debugmsg.h"

const QString ArrowFormat::SEPARATOR = ";";

/*______________________________________________________________________________

        ArrowFormat::constructor from a source string.

        See arrowformat.h for a description of the ARROWFORMAT_SRCSTRING_FORMAT
______________________________________________________________________________*/
ArrowFormat::ArrowFormat(const QString& source_string) {
  this->_internal_state = this->init_from_string(source_string);
  this->_well_initialized = (this->_internal_state == ArrowFormat::INTERNALSTATE::OK);
}

/*______________________________________________________________________________

        ArrowFormat::init_from_string() : initialize "this" from a source string.

        The function returns an "internal state". See arrowformat.h for the
	available values.
______________________________________________________________________________*/
int ArrowFormat::init_from_string(const QString& source_string) {
  this->_repr = source_string;

  QStringList list_of_keywords = source_string.split(this->SEPARATOR);

  int res = ArrowFormat::INTERNALSTATE::OK;

  for (auto &keyword : list_of_keywords) {
    // spaces are not taken in account :
    keyword.replace(" ", "");

    if (keyword.length() == 0) {
      continue;
    }

    /*
      thickness
    */
    if (keyword.startsWith("thickness:") == true) {
      QString str_value = keyword.right(keyword.length() - QString("thickness:").length());
      bool ok;
      int value = str_value.toInt(&ok, 10);
      if ((ok == true) && (value > 0)) {
        this->_thickness = value;
      } else {
        res = ArrowFormat::INTERNALSTATE::WRONG_DECIMAL_VALUE_FOR_THICKNESS;
        this->_well_initialized = false;
      }
      continue;
    }

    /*
      main color
    */
    // main color with hexadecimal value ?
    if (keyword.startsWith("main-color:#") == true) {
      QString str_value = keyword.right(keyword.length() - QString("main-color:#").length());
      bool ok;
      int value = str_value.toInt(&ok, 16);
      if (ok == true) {
        this->_maincolor = QColor(static_cast<unsigned int>(value));
      } else {
        res = ArrowFormat::INTERNALSTATE::WRONG_HEX_VALUE_FOR_MAIN_COLOR;
        this->_well_initialized = false;
      }
      continue;
    }
    // main colors with a keyword like "black", ... ?
    if (keyword == "main-color:black")   { this->_maincolor = QColor(Qt::black);   continue;  }
    if (keyword == "main-color:blue")    { this->_maincolor = QColor(Qt::blue);    continue;  }
    if (keyword == "main-color:cyan")    { this->_maincolor = QColor(Qt::cyan);    continue;  }
    if (keyword == "main-color:gray")    { this->_maincolor = QColor(Qt::gray);    continue;  }
    if (keyword == "main-color:green")   { this->_maincolor = QColor(Qt::green);   continue;  }
    if (keyword == "main-color:magenta") { this->_maincolor = QColor(Qt::magenta); continue;  }
    if (keyword == "main-color:red")     { this->_maincolor = QColor(Qt::red);     continue;  }
    if (keyword == "main-color:white")   { this->_maincolor = QColor(Qt::white);   continue;  }
    if (keyword == "main-color:yellow")  { this->_maincolor = QColor(Qt::yellow);  continue;  }

    /*
      start color
    */
    // start color with hexadecimal value ?
    if (keyword.startsWith("start-color:#") == true) {
      QString str_value = keyword.right(keyword.length() - QString("start-color:#").length());
      bool ok;
      int value = str_value.toInt(&ok, 16);
      if (ok == true) {
        this->_startcolor = QColor(static_cast<unsigned int>(value));
      } else {
        res = ArrowFormat::INTERNALSTATE::WRONG_HEX_VALUE_FOR_START_COLOR;
        this->_well_initialized = false;
      }
      continue;
    }
    // start colors with a keyword like "black", ... ?
    if (keyword == "start-color:black")   { this->_startcolor = QColor(Qt::black);   continue;  }
    if (keyword == "start-color:blue")    { this->_startcolor = QColor(Qt::blue);    continue;  }
    if (keyword == "start-color:cyan")    { this->_startcolor = QColor(Qt::cyan);    continue;  }
    if (keyword == "start-color:gray")    { this->_startcolor = QColor(Qt::gray);    continue;  }
    if (keyword == "start-color:green")   { this->_startcolor = QColor(Qt::green);   continue;  }
    if (keyword == "start-color:magenta") { this->_startcolor = QColor(Qt::magenta); continue;  }
    if (keyword == "start-color:red")     { this->_startcolor = QColor(Qt::red);     continue;  }
    if (keyword == "start-color:white")   { this->_startcolor = QColor(Qt::white);   continue;  }
    if (keyword == "start-color:yellow")  { this->_startcolor = QColor(Qt::yellow);  continue;  }

    /*
      end color
    */
    // end color with hexadecimal value ?
    if (keyword.endsWith("end-color:#") == true) {
      QString str_value = keyword.right(keyword.length() - QString("end-color:#").length());
      bool ok;
      int value = str_value.toInt(&ok, 16);
      if (ok == true) {
        this->_endcolor = QColor(static_cast<unsigned int>(value));
      } else {
        res = ArrowFormat::INTERNALSTATE::WRONG_HEX_VALUE_FOR_END_COLOR;
        this->_well_initialized = false;
      }
      continue;
    }
    // end colors with a keyword like "black", ... ?
    if (keyword == "end-color:black")   { this->_endcolor = QColor(Qt::black);   continue;  }
    if (keyword == "end-color:blue")    { this->_endcolor = QColor(Qt::blue);    continue;  }
    if (keyword == "end-color:cyan")    { this->_endcolor = QColor(Qt::cyan);    continue;  }
    if (keyword == "end-color:gray")    { this->_endcolor = QColor(Qt::gray);    continue;  }
    if (keyword == "end-color:green")   { this->_endcolor = QColor(Qt::green);   continue;  }
    if (keyword == "end-color:magenta") { this->_endcolor = QColor(Qt::magenta); continue;  }
    if (keyword == "end-color:red")     { this->_endcolor = QColor(Qt::red);     continue;  }
    if (keyword == "end-color:white")   { this->_endcolor = QColor(Qt::white);   continue;  }
    if (keyword == "end-color:yellow")  { this->_endcolor = QColor(Qt::yellow);  continue;  }

    DebugMsg() << "ArrowFormat::init_from_string(); unknown keyword=" << keyword;
    res = ArrowFormat::INTERNALSTATE::BADSRCSTRING_UNKNOWNKEYWORD;
    this->_well_initialized = false;
  }

  /*
    this->_*_qpen initialization :
  */
  this->_body_qpen = QPen(QBrush(this->_maincolor),
                          this->_thickness,
                          Qt::SolidLine,
                          Qt::SquareCap,
                          Qt::BevelJoin);

  this->_start_qpen = QPen(QBrush(this->_startcolor),
                           this->_thickness,
                           Qt::SolidLine,
                           Qt::SquareCap,
                           Qt::BevelJoin);

  this->_end_qpen = QPen(QBrush(this->_endcolor),
                         this->_thickness,
                         Qt::SolidLine,
                         Qt::SquareCap,
                         Qt::BevelJoin);

  return res;
}

/*______________________________________________________________________________

        ArrowFormat::body_qpen
______________________________________________________________________________*/
const QPen& ArrowFormat::body_qpen(void) const {
  return this->_body_qpen;
}

/*______________________________________________________________________________

        ArrowFormat::end_qpen
______________________________________________________________________________*/
const QPen& ArrowFormat::end_qpen(void) const {
  return this->_end_qpen;
}

/*______________________________________________________________________________

        ArrowFormat::start_qpen
______________________________________________________________________________*/
const QPen& ArrowFormat::start_qpen(void) const {
  return this->_start_qpen;
}
