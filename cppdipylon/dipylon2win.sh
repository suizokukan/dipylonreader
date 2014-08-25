rm -rf 2win
mkdir 2win
cp -r * 2win/

rm 2win/dipylon.pro*
cp dipylon2win.pro 2win/dipylon.pro

rm 2win/dipylon.sh*
cp dipylon2win.sh 2win/dipylon.sh

rm -rf 2win/build/*

cd 2win
~/mxe/usr/i686-pc-mingw32/qt5/bin/qmake && make
cd ..
