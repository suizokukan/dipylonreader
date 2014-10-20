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

    ❏DipylonReader❏ : qt/scsplitter.cpp

    see scsplitter.h for the documentation

*******************************************************************************/

#include "qt/scsplitter.h"

/*______________________________________________________________________________

        SCSplitter::SCSplitter()

        SCSplitter constructor.

        Initialize (bool)_well_initialized .
______________________________________________________________________________*/
SCSplitter::SCSplitter(const QString& directoryName,
                       bool & _visible_toolbars,
                       QWidget *_parent) : QSplitter(_parent),
                                                     visible_toolbars(_visible_toolbars),
                                                     _well_initialized(false),
                                                     blocked_commentaries(false) {
  /*
    (1) loading the DipyDoc
  */
  bool loading_ok = true;

  #ifndef QT_NO_CURSOR
  QApplication::setOverrideCursor(Qt::WaitCursor);
  #endif

  this->dipydoc = DipyDoc(directoryName);

  if (this->dipydoc.well_initialized() == false) {
    // an error occurs :
    QMessageBox msgBox;
    msgBox.setText(tr("Unable to load any valid Dipydoc's document from <b>") + \
                   directoryName + "</b> ." + \
                   "<br/><br/>" + this->dipydoc.diagnosis() + \
                   "<br/><br/>" + tr("See more details below."));

    msgBox.setDetailedText("internal state = " + \
                           QString().setNum(this->dipydoc.internal_state()) + \
                           "\n\n" + \
                           this->dipydoc.err_messages.join("\n\n") + \
                           "\n\n\n*** internal debug message ***\n\n\n" + \
                           DebugMsg::messages.join("\n"));
    msgBox.exec();

    loading_ok = false;
  }

  #ifndef QT_NO_CURSOR
  QApplication::restoreOverrideCursor();
  #endif

  if (loading_ok == false) {
    this->_well_initialized = false;
    return;
  }

  /*
    (2) setting the splitter
  */
  QString splitter_name("mainwindow__splitter"+this->dipydoc.menu_name);
  this->setObjectName(splitter_name);
  this->setStyleSheet(QString("#%1::handle:vertical {height: 5px;}").arg(splitter_name));
  this->setOrientation(Qt::Vertical);
  this->setSizes(fixedparameters::default__editors_size_in_main_splitter);

  this->source_zone = new SourceZone(splitter_name,
                                     this->dipydoc,
                                     this->blocked_commentaries,
                                     this->visible_toolbars,
                                     this);
  this->commentary_zone = new CommentaryZone(splitter_name,
                                             this->dipydoc,
                                             this->blocked_commentaries,
                                             this);
  this->addWidget(this->source_zone);
  this->addWidget(this->commentary_zone);

  /*
    (3) signals
  */

  // (confer doc.) connection #C001
  QObject::connect(this->source_zone->editor,      &SourceEditor::signal__update_commentary_zone_content,
                   this->commentary_zone->editor,  &CommentaryEditor::update_content__translation_expected);

  // (confer doc.) connection #C002
  QObject::connect(this->source_zone,              &SourceZone::signal__hide_toolbar_in_the_commentary_zone,
                   this->commentary_zone->toolbar, &CommentaryToolBar::hide);

  // (confer doc.) connection #C003
  QObject::connect(this->source_zone,              &SourceZone::signal__show_toolbar_in_the_commentary_zone,
                   this->commentary_zone->toolbar, &CommentaryToolBar::show);

  // (confer doc.) connection #C004
  QObject::connect(this->source_zone,              &SourceZone::signal__set_zoom_value_in_commentary_editor,
                   this->commentary_zone->editor,  &TextEditor::set_zoom_value);

  // (confer doc.) connection #C006
  QObject::connect(this->source_zone,              &SourceZone::signal__in_commentary_editor_update_from_dipydoc_info,
                   this->commentary_zone->editor,  &CommentaryEditor::update_aspect_from_dipydoc_aspect_informations);

  // (confer doc.) connection #C007
  QObject::connect(this->source_zone,              &SourceZone::signal__update_commentary_zone_content,
                   this->commentary_zone->editor,  &CommentaryEditor::update_content__translation_expected);

  /*
    (4) zoom value of the current text
  */
  QSettings settings;
  settings.setValue(QString("text/%1/sourceeditor/zoomvalue").arg(this->dipydoc.qsettings_name),
                    this->source_zone->editor->zoom_value);
  settings.setValue(QString("text/%1/commentaryeditor/zoomvalue").arg(this->dipydoc.qsettings_name),
                    this->commentary_zone->editor->zoom_value);

  /*
    (5) setting this->_well_initialized
  */
  this->_well_initialized = true;
}

/*______________________________________________________________________________

        SCSplitter::well_initialized
______________________________________________________________________________*/
bool SCSplitter::well_initialized(void) {
  return this->_well_initialized;
}
