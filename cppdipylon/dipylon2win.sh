echo "=== cross-compiling Linux > Windows using MXE ==="
echo "==="
echo "===   This file must be launched from the root directory,"
echo "===   not from the build2win/ folder."
echo "==="
echo "===   Everything is compiled in the build2win/ folder."
echo "==="
echo "===   The binary file created by the compilation will"
echo "===   copied into the builds/ folder"
echo "==="
echo ""

echo "== export MXE binary folder to PATH"
export PATH=~/mxe/usr/bin:$PATH
echo $PATH

echo "== filling build2win/"
mkdir -p build2win/
rm -rf build2win/*
rsync -a . build2win/ --exclude build2win/

echo "== 2win/* > build2win/"
echo "... dipylon.pro"
cp 2win/dipylon.pro build2win/dipylon.pro
echo "... win_app_icon.ico"
cp 2win/ressources/images/icons/win_app_icon.ico build2win/ressources/images/icons/
echo "... dipylon.rc"
cp 2win/dipylon.rc build2win/

echo "== removing build2win/[quick_]dipylon.sh*"
rm build2win/dipylon.sh*
rm build2win/quick_dipylon.sh*

echo "== removing all files from build2win/build/"
rm -rf build2win/build/*

cd build2win/
echo "== now in build2win/"

echo "== removing the binary in builds/"
rm -f ../../builds/dipylon_windows_32bits_qtstatic.exe

echo "== calling qmake"
~/mxe/usr/i686-pc-mingw32/qt5/bin/qmake -makefile dipylon.pro
echo "== calling make"
make

echo "== copying the binary into the builds/ folder"
cp ./build/dipylon.exe ../../builds/dipylon_windows_32bits_qtstatic.exe

echo "== now in ./"
cd ..
