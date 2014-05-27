######################################################################
# Dipylon project / tests
######################################################################

QT += testlib

QT += widgets

TEMPLATE = app
TARGET = tests
INCLUDEPATH += .

# Input
HEADERS = ../gaps.h \
          ../hash.h \
          testhash.h \
          testgaps.h

SOURCES += tests.cpp \
           testgaps.cpp \
           testhash.cpp \
           ../gaps.cpp

QMAKE_CFLAGS += -std=c++11 -Wpedantic
QMAKE_CXXFLAGS += -std=c++11 -Wpedantic
