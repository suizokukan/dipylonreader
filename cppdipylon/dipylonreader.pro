######################################################################
# DipylonReader project : Linux > Linux
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
DEFINES += READANDWRITE
DEFINES += ALLOW_LOADING_DIPYDOC_FROM_THE_COMMAND_LINE
DEFINES += ALLOW_SPLASHSCREEN
DEFINES += ALLOW_RESIZING_THE_MAINWINDOW
DEFINES += ALLOW_MOVING_THE_MAINWINDOW
DEFINES += ALLOW_MAXIMIZE_MAINWINDOW
DEFINES += MAXIMIZE_MAINWINDOW_LINUXDESKTOPX11_METHOD
DEFINES += DEBUG_MESSAGES_TO_CERR
DEFINES += STORE_DEBUG_MESSAGES
DEFINES += QT_NO_DEBUG_OUTPUT
DEFINES += DISPLAY_INTERNAL_MESSAGES_IN_HELP_MENUITEM
DEFINES += DOWNLOAD_OGG_VERSION_OF_DIPYDOCS

QT += network
QT += widgets
QT += multimedia

# Input
HEADERS         +=  ./fixedparameters.h \
                    debugmsg/debugmsg.h \
                    dipydoc/dipydoc.h \
                    dipydoc/dipydocnotes.h \
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
                    qt/ui.h \	
                    qt/mainwindow.h \
                    qt/posintextframeformat.h \
                    qt/sourceeditor.h \
                    qt/sourcetoolbar.h \
                    qt/sourcezone.h \
                    qt/textformat.h \
                    qt/downloaddemodipydocs.h

SOURCES         +=  ./main.cpp \
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
                    qt/ui.cpp \
                    qt/mainwindow.cpp \
                    qt/posintextframeformat.cpp \
                    qt/sourceeditor.cpp \
                    qt/sourcetoolbar.cpp \
                    qt/sourcezone.cpp \
                    qt/textformat.cpp \
                    qt/downloaddemodipydocs.cpp

DESTDIR = build/
OBJECTS_DIR = build/
MOC_DIR = build/
RCC_DIR = build/
UI_DIR = build/

QMAKE_CFLAGS     += -std=c++1y -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wunused-value -Werror

QMAKE_CXXFLAGS   += -std=c++1y -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wunused-value -Werror

#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/application
#INSTALLS += target
