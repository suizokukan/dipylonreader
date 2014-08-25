######################################################################
# Dipylon project
######################################################################

TEMPLATE = app
TARGET = dipylon
INCLUDEPATH += .
RESOURCES        =  dipylon.qrc
TRANSLATIONS = dipylon_French.ts

# to get rid of the qDebug() messages, uncomment this line :
DEFINES += QT_NO_DEBUG_OUTPUT

# access to DipyDoc write functions :
#DEFINES += READANDWRITE

# some particularities bound to MXE/Qt :
DEFINES += CROSSCOMPILE_TO_WIN_USING_MXE

QT += widgets
QT += multimedia

# Input
HEADERS         +=  fixedparameters.h \
                    dipydoc/dipydoc.h \
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
                    pos/posintext2posinaudio.cpp \
                    pos/posinaudio2posintext.cpp \
                    pos/posinaudio/posinaudiorange.cpp \
                    pos/posintext/posintext2str.cpp \
                    pos/posintext/posintextranges.cpp \
                    pos/posintext/vectorposintextranges.cpp \
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

QMAKE_CFLAGS     += -std=c++11

QMAKE_CXXFLAGS   += -std=c++11

#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/application
#INSTALLS += target
