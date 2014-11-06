######################################################################
# DipylonReader project : .pro file for Windows/32 bits/static with MXE
######################################################################

TEMPLATE = app
TARGET = dipylonreader
INCLUDEPATH += .
RESOURCES        =  dipylonreader.qrc
TRANSLATIONS = dipylonreader_French.ts

#_______________________________________________________________________________
#
# compilation options : see dipylonreader.project for more informations
#
#_______________________________________________________________________________
DEFINES += ALLOW_MAXIMIZE_MAINWINDOW
DEFINES += ALLOW_MOVING_THE_MAINWINDOW
DEFINES += ALLOW_RESIZING_THE_MAINWINDOW
DEFINES += ALLOW_SPLASHSCREEN_AT_START
DEFINES += COMPILE_TO_32BITS_ARCHITECTURE
DEFINES += DEBUG_MESSAGES_TO_CERR
DEFINES += MENUACCESS_TO_INTERNAL_MESSAGES
DEFINES += DOWNLOAD_MP3_VERSION_OF_DIPYDOCS
DEFINES += MAXIMIZE_MAINWINDOW_TRUE_METHOD
DEFINES += NO_MAIN_POPUPMENU
DEFINES += STORE_DEBUG_MESSAGES
DEFINES += QT_NO_DEBUG_OUTPUT

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
HEADERS         +=  ./fixedparameters.h \
                    debugmsg/debugmsg.h \
                    dipydoc/arrowtarget.h \
                    dipydoc/dipydoc.h \
                    dipydoc/notes.h \
                    dipydoc/syntagmas.h \
                    dipydoc/menunames.h \
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
                    qt/commentarytoolbar.h \
                    qt/commentaryzone.h \
                    qt/downloaddemodipydocs.h \
                    qt/icons.h \	
                    qt/mainwindow.h \
                    qt/posintextframeformat.h \
                    qt/presentationscreen.h \
                    qt/readingmodes.h \
                    qt/scsplitter.h \
                    qt/sourceeditor.h \ 
                    qt/sourcetoolbar.h \
                    qt/sourcezone.h \  
                    qt/sctabs.h \
                    qt/texteditor.h \
                    qt/textformat.h \
                    qt/ui.h


SOURCES         +=  ./main.cpp \
                    debugmsg/debugmsg.cpp \
                    dipydoc/dipydoc.cpp \
                    dipydoc/notes.cpp \
                    dipydoc/syntagmas.cpp \
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
                    qt/commentarytoolbar.cpp \
                    qt/commentaryzone.cpp \
                    qt/downloaddemodipydocs.cpp \
                    qt/icons.cpp \
                    qt/mainwindow.cpp \
                    qt/posintextframeformat.cpp \
                    qt/presentationscreen.cpp \
                    qt/scsplitter.cpp \
                    qt/sourceeditor.cpp \
                    qt/sourcetoolbar.cpp \
                    qt/sourcezone.cpp \
                    qt/sctabs.cpp \
                    qt/texteditor.cpp \
                    qt/textformat.cpp \
                    qt/ui.cpp

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
RC_FILE = dipylonreader.rc



QMAKE_CFLAGS     += -std=c++1y -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wunused-value -O2

QMAKE_CXXFLAGS   += -std=c++1y -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wunused-value -O2

#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/application
#INSTALLS += target
