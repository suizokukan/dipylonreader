echo "=== cross-compiling Linux > Windows/32/static/ using MXE ==="
echo "==="
echo "===   This file must be launched from the root directory,"
echo "===   not from the build_XXX/ folder."
echo "==="
echo "===   Everything is compiled in the build_XXX/ folder."
echo "==="
echo "===   The binary file created by the compilation will"
echo "===   copied into the builds/ folder"
echo "==="
echo ""

echo "== export MXE binary folder to PATH"
export PATH=~/mxe/usr/bin:$PATH
echo $PATH

echo "== filling build_win32_static/"
mkdir -p build_win32_static/
rm -rf build_win32_static/*
rsync -a . build_win32_static/ --exclude build_win32_static/

echo "== 2win32_static/* > build_win32_static/"
echo "... dipylon.pro"
cp 2win32_static/dipylon.pro build_win32_static/dipylon.pro
echo "... win_app_icon.ico"
cp 2win32_static/ressources/images/icons/win_app_icon.ico build_win32_static/ressources/images/icons/
echo "... dipylon.rc"
cp 2win32_static/dipylon.rc build_win32_static/

echo "== removing build_win32_static/[quick_]dipylon.sh*"
rm build_win32_static/dipylon.sh*
rm build_win32_static/quick_dipylon.sh*

echo "== removing all files from build_win32_static/build/"
rm -rf build_win32_static/build/*

cd build_win32_static/
echo "== now in build_win32_static/"

echo "== removing the binary in builds/"
rm -f ../../builds/dipylon_windows_32bits_static.exe

echo "== calling qmake"
~/mxe/usr/i686-pc-mingw32/qt5/bin/qmake -makefile dipylon.pro
echo "== calling make"
make

echo "== copying the binary into the builds/ folder"
cp ./build/dipylon.exe ../../builds/dipylon_windows_32bits_static.exe

echo "== now in ./"
cd ..
