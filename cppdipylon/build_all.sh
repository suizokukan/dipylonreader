rm ../builds/*

rm -rf temp__build* && ./build_dipylonreader_win32static.py --debug=0 --console=no
rm -rf temp__build* && ./build_dipylonreader_win32static.py --debug=1 --console=yes

rm -rf temp__build* && ./build_dipylonreader_win64static.py --debug=0 --console=no
rm -rf temp__build* && ./build_dipylonreader_win64static.py --debug=1 --console=yes

rm -rf temp__build* && ./build_dipylonreader_linux64dynamic.py --debug=0
rm -rf temp__build* && ./build_dipylonreader_linux64dynamic.py --debug=1


