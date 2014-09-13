echo "=== compiling Linux > Linux64/dynamic ==="
echo "==="
echo "===   This file must be launched from the root directory,"
echo "===   not from the temp__build_linux64_dynamic/ folder."
echo "==="
echo "===   Everything is compiled in the temp__build_linux64_dynamic/ folder."
echo "==="
echo "===   The binary file created by the compilation will"
echo "===   copied into the builds/ folder"
echo "==="
echo ""

echo "== create builds/ folder if it doesn't exist"
mkdir -p ../builds

echo "== filling temp__build_linux64_dynamic/"
rm -f temp__build_linux64_dynamic/build/qrc_*.cpp
rm -f temp__build_linux64_dynamic/build/moc_*.cpp
rm -f temp__build_linux64_dynamic/build/dipylonreader
rsync -a . temp__build_linux64_dynamic/ --exclude temp__build_linux64_dynamic/

cd temp__build_linux64_dynamic/
echo "== now in temp__build_linux64_dynamic/"

echo "== removing the binary in builds/ folder"
rm -f ../../builds/dipylonreader_linux_64bits_dynamic

echo "== calling qmake"
qmake-qt5 -makefile dipylonreader.pro

echo "== calling make"
make

echo "== copying the binary into the builds/ folder"
cp ./build/dipylonreader ../../builds/dipylonreader_linux_64bits_dynamic

echo "== now in ./"
cd ..

echo "== launching the binary"
../builds/dipylonreader_linux_64bits_dynamic

