######################################################################
# Dipylon project
######################################################################

TEMPLATE = app
TARGET = dipylon
INCLUDEPATH += .
RESOURCES        =  dipylon.qrc
TRANSLATIONS = dipylon_French.ts

#_______________________________________________________________________________
#
# compilation options : see dipylon.project for more informations
#
#_______________________________________________________________________________
DEFINES += READANDWRITE
DEFINES += ALLOW_LOADING_DIPYDOC_FROM_THE_COMMAND_LINE
DEFINES += ALLOW_SPLASHSCREEN

QT += widgets
QT += multimedia

# Input
HEADERS         +=  fixedparameters.h \
                    dipydoc/dipydoc.h \
                    dipydoc/dipydocnotes.h \
                    languages/languages.h \
                    languages/languagefromto.h \
                    pos/posintext2posinaudio.h \
                    pos/posinaudio2posintext.h \
                    pos/posinaudio/posinaudio.h \
                    pos/posinaudio/posinaudiorange.h \
                    pos/posintext/posintext.h \
                    pos/posintext/posintextranges.h \
                    pos/posintext/vectorposintextranges.h \
                    pos/posintext/posintext2str.h \
                    qt/arrowformat.h \
                    qt/blockformat.h \
                    qt/commentaryeditor.h \
                    qt/dipylonui.h \	
                    qt/mainwindow.h \
                    qt/posintextframeformat.h \
                    qt/sourceeditor.h \
                    qt/textformat.h

SOURCES         +=  main.cpp \
                    languages/languagefromto.cpp \
                    dipydoc/dipydoc.cpp \
                    dipydoc/dipydocnotes.cpp \
                    pos/posintext2posinaudio.cpp \
                    pos/posinaudio2posintext.cpp \
                    pos/posinaudio/posinaudiorange.cpp \
                    pos/posintext/posintext2str.cpp \
                    pos/posintext/posintextranges.cpp \
                    pos/posintext/vectorposintextranges.cpp \
                    qt/arrowformat.cpp \
                    qt/blockformat.cpp \
                    qt/commentaryeditor.cpp \
                    qt/dipylonui.cpp \
                    qt/mainwindow.cpp \
                    qt/posintextframeformat.cpp \
                    qt/sourceeditor.cpp \
                    qt/textformat.cpp

DESTDIR = build/
OBJECTS_DIR = build/
MOC_DIR = build/
RCC_DIR = build/
UI_DIR = build/

QMAKE_CFLAGS     += -std=c++1y -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wunused-value -Werror

QMAKE_CXXFLAGS   += -std=c++1y -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wunused-value -Werror

#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/application
#INSTALLS += target
