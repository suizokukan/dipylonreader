rm build/qrc_*.cpp
rm build/moc_*.cpp
rm build/dipylon

rm ./../builds/dipylon_linux_64bits_qtdynamic

qmake-qt5 -project dipylon.pro

make

cp ./build/dipylon ../builds/dipylon_linux_64bits_qtdynamic

./../builds/dipylon_linux_64bits_qtdynamic
