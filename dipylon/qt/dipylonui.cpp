#include "qt/dipylonui.h"
#include "qt/mainwindow.h"
#include "dipydoc/dipydoc.h"

#include <QApplication>

DipylonUI::DipylonUI(int argc, char **argv) {
  this->cmdline_argc = argc;
  this->cmdline_argv = argv;
}

int DipylonUI::go(void) {
    QApplication app(this->cmdline_argc, this->cmdline_argv);
    app.setOrganizationName( this->organization_name );
    app.setOrganizationDomain( this->organization_domain );
    app.setApplicationName(this->application_name );
    app.setApplicationVersion( this->application_version );

    this->current_dipydoc = new DipyDoc();

    MainWindow mainWin(current_dipydoc);
    mainWin.show();
    return app.exec();
}

DipylonUI::~DipylonUI(void) {
  delete current_dipydoc;
}
