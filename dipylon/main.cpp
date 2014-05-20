#include <QtWidgets>

#include <sourceeditor.h>
#include <commentaryeditor.h>

int main(int argv, char **args)
{
    qDebug() << "Dipylon : entry point\n";

    QApplication app(argv, args);

    SourceEditor src_editor;
    src_editor.setWindowTitle(QObject::tr("source editor"));
    src_editor.show();

    CommentaryEditor com_editor;
    com_editor.setWindowTitle(QObject::tr("commentary editor"));
    com_editor.show();

    return app.exec();
}
