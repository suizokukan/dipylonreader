rm qrc_*.cpp
rm moc_*.cpp
rm dipylon

qmake-qt5

make

./dipylon
