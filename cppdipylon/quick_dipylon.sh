rm build/qrc_*.cpp
rm build/moc_*.cpp
rm build/dipylon

qmake-qt5

make

./build/dipylon
