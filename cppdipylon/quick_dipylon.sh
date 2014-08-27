echo "=== compiling Linux > Linux64/dynamic ==="
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

echo "== filling temp__build_linux64_dynamic/"
rm temp__build_linux64_dynamic/build/qrc_*.cpp
rm temp__build_linux64_dynamic/build/moc_*.cpp
rm temp__build_linux64_dynamic/build/dipylon
rsync -a . temp__build_linux64_dynamic/ --exclude temp__build_linux64_dynamic/

cd temp__build_linux64_dynamic/
echo "== now in temp__build_linux64_dynamic/"

echo "== removing the binary in builds/ folder"
rm ../../builds/dipylon_linux_64bits_dynamic

echo "== calling qmake"
qmake-qt5 -project dipylon.pro

echo "== calling make"
make

echo "== copying the binary into the builds/ folder"
cp ./build/dipylon ../../builds/dipylon_linux_64bits_dynamic

echo "== now in ./"
cd ..

echo "== launching the binary"
../builds/dipylon_linux_64bits_dynamic

