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
