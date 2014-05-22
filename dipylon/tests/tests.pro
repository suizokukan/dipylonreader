######################################################################
# Dipylon project / tests
######################################################################

QT += testlib

QT += widgets

TEMPLATE = app
TARGET = tests
INCLUDEPATH += .

# Input
HEADERS = ../gaps.h

SOURCES += testgaps.cpp ../gaps.cpp

QMAKE_CFLAGS += -std=c++11 -Wpedantic
QMAKE_CXXFLAGS += -std=c++11 -Wpedantic
