echo "=== compiling Linux > Linux ==="
echo "==="
echo "===   This file must be launched from the root directory,"
echo "===   not from the build/ folder."
echo "==="
echo "===   Everything is compiled in the build/ folder."
echo "==="
echo "===   The binary file created by the compilation will"
echo "===   copied into the builds/ folder"
echo "==="
echo ""

echo "== cleaning the build/ folder"
rm -rf build/*

echo "== removing the binary in builds/"
rm -f ../builds/dipylon_linux_64bits_qtdynamic

echo "== calling qmake"
qmake-qt5 -makefile dipylon.pro

echo "== calling make"
make

echo "== copying the binary into the builds/ folder"
cp ./build/dipylon ../builds/dipylon_linux_64bits_qtdynamic

echo "== launching the binary"
./../builds/dipylon_linux_64bits_qtdynamic
