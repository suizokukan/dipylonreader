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

    ❏Dipylon❏ : qt/dipylonui.cpp

    More documentation in dipylonui.h .

*******************************************************************************/

#include "qt/dipylonui.h"

/*______________________________________________________________________________

        DipylonUI::DipylonUI : normal constructor
______________________________________________________________________________*/
DipylonUI::DipylonUI(int argv, char ** args) : QApplication(argv, args)
{
  qDebug() << "DipylonUI::DipylonUI : enter";
  this->set_the_ui();
  qDebug() << "DipylonUI::DipylonUI : exit";
}

/*______________________________________________________________________________

        DipylonUI::exec : public access to QApplication.exec()
______________________________________________________________________________*/
int DipylonUI::exec(void)
{
  qDebug() << "DipylonUI::exec : enter";
  return this->QApplication::exec();
}

/*______________________________________________________________________________

        DipylonUI::set_the_ui() : User Interface implementation.
______________________________________________________________________________*/
void DipylonUI::set_the_ui(void)
{
  qDebug() << "DipylonUI::set_the_ui : enter";

  // the desktop widget (also called the root window) :
  QDesktopWidget* desktop_widget = this->desktop();

  qDebug() << "DipylonUI::set_the_ui : #1";
  this->source_editor = SourceEditor();
  this->source_editor.init(&this->current_dipydoc);

  qDebug() << "DipylonUI::set_the_ui : #2";
  this->commentary_editor = CommentaryEditor();
  qDebug() << "DipylonUI::set_the_ui : #3";
  this->main_splitter = MainSplitter();
  qDebug() << "DipylonUI::set_the_ui : #4";
  this->main_splitter.addWidget(source_editor);
  this->main_splitter.addWidget(commentary_editor);
  qDebug() << "DipylonUI::set_the_ui : #5";
    /* ne pas régler la taille dans le constructeur : d'abord ajouter les widgets puis
       régler la taille : 

       Avec (500, 100) comme valeurs, il existe un rapport de 5 à 1 en taille.
       Deux nombres doivent être donnés (et pas un seul)
    */
  QList<int> main_splitter_heights;
  CORE DUMPEDmain_splitter_heights << 500 << 100;
  this->main_splitter.setSizes( {{500,100}} );
  qDebug() << "DipylonUI::set_the_ui : #6";
  this->main_splitter.show();
  qDebug() << "DipylonUI::set_the_ui : #7";

  
  //============================================================================
  // $$$ fake initialization $$$
  //============================================================================
  this->current_dipydoc = DipyDoc("../texts/Ovid_M_I_452_567/");
  //this->source_editor->setPlainText(this->current_dipydoc.text);
  qDebug() << "DipylonUI::set_the_ui : #8";
  QTextDocument* doc = this->source_editor->document();
  doc->setPlainText(this->current_dipydoc.text);
  QTextCursor cur = this->source_editor->textCursor();
  cur.insertText("aaa\nbbb");
  //cur.insertHtml("<b>CCC</b>");
  qDebug() << "nbr block=" << doc->blockCount();
  //this->source_editor->setDocument(&doc);
  qDebug() << "DipylonUI::set_the_ui : #9";
  // $$$ pas la bonne manière de le faire : cette fonction ne sert qu'à indiquer que
  // le programme n'est pas dans son état normal.
  // MAIS la manière normale (xxx->setCursor(yyy)) ne fonctionne pas...
  // $$$ this->setOverrideCursor(QCursor(QPixmap("cursor.png")));
  this->setOverrideCursor(QCursor(QPixmap(":/ressources/images/cursors/cursor.png")));
  qDebug() << "DipylonUI::set_the_ui : exit";
}
