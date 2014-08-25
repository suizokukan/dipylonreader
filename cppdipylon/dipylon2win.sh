echo "=== cross-compiling Linux > Windows using MXE ==="

echo "== export PATH"
export PATH=~/mxe/usr/bin:$PATH
echo $PATH

echo "== filling 2win/"
rm -rf 2win
mkdir 2win
cp -r * 2win/

echo "== dipylon2win.pro > 2win/dipylon.pro"
rm 2win/dipylon.pro*
cp dipylon2win.pro 2win/dipylon.pro

echo "== dipylon2win.sh > 2win/dipylon.sh"
rm 2win/dipylon.sh*
cp dipylon2win.sh 2win/dipylon.sh

echo "== removing 2win/quick_dipylon.sh*"
rm 2win/quick_dipylon.sh*

echo "== removing all files in 2win/build/"
rm -rf 2win/build/*

cd 2win
echo "== now in 2win/"

echo "== calling qmake"
~/mxe/usr/i686-pc-mingw32/qt5/bin/qmake -makefile dipylon.pro
echo "== calling make"
make

echo "== now in ./"
cd ..