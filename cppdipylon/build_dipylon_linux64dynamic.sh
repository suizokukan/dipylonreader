echo "=== compiling Linux > Linux64/dynamic ==="
echo "==="
echo "===   This file must be launched from the root directory,"
echo "===   not from the temp__build_linux64_dynamic/ folder."
echo "==="
echo "===   Everything is compiled in the temp__build_linux64_dynamic/ folder."
echo "==="
echo "===   The binary file created by the compilation will be"
echo "===   copied into the builds/ folder"
echo "==="
echo ""

echo "== filling temp__build_linux64_dynamic/"
mkdir -p temp__build_linux64_dynamic/
rm -rf temp__build_linux64_dynamic/*
rsync -a . temp__build_linux64_dynamic/ --exclude temp__build_linux64_dynamic/

cd temp__build_linux64_dynamic/
echo "== now in temp__build_linux64_dynamic/"

echo "== removing the binary in builds/"
rm -f ../../builds/dipylon_linux_64bits_dynamic

echo "== calling qmake"
qmake-qt5 -makefile dipylon.pro

echo "== calling make"
make

echo "== copying the binary into the builds/ folder"
cp ./build/dipylon ../../builds/dipylon_linux_64bits_dynamic

echo "== now in ./"
cd ..
