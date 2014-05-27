######################################################################
# Dipylon project / tests
######################################################################

QT += testlib

QT += widgets

TEMPLATE = app
TARGET = tests
INCLUDEPATH += .

# Input
HEADERS = ../posranges.h \
          ../hash.h \
          testhash.h \
          testposranges.h

SOURCES += tests.cpp \
           testposranges.cpp \
           testhash.cpp \
           ../posranges.cpp

QMAKE_CFLAGS += -std=c++11 -Wpedantic
QMAKE_CXXFLAGS += -std=c++11 -Wpedantic
