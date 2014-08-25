rm -rf build/*

qmake-qt5 -makefile dipylon.pro

make

./build/dipylon
