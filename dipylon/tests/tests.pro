######################################################################
# Dipylon project / tests
######################################################################

TEMPLATE = app
TARGET = dipylon
INCLUDEPATH      += ..

QT += testlib

# Input
HEADERS          += ../posintxt/posintxt.h \
                    ../posintxt/posranges.h \
                    ../posintxt/vectorposranges.h \
                    ../posintxt/pos2str.h
HEADERS          += testhash.h \
                    testposranges.h \
                    testvectorposranges.h \
                    testpos2str.h

SOURCES          += ../posintxt/posranges.cpp \
                    ../posintxt/vectorposranges.cpp \
                    ../posintxt/pos2str.cpp
SOURCES          += tests.cpp \
                    testposranges.cpp \
                    testvectorposranges.cpp \
                    testpos2str.cpp \
                    testhash.cpp

QMAKE_CFLAGS     += -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused

QMAKE_CXXFLAGS   += -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused
