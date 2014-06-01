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
  this->set_the_ui();
}

/*______________________________________________________________________________

        DipylonUI::exec : public access to QApplication.exec()
______________________________________________________________________________*/
int DipylonUI::exec(void)
{
  return this->QApplication::exec();
}

/*______________________________________________________________________________

        DipylonUI::set_the_ui() : User Interface implementation.
______________________________________________________________________________*/
void DipylonUI::set_the_ui(void)
{
  qDebug() << "DipylonUI::set_the_ui";

  // the desktop widget (also called the root window) :
  QDesktopWidget* desktop_widget = this->desktop();

  delete this->source_editor;
  this->source_editor = new SourceEditor(desktop_widget, &(this->current_dipydoc));

  delete this->commentary_editor;
  this->commentary_editor = new CommentaryEditor;

  delete this->main_splitter;
  this->main_splitter = new MainSplitter;

  this->main_splitter->addWidget(source_editor);
  this->main_splitter->addWidget(commentary_editor);

    /* ne pas régler la taille dans le constructeur : d'abord ajouter les widgets puis
       régler la taille : 

       Avec (500, 100) comme valeurs, il existe un rapport de 5 à 1 en taille.
       Deux nombres doivent être donnés (et pas un seul)
    */
  //QList<int> main_splitter_heights;
  //main_splitter_heights << 500 << 100;
  this->main_splitter->setSizes( {{500,100}} );

  this->main_splitter->show();

  //============================================================================
  // $$$ fake initialization $$$
  //============================================================================
  this->current_dipydoc = DipyDoc("../texts/Ovid_M_I_452_567/");
  this->source_editor->setPlainText(this->current_dipydoc.text);

  // $$$ pas la bonne manière de le faire : cette fonction ne sert qu'à indiquer que
  // le programme n'est pas dans son état normal.
  // MAIS la manière normale (xxx->setCursor(yyy)) ne fonctionne pas...
  // $$$ this->setOverrideCursor(QCursor(QPixmap("cursor.png")));
  this->setOverrideCursor(QCursor(QPixmap(":/ressources/images/cursors/cursor.png")));
}
