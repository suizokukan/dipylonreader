#ifndef DIPYLONUI_H
#define DIPYLONUI_H

#include "dipydoc/dipydoc.h"

#include <QString>

class DipylonUI {

private:
  // attributes used to initialize the QApplication constructor :
  int cmdline_argc = 0;
  char** cmdline_argv = nullptr;

  // current document displayed in the source zone :
  DipyDoc* current_dipydoc = nullptr;

  /* 
        data used to initialize the QApplication object.

        see http://qt-project.org/doc/qt-5/qcoreapplication.html
  */
  const QString organization_name = QString("suizokukan's factory");
  const QString organization_domain = QString("94.23.197.37");
  const QString application_name = QString("Dipylon");
  const QString application_version = QString("0.1.9");

public:
      DipylonUI(int argc, char **argv);
      ~DipylonUI(void);
  int go(void);
};

#endif
