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
SCSplitter::SCSplitter(const int index_in_scbar,
                       const QString& directoryName,
                       bool & _visible_toolbars,
                       QWidget *_parent) : QSplitter(_parent),
                                                     visible_toolbars(_visible_toolbars),
                                                     _well_initialized(false),
                                                     blocked_commentaries(false) {
  DebugMsg() << "SCSplitter::SCSplitter : entry point " << directoryName;

  /*
    (1) loading the DipyDoc
  */
  bool loading_ok = true;

  #ifndef QT_NO_CURSOR
  QApplication::setOverrideCursor(Qt::WaitCursor);
  #endif

  DebugMsg() << "SCSplitter::SCSplitter : reading DipyDoc...";
  this->dipydoc = new DipyDoc(directoryName);
  DebugMsg() << "SCSplitter::SCSplitter : ... DipyDoc read";

  if (this->dipydoc->well_initialized() == false) {
    // an error occurs :
    QMessageBox msgBox;
    msgBox.setText(tr("Unable to load any valid Dipydoc's document from <b>") + \
                   directoryName + "</b> ." + \
                   "<br/><br/>" + this->dipydoc->diagnosis() + \
                   "<br/><br/>" + tr("See more details below."));

    msgBox.setDetailedText("internal state = " + \
                           QString().setNum(this->dipydoc->internal_state()) + \
                           "\n\n" + \
                           this->dipydoc->err_messages.join("\n\n") + \
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
    DebugMsg() << "SCSplitter::SCSplitter : exit point on error" << directoryName;
    return;
  }

  /*
    (2) setting the splitter
  */
  this->setObjectName(this->get_object_name(index_in_scbar));
  DebugMsg() << "[SCSplitter::SCSplitter] this->setStyleSheet = " \
             << QString("#%1::handle:vertical {height: 5px;}").arg(this->objectName());
  this->setStyleSheet(QString("#%1::handle:vertical {height: 5px;}").arg(this->objectName()));
  this->setOrientation(Qt::Vertical);

  this->source_zone = new SourceZone(this->objectName(),
                                     this->dipydoc,
                                     this->blocked_commentaries,
                                     this->visible_toolbars,
                                     this->readingmode,
                                     this->readingmode_details,
                                     this);
  this->commentary_zone = new CommentaryZone(this->objectName(),
                                             this->dipydoc,
                                             this->blocked_commentaries,
                                             this);
  this->addWidget(this->source_zone);
  this->addWidget(this->commentary_zone);

  /*
    (3) settings' value for the current text; apply these values to te UI.
  */
  this->read_settings();

  this->setSizes(this->splittersizes);
  this->source_zone->editor->set_zoom_value(this->source_zone->editor->zoom_value);
  this->commentary_zone->editor->set_zoom_value(this->commentary_zone->editor->zoom_value);

  /*
    (4) signals
  */

  // connection #C001 (confer documentation)
  QObject::connect(this->source_zone->editor,      &SourceEditor::signal__update_commentary_zone_content,
                   this->commentary_zone->editor,  &CommentaryEditor::update_content__translation_expected);

  // connection #C002 (confer documentation)
  QObject::connect(this->source_zone,              &SourceZone::signal__set_zoom_value_in_commentary_editor,
                   this->commentary_zone->editor,  &TextEditor::set_zoom_value);

  // connection #C003 (confer documentation)
  QObject::connect(this->source_zone,              &SourceZone::signal__in_commentary_editor_update_from_dipydoc_info,
                   this->commentary_zone->editor,  &CommentaryEditor::update_aspect_from_dipydoc_aspect_informations);

  // connection #C004 (confer documentation)
  QObject::connect(this->source_zone,              &SourceZone::signal__update_commentary_zone_content,
                   this->commentary_zone->editor,  &CommentaryEditor::update_content__translation_expected);

  // connection #C005 (confer documentation)
  QObject::connect(this->source_zone,              &SourceZone::signal__update_icons,
                   this,                           &SCSplitter::update_icons);

  /*
    (5) update icons
  */
  this->update_icons();

  /*
    (6) setting this->_well_initialized
  */
  this->_well_initialized = true;

  DebugMsg() << "SCSplitter::SCSplitter : exit point" << directoryName;;
}

/*______________________________________________________________________________

        SCSplitter::~SCSplitter()

        SCSplitter destructor
______________________________________________________________________________*/
SCSplitter::~SCSplitter(void) {
  DebugMsg() << "~SCSplitter";
  delete this->dipydoc;
}

/*______________________________________________________________________________

        SCSplitter::get_object_name

        Return the internal name of the object.

        An index of the object in the TabBar object is used in order to
        distinguish the same DipyDoc opened several times.
______________________________________________________________________________*/
QString SCSplitter::get_object_name(const int index_in_scbar) const {
  return QString("mainwindow__scsplitter" + \
                 this->dipydoc->internal_name + \
                 QString().setNum(index_in_scbar));
}

/*______________________________________________________________________________

  SCSplitter::read_settings()

  Read the settings value from the settings' file.
________________________________________________________________________________*/
void SCSplitter::read_settings(void) {
  DebugMsg() << "SCSplitter::read_settings()";

  QSettings settings;
  this->source_zone->editor->zoom_value = \
    settings.value(QString("text/%1/sourceeditor/zoomvalue").arg(this->dipydoc->qsettings_name),
                   fixedparameters::default__zoom_value).toInt();

  this->commentary_zone->editor->zoom_value = \
    settings.value(QString("text/%1/commentaryeditor/zoomvalue").arg(this->dipydoc->qsettings_name),
                   fixedparameters::default__zoom_value).toInt();

  /*
    see SCSplitter::write_settings for the explanations.
  */
  this->splittersizes.clear();
  foreach(QVariant v,
          settings.value(QString("text/%1/splittersizes").arg(this->dipydoc->qsettings_name)).toList()) {
  this->splittersizes << v.toInt();
  }
}

/*______________________________________________________________________________

  SCSplitter::update_icons()

  Update the icons along the current Dipydoc and the reading mode.
________________________________________________________________________________*/
void SCSplitter::update_icons(void) {
  DebugMsg() << "SCSplitter::update_icons; visible_toolbars=" << this->visible_toolbars;

  if (this->visible_toolbars == false) {
    /*
      invisible toolbars :
    */
    this->source_zone->toolbar->hide();
    this->commentary_zone->toolbar->hide();
  } else {
    /*
       visible toolbars :
    */
    this->source_zone->toolbar->show();
    this->commentary_zone->toolbar->show();
  }

  this->source_zone->update_icons();
}

/*______________________________________________________________________________

        SCSplitter::well_initialized
______________________________________________________________________________*/
bool SCSplitter::well_initialized(void) const {
  return this->_well_initialized;
}

/*______________________________________________________________________________

  SCSplitter::write_settings()

  Write the settings specific to the DipyDoc linked to "this".
________________________________________________________________________________*/
void SCSplitter::write_settings(void) {
  DebugMsg() << "SCSplitter::write_settings()";

  QSettings settings;

  /*
    zoom value :
  */
  settings.setValue(QString("text/%1/sourceeditor/zoomvalue").arg(this->dipydoc->qsettings_name),
                    this->source_zone->editor->zoom_value);
  settings.setValue(QString("text/%1/commentaryeditor/zoomvalue").arg(this->dipydoc->qsettings_name),
                    this->commentary_zone->editor->zoom_value);
  /*
    splitter's sizes :

    About the trick used here :
      The normal way to store a QList<int> is described here [1] and here [2] but this
    method leads to difficulties, at least on Linux system. Hence this work around
    described here [3].

      [1] http://qt-project.org/doc/qt-5/qsettings.html#details
      [2] http://stackoverflow.com/questions/2452893/save-qlistint-to-qsettings
      [3] http://stackoverflow.com/questions/21923016
  */
  QVariantList splittersizes_variant;
  for (int & v : this->sizes()) {
    splittersizes_variant << v;
  }
  settings.setValue(QString("text/%1/splittersizes").arg(this->dipydoc->qsettings_name),
                    splittersizes_variant);
}
