echo "=== cross-compiling Linux > Windows/32/static/ using MXE ==="
echo "==="
echo "===   This file must be launched from the root directory,"
echo "===   not from the temp__build_win32_static/ folder."
echo "==="
echo "===   Everything is compiled in the temp__build_win32_static/ folder."
echo "==="
echo "===   The binary file created by the compilation will be"
echo "===   copied into the builds/ folder"
echo "==="
echo ""

echo "== export MXE binary folder to PATH"
export PATH=~/mxe/usr/bin:$PATH
echo $PATH

echo "== filling temp__build_win32_static/"
mkdir -p temp__build_win32_static/
rm -rf temp__build_win32_static/*
rsync -a . temp__build_win32_static/ --exclude temp__build_win32_static/

echo "== 2win32_static/* > temp__build_win32_static/"
echo "... dipylon.pro"
cp 2win32_static/dipylon.pro temp__build_win32_static/dipylon.pro
echo "... win_app_icon.ico"
cp 2win32_static/ressources/images/icons/win_app_icon.ico temp__build_win32_static/ressources/images/icons/
echo "... dipylon.rc"
cp 2win32_static/dipylon.rc temp__build_win32_static/

cd temp__build_win32_static/
echo "== now in temp__build_win32_static/"

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
