######################################################################
# DipylonReader project : Linux > Linux
######################################################################

TEMPLATE = app
TARGET = dipylonreader
INCLUDEPATH += .

QT += widgets

# Input
HEADERS         +=  ./fixedparameters.h
HEADER          +=  ./m1.h

SOURCES         +=  ./main.cpp
SOURCES         +=  ./m1.cpp

DESTDIR = build/
OBJECTS_DIR = build/
MOC_DIR = build/
RCC_DIR = build/
UI_DIR = build/

QMAKE_CFLAGS     += -std=c++1y -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wunused-value -Werror -fdiagnostics-color=auto

QMAKE_CXXFLAGS   += -std=c++1y -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wunused-value -Werror -fdiagnostics-color=auto

#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/application
#INSTALLS += target
