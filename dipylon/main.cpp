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

#include "pos2str.h"

#include <typeinfo>  //for 'typeid'

int main(int argv, char **args)
{
    qDebug() << "Dipylon : entry point\n";

    Pos2Str m = {
      { {{ {1,2}, {3,4} },}, QString("example1")},
        { {{ {1,2}, {3,5} },}, QString("example2")},
        { {{ {1,2}, {3,8} },}, QString("example3")},
    };
    qDebug() << "map.size=" << m.size();
    qDebug() << m[{{ {1,2}, {3,5} }}];
    m[{{ {1,2}, {3,9} }}] = QString("example4");
    qDebug() << "map.size=" << m.size();
    qDebug() << m[{{ {1,2}, {3,9} }}];

    if( m[{{ {1,2}, {3,9} }}] == QString("example4") )
      {
        qDebug() << "#1 !!!";
      }

    if( m[{{ {1,2}, {3,9} }}] == "example4" )
      {
        qDebug() << "#1 !!!";
      }

    QApplication app(argv, args);

    SourceEditor *src_editor = new SourceEditor;
    CommentaryEditor *com_editor = new CommentaryEditor;

    MainSplitter *main_splitter = new MainSplitter;
    main_splitter->addWidget(src_editor);
    main_splitter->addWidget(com_editor);

    /* ne pas régler la taille dans le constructeur : d'abord ajouter les widgets puis
       régler la taille : 

       Avec (500, 100) comme valeurs, il existe un rapport de 5 à 1 en taille.
       Deux nombres doivent être donnés (et pas un seul)
    */
    QList<int> mainsplitter_heights;
    mainsplitter_heights << 500 << 100;
    main_splitter->setSizes( mainsplitter_heights );

    //__________________________________________________________________________
    QFile src_file("dyptexts/Ovid_M_I_452_567/text");
    /*
      à propos du chemin :
        QFile expects the file separator to be '/' regardless of operating system. 
        (from http://qt-project.org/doc/qt-5/qfile.html)

      le codec : setCodec
     */
    src_file.open( QIODevice::ReadOnly | QIODevice::Text );
    QTextStream in(&src_file);
    in.setCodec("UTF-8");
    QString src = in.readAll();
    src_editor->setPlainText(src);

    //__________________________________________________________________________
    main_splitter->show();

    //

    return app.exec();
}
