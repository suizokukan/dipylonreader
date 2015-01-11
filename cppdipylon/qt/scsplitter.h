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

    ❏DipylonReader❏ : qt/scsplitter.h

    * SCSplitter class (Source and Commentary Splitter)

*******************************************************************************/

#ifndef CPPDIPYLON_QT_SCSPLITTER_H_
#define CPPDIPYLON_QT_SCSPLITTER_H_

#include <QApplication>
#include <QMessageBox>
#include <QMetaType>
#include <QPoint>
#include <QSettings>
#include <QSplitter>
#include <QString>

#include "debugmsg/debugmsg.h"
#include "dipydoc/dipydoc.h"
#include "pos/posintext/posintextranges.h"
#include "qt/commentaryzone.h"
#include "qt/popupmessage.h"
#include "qt/sourcezone.h"

/*______________________________________________________________________________

  SCSplitter class

  Splitter bewteen a SourceZone object and a CommentaryZone object.
______________________________________________________________________________*/
class SCSplitter : public QSplitter {
friend class MainWindow;

    Q_OBJECT

 signals:
  void               signal__close_the_current_dipydoc(void);
  void               signal__open_a_new_dipydoc(void);

 private:
  bool &             visible_toolbars;
  bool               _well_initialized = false;               // object state
  bool               blocked_commentaries = false;
  DipyDoc *          dipydoc;
  SourceZone*        source_zone = nullptr;            // (ui) source zone
  CommentaryZone*    commentary_zone = nullptr;    // (ui) commentary zone
  ReadingMode        readingmode = READINGMODE::READINGMODE_UNDEFINED;
  ReadingModeDetails readingmode_details = READINGMODEDETAILS::READINGMODEDETAIL_UNDEFINED;
  QList<int> splittersizes = fixedparameters::default__editors_size_in_main_splitter;

  PopupMessage*      popup_message = nullptr;

  void               read_settings(void);
  void               write_settings(void);

 private slots:  // NOLINT(whitespace/indent)
  void              update_icons(void);
  void              update_content__popuptranslation_expected(const PosInTextRanges& posintext);

 public:
            explicit SCSplitter(const int index_in_scbar,
                                const QString& directoryName,
                                bool & _visible_toolbars,
                                QWidget *_parent);
                    ~SCSplitter(void);
  bool               well_initialized(void) const;
  QString            get_object_name(const int index_in_scbar) const;
};

#endif  // CPPDIPYLON_QT_SCSPLITTER_H_
