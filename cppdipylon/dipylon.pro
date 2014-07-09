######################################################################
# Dipylon project
######################################################################

TEMPLATE = app
TARGET = dipylon
INCLUDEPATH += .
RESOURCES        =  dipylon.qrc
TRANSLATIONS = dipylon_French.ts

# to get rid of the qDebug() messages, uncomment this line :
#DEFINES += QT_NO_DEBUG_OUTPUT

# access to DipyDoc write functions :
DEFINES += READANDWRITE

QT += widgets
QT += multimedia

# Input
HEADERS         +=  fixedparameters.h \
                    languages/languages.h \
                    languages/languagefromto.h \
                    qt/mainwindow.h \
                    qt/dipylonui.h \	
                    qt/sourceeditor.h \
                    qt/commentaryeditor.h \
                    qt/textformat.h \
                    dipydoc/dipydoc.h \
                    pos/posintext2posinaudio.h \
                    pos/posinaudio2posintext.h \
                    pos/posinaudio/posinaudio.h \
                    pos/posinaudio/posinaudiorange.h \
                    pos/posintext/posintext.h \
                    pos/posintext/posintextranges.h \
                    pos/posintext/vectorposintextranges.h \
                    pos/posintext/posintext2str.h

SOURCES         +=  main.cpp \
                    languages/languagefromto.cpp \
                    qt/mainwindow.cpp \
                    qt/dipylonui.cpp \
                    qt/sourceeditor.cpp \
                    qt/commentaryeditor.cpp \
                    qt/textformat.cpp \
                    dipydoc/dipydoc.cpp \
                    pos/posintext2posinaudio.cpp \
                    pos/posinaudio2posintext.cpp \
                    pos/posinaudio/posinaudiorange.cpp \
                    pos/posintext/posintextranges.cpp \
                    pos/posintext/vectorposintextranges.cpp \
                    pos/posintext/posintext2str.cpp

QMAKE_CFLAGS     += -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused

QMAKE_CXXFLAGS   += -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused

#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/application
#INSTALLS += target
