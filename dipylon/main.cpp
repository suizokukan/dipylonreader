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
    main_splitter->show();

    return app.exec();
}
