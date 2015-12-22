rm ../builds/*

rm -rf temp__build* && ./build_win32static.py --debug=0 --console=no
rm -rf temp__build* && ./build_win32static.py --debug=1 --console=yes

rm -rf temp__build* && ./build_win64static.py --debug=0 --console=no
rm -rf temp__build* && ./build_win64static.py --debug=1 --console=yes

rm -rf temp__build* && ./build_linux64dynamic.py --debug=0 --compiler=gcc
rm -rf temp__build* && ./build_linux64dynamic.py --debug=1 --compiler=gcc
rm -rf temp__build* && ./build_linux64dynamic.py --debug=0 --compiler=clang
rm -rf temp__build* && ./build_linux64dynamic.py --debug=1 --compiler=clang

rm -rf temp__build*


