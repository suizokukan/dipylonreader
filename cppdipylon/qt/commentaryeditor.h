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

    ❏DipylonReader❏ : qt/commentaryeditor.h

    Zone where the annotations are displayed.

*******************************************************************************/

#ifndef CPPDIPYLON_QT_COMMENTARYEDITOR_H_
#define CPPDIPYLON_QT_COMMENTARYEDITOR_H_

#include <QTextEdit>

#include "debugmsg/debugmsg.h"
#include "dipydoc/dipydoc.h"
#include "pos/posintext/posintextranges.h"
#include "qt/readingmodes.h"
#include "qt/texteditor.h"

/*______________________________________________________________________________

  CommentaryEditor class
______________________________________________________________________________*/
class CommentaryEditor : public TextEditor {
friend class MainWindow;

    Q_OBJECT

 signals:
  void signal__close_the_current_dipydoc(void);
  void signal__open_a_new_dipydoc(void);

 public:
  explicit CommentaryEditor(const QString & splitter_name,
                            const DipyDoc * _dipydoc,
                            bool & _blocked_commentaries,
                            QWidget * _parent);

  void set_the_appearance(void);
  void set_the_text_formats(void);

 public slots:  //  NOLINT(whitespace/indent)
  void update_content__translation_expected(const PosInTextRanges&);
  void update_aspect_from_dipydoc_aspect_informations(void);
  void update_content__commentary_expected(const QString & textnote);

 private:
    const DipyDoc * dipydoc;
    // text formats, initialized by this->set_the_text_formats() :
    QTextCharFormat format_text = QTextCharFormat();

    bool & blocked_commentaries;
};

#endif  // CPPDIPYLON_QT_COMMENTARYEDITOR_H_
