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

    ❏Dipylon❏ : main.cpp

*******************************************************************************/
#include <QtWidgets>

#include "qt/sourceeditor.h"
#include "qt/commentaryeditor.h"
#include "qt/mainsplitter.h"

#include "dipydoc/dipydoc.h"

class DipylonUI : QApplication
{
    public:
        DipylonUI(int, char **);
        DipyDoc* current_dipydoc = 0;

        int exec(void);

    private:
        SourceEditor* source_editor = 0;
        CommentaryEditor *commentary_editor = 0;
        MainSplitter *main_splitter = 0;

        void set_the_ui(void);
};
DipylonUI::DipylonUI(int argv, char ** args) : QApplication(argv, args)
{
  this->set_the_ui();
}

int DipylonUI::exec(void)
{
  return this->QApplication::exec();
}

void DipylonUI::set_the_ui(void)
{
  delete this->source_editor;
  this->source_editor = new SourceEditor(this->current_dipydoc);

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
}

int main(int argv, char **args)
{
    qDebug() << "Dipylon : entry point\n";

    DipylonUI app(argv, args);

    return app.exec();
}
