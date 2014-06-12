######################################################################
# Dipylon project
######################################################################

TEMPLATE = app
TARGET = dipylon
INCLUDEPATH += .
RESOURCES        =  dipylon.qrc

QT += widgets
QT += multimedia

# Input
HEADERS         +=  parameters.h \
                    qt/mainwindow.h \
                    qt/dipylonui.h \	
                    qt/sourceeditor.h \
                    qt/commentaryeditor.h \
                    dipydoc/dipydoc.h \
                    posintxt/posintxt.h \
                    posintxt/posranges.h \
                    posintxt/vectorposranges.h \
                    posintxt/pos2str.h \
                    posinaudio/posinaudio.h

SOURCES         +=  main.cpp \
                    qt/mainwindow.cpp \
                    qt/dipylonui.cpp \
                    qt/sourceeditor.cpp \
                    qt/commentaryeditor.cpp \
                    dipydoc/dipydoc.cpp \
                    posintxt/posranges.cpp \
                    posintxt/vectorposranges.cpp \
                    posintxt/pos2str.cpp

QMAKE_CFLAGS     += -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused

QMAKE_CXXFLAGS   += -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused

#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/application
#INSTALLS += target
