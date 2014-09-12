######################################################################
# Dipylon project : .pro file for Windows/32 bits/static with MXE
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
DEFINES += CROSSCOMPILE_TO_WIN_USING_MXE
DEFINES += COMPILE_TO_32BITS_ARCHITECTURE
DEFINES += ALLOW_RESIZING_THE_MAINWINDOW
DEFINES += ALLOW_MOVING_THE_MAINWINDOW
DEFINES += ALLOW_SPLASHSCREEN
DEFINES += ALLOW_MAXIMIZE_MAINWINDOW
DEFINES += MAXIMIZE_MAINWINDOW_TRUE_METHOD

#_______________________________________________________________________________
#
# add this line if you want to see qDebug() messages
#_______________________________________________________________________________
CONFIG += console



QT += widgets
QT += multimedia

# on Windows, in order to use QMediaPlayer, add the following line :
# (see http://lists.gnu.org/archive/html/mingw-cross-env-list/2013-06/msg00027.html)
QTPLUGIN += dsengine qtmedia_audioengine

# Input
HEADERS         +=  fixedparameters.h \
                    debugmsg/debugmsg.h \
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
                    debugmsg/debugmsg.cpp \
                    dipydoc/dipydoc.cpp \
                    dipydoc/dipydocnotes.cpp \
                    languages/languagefromto.cpp \
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

#_______________________________________________________________________________
#
# .rc file used to add the desktop icon to the application
#
# see http://qt-project.org/doc/qt-5/appicon.html
#_______________________________________________________________________________
RC_FILE = dipylon.rc



QMAKE_CFLAGS     += -std=c++1y -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wunused-value

QMAKE_CXXFLAGS   += -std=c++1y -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wunused-value

#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/application
#INSTALLS += target
