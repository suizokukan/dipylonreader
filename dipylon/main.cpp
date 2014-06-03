#include <QApplication>

#include "qt/mainwindow.h"

class DipylonUI {

private:
  // attributes used to initialize the QApplication constructor :
  int cmdline_argc = 0;
  char** cmdline_argv = nullptr;

  int* current_dipydoc = nullptr;

public:
      DipylonUI(int argc, char **argv);
      ~DipylonUI(void);
  int go(void);
};
DipylonUI::DipylonUI(int argc, char **argv) {
  this->cmdline_argc = argc;
  this->cmdline_argv = argv;
}
int DipylonUI::go(void) {
    QApplication app(this->cmdline_argc, this->cmdline_argv);
    app.setOrganizationName(" QtProject");
    app.setOrganizationDomain("94.23.197.37");
    app.setApplicationName("Dipylon");
    app.setApplicationVersion("0.1.9");
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
DipylonUI::~DipylonUI(void) {
  delete current_dipydoc;
}

int main(int argc, char **argv)
{
    Q_INIT_RESOURCE(dipylon);

    DipylonUI myapp(argc, argv);
    return myapp.go();
}
