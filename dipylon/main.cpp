#include <QtWidgets>

#include <sourceeditor.h>
#include <commentaryeditor.h>
#include <mainsplitter.h>

int main(int argv, char **args)
{
    qDebug() << "Dipylon : entry point\n";

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
