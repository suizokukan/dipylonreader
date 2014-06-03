// http://qt-project.org/doc/qt-5/qtwidgets-mainwindows-application-example.html

#include <QApplication>

#include "qt/mainwindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(dipylon);

    QApplication app(argc, argv);
    app.setOrganizationName("QtProject");
    app.setApplicationName("Application Example");
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
