rm build/qrc_*.cpp
rm build/moc_*.cpp
rm build/dipylon

qmake-qt5 -project dipylon.pro

make

cp ./build/dipylon ../builds/dipylon_linux_64bits

./../builds/dipylon_linux_64bits
