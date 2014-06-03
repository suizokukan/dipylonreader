#include "qt/dipylonui.h"
#include <QApplication>

int main(int argc, char **argv)
{
    Q_INIT_RESOURCE(dipylon);

    DipylonUI myapp(argc, argv);
    return myapp.go();
}
