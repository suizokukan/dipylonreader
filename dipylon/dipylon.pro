######################################################################
# Dipylon project
######################################################################

QT += widgets

TEMPLATE = app
TARGET = dipylon
INCLUDEPATH += .

# Input
HEADERS = postxt/posranges.h \
          postxt/pos2str.h \
          postxt/translations.h \
          hash.h \
          qt/sourceeditor.h \
          qt/commentaryeditor.h \
          qt/mainsplitter.h

SOURCES += main.cpp \		
           postxt/posranges.cpp \
           postxt/pos2str.cpp \
           postxt/translations.cpp \
           qt/sourceeditor.cpp \
           qt/commentaryeditor.cpp \
           qt/mainsplitter.cpp

QMAKE_CFLAGS += -std=c++11 -Wpedantic
QMAKE_CXXFLAGS += -std=c++11 -Wpedantic

QT += testlib
