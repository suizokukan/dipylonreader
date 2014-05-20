#include <QtWidgets>

#include <codeeditor.h>

int main(int argv, char **args)
{
    qDebug() << "ENTRY POINT\n";

    QApplication app(argv, args);

    CodeEditor editor;
    editor.setWindowTitle(QObject::tr("Code Editor Example"));
    editor.show();

    qDebug() << "EXIT POINT\n";

    return app.exec();
}
