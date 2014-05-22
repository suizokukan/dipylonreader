######################################################################
# Dipylon project
######################################################################

QT += widgets

TEMPLATE = app
TARGET = dipylon
INCLUDEPATH += .

# Input
HEADERS = gaps.h \
          qt/sourceeditor.h \
          qt/commentaryeditor.h \
          qt/mainsplitter.h 

SOURCES += main.cpp \
           gaps.cpp \
           qt/sourceeditor.cpp \
           qt/commentaryeditor.cpp \
           qt/mainsplitter.cpp

QMAKE_CFLAGS += -std=c++11 -Wpedantic
QMAKE_CXXFLAGS += -std=c++11 -Wpedantic

QT += testlib
