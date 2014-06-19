######################################################################
# Dipylon project
######################################################################

QT += widgets

TEMPLATE = app
TARGET = dipylon
INCLUDEPATH += .
RESOURCES = ressources.qrc

# Input
HEADERS = postxt/posranges.h \
          postxt/vectorposranges.h \
          postxt/pos2str.h \
          hash.h \
          qt/dipylonui.h \
          qt/sourceeditor.h \
          qt/commentaryeditor.h \
          qt/mainsplitter.h \
          dipydoc/dipydoc.h

SOURCES += main.cpp \
           postxt/posranges.cpp \
           postxt/vectorposranges.cpp \
           postxt/pos2str.cpp \
           qt/dipylonui.cpp \
           qt/sourceeditor.cpp \
           qt/commentaryeditor.cpp \
           qt/mainsplitter.cpp \
           dipydoc/dipydoc.cpp

QMAKE_CFLAGS += -std=c++11 -Wpedantic
QMAKE_CXXFLAGS += -std=c++11 -Wpedantic

QT += testlib