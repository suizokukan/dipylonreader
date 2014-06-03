######################################################################
# Dipylon project / tests
######################################################################

QT += testlib

QT += widgets

TEMPLATE = app
TARGET = tests
INCLUDEPATH += ..

# Input
HEADERS = ../postxt/posranges.h \
          ../postxt/vectorposranges.h \
          ../postxt/pos2str.h \
	  ../hash.h \
          testhash.h \
          testposranges.h \
          testvectorposranges.h \
          testpos2str.h

SOURCES += ../postxt/posranges.cpp \
           ../postxt/vectorposranges.cpp \
           ../postxt/pos2str.cpp \
           tests.cpp \
           testposranges.cpp \
           testvectorposranges.cpp \
           testpos2str.cpp \
           testhash.cpp           

QMAKE_CFLAGS += -std=c++11 -Wpedantic
QMAKE_CXXFLAGS += -std=c++11 -Wpedantic
