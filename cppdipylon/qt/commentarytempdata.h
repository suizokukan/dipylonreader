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

    ❏DipylonReader❏ : qt/commentarytempdata.h

    * CommentaryTempData class

*******************************************************************************/

#ifndef CPPDIPYLON_QT_COMMENTARYTEMPDATA_H_
#define CPPDIPYLON_QT_COMMENTARYTEMPDATA_H_

#include <QObject>
#include <QPoint>
#include <QString>

#include "debugmsg/debugmsg.h"
#include "qt/sourceeditor.h"

/*______________________________________________________________________________

  CommentaryTempData class

  Object used to store (temporary) informations about the fragment of text 
  choosed by the user.

  Please use the informations stored inside ONLY IF updated is set to true.
_____________________________________________________________________________*/
struct CommentaryTempData : QObject {
    Q_OBJECT

 public:
  bool      updated = false;
  QPoint    xy;
  QString   text;

  SourceEditor * source_zone__editor = nullptr;

 public:
  CommentaryTempData(SourceEditor * _source_zone__editor,
                     QWidget      * _parent);

 public slots:  // NOLINT(whitespace/indent)
  void update(const PosInTextRanges& _pos_in_text_ranges);
};

#endif  // CPPDIPYLON_QT_COMMENTARYTEMPDATA_H_
