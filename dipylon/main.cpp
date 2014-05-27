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

#include <unordered_map>

#include "posranges.h"

/*
class PosRanges2Str
{
    public:
        PosRanges2Str(int length);
        int add(const QString&, const QString&);
        int internal_state(void);
        bool well_initialized(void);

    private:
        int _internal_state;
        bool _well_initialized;
        std::unordered_map<PosRanges, QString, PosRangesHasher> data;

        const int INTERNALSTATE_OK = 0;
};
PosRanges2Str::PosRanges2Str(int length)
{
  // empty hash map, everything's ok :
  this->_well_initialized = true;
  this->_internal_state = this->INTERNALSTATE_OK;
  this->data = std::unordered_map<PosRanges, QString, PosRangesHasher>(length);
}
int PosRanges2Str::add(const QString& key, const QString& value)
{
  // PosRanges object corresponding the QString key :
  PosRanges posranges_key = PosRanges(key);
  this->data[posranges_key] = value;
  return this->_internal_state;
}
int PosRanges2Str::internal_state(void)
{
  return this->_internal_state;
}
bool PosRanges2Str::well_initialized(void)
{
  return this->_well_initialized;
}*/

int main(int argv, char **args)
{
    qDebug() << "Dipylon : entry point\n";

    //std::unordered_map<PosRanges, QString, PosRangesHasher> m;
    //m.insert[ {{ {1,2}, {3,6} }} ] =  QString("abc");
    /*
    std::unordered_map<PosRanges, std::string, PosRangesHasher> m;
    PosRanges posranges("12-13");
    m[ posranges ] =  "abc";
    */

    /*PosRanges2Str posranges2str = PosRanges2Str(1000);
    QString q1("89…91+101…105+1000…1001");
    QString& qq1 = q1;
    QString q2("abc");
    QString& qq2 = q2;
    posranges2str.add( qq1, qq2 );
    */

    /*
    std::unordered_map<PosRanges, std::string, PosRangesHasher> m6 = {
    { {{ {1,2}, {3,4} },}, "example1"},
    { {{ {1,2}, {3,5} },}, "example2"},
    };
    */

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
