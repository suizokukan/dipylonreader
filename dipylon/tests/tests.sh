rm qrc_*.cpp
rm moc_*.cpp
rm *.o
rm tests

qmake-qt5

make 

./tests
