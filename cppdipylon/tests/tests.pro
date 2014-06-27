######################################################################
# Dipylon project / tests
######################################################################

TEMPLATE = app
TARGET = tests
INCLUDEPATH      += ..

QT += testlib

# Input
HEADERS          += ../pos/posintext/posintext.h \
                    ../pos/posintext/posintextranges.h \
                    ../pos/posintext/vectorposintextranges.h \
                    ../pos/posintext/posintext2str.h \
                    ../pos/posinaudio/posinaudio.h \
                    ../pos/posinaudio/posinaudiorange.h \
                    ../pos/posintext2posinaudio.h \
                    ../pos/posinaudio2posintext.h \
                    ../languages/languagefromto.h
HEADERS          += testhash.h \
                    testposintextranges.h \
                    testvectorposintextranges.h \
                    testposinaudiorange.h \
                    testposintext2str.h \
                    testposintext2posinaudio.h \
                    testposinaudio2posintext.h \
                    testlanguagefromto.h

SOURCES          += ../pos/posintext/posintextranges.cpp \
                    ../pos/posintext/vectorposintextranges.cpp \
                    ../pos/posintext/posintext2str.cpp \
                    ../pos/posinaudio/posinaudiorange.cpp \
                    ../pos/posintext2posinaudio.cpp \
                    ../pos/posinaudio2posintext.cpp \
                    ../languages/languagefromto.cpp
SOURCES          += tests.cpp \
                    testposintextranges.cpp \
                    testvectorposintextranges.cpp \
                    testposinaudiorange.cpp \
                    testposintext2str.cpp \
                    testposintext2posinaudio.cpp \
                    testposinaudio2posintext.cpp \
                    testlanguagefromto.cpp \
                    testhash.cpp 

QMAKE_CFLAGS     += -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused

QMAKE_CXXFLAGS   += -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused
