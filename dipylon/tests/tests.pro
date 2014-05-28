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
          ../pos2str.h \
	  ../hash.h \
          testhash.h \
          testposranges.h \
          testpos2str.h

SOURCES += ../posranges.cpp \
           ../pos2str.cpp \
           tests.cpp \
           testposranges.cpp \
           testpos2str.cpp \
           testhash.cpp           

QMAKE_CFLAGS += -std=c++11 -Wpedantic
QMAKE_CXXFLAGS += -std=c++11 -Wpedantic
