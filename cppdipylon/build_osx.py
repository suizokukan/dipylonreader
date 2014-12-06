#!/usr/bin/env python
# -*- coding: utf-8 -*-

################################################################################
#
# build_osx.py
#
# Python2/3 script.
# to be used only on OSX.
#
################################################################################
#
# This script launches the compilation of the Dipylon's project
#
# o --debug=0, --debug=1
#       =0 : no call to DebugMessage() will be kept
#       =1 : the calls to DebugMessage() marked as // DEBUG1 will be kept
#
# o this script seeks in fixedparameters.h the project's version :
#   expected format is :
#       const QString application_version = "@@@version number@@@";
#
#       where @@@version number@@@ can be anything, "0.4.7" or "1.2.3-special-release"
# 
################################################################################
#
#
################################################################################

#pour résoudre un bug apparaissant avec macdeployqt et faisant apparaître le message :
#
# ERROR : no file at "/opt/local/lib/libz.1.dylib"
#
# ajouter le fichier manuellement :
#
# sudo cp /Users/admin/qt5_online_installation/Qt\ Creator.app/Contents/Frameworks/libz.1.dylib /opt/local/lib/
#
import os
import argparse
from datetime import datetime

start_time = datetime.now()

VERSION = "build_osx : v1"
SUMMARY = "OSX > OSX/dynamic + macdeployqt"

# system call
def ossystem(arg):
    os.system(arg)
    print(arg)

# command line options :
PARSER = argparse.ArgumentParser(description=SUMMARY)

PARSER.add_argument("--debug",
                    help="level of the calls to DebugMessage() to be kept : =0 if nothing to be kept.",
                    choices={0,1},
                    required=True,
                    type=int)

PARSER.add_argument("--version",
                    action="version",
                    version=VERSION)

ARGS = PARSER.parse_args()

# getting the version of the project :
VERSION = "unknown_version"
VERSION_LINE_STARTSWITH = "const QString application_version = \""
with open("fixedparameters.h", 'r') as fixedparameters_file:
    for line in fixedparameters_file.readlines():
        if line.startswith(VERSION_LINE_STARTSWITH):
            # "-3" since we get rid of the two "; characters :
            VERSION = line[len(VERSION_LINE_STARTSWITH):-3]

# setting the version string for the executable filename :
VERSION_FOR_EXEC_NAME = VERSION.replace(".", "_")
VERSION_FOR_EXEC_NAME = VERSION.replace(" ", "_")

# getting the build number :
BUILD_NUMBER = -1
with open("build_number", 'r') as buildnumber_file:
    BUILD_NUMBER = int(buildnumber_file.read())
    BUILD_NUMBER += 1
with open("build_number", 'w') as buildnumber_file:
    buildnumber_file.write(str(BUILD_NUMBER))

# setting the temporary build folder without the final '/' :
TEMP_FOLDER = "temp__build_osx_debug{0}".format(ARGS.debug)

# setting the executable name :
EXEC_NAME  = "dipylonreader_osx_v{0}_debug{1}_build{2}".format(VERSION_FOR_EXEC_NAME,
                                                                       ARGS.debug,
                                                                       BUILD_NUMBER)

PATH_TO_QMAKE = "/Users/admin/qt5_online_installation/5.4/clang_64/bin/qmake"

PATH_TO_MACDEPLOYQT = "/Users/admin/qt5_online_installation/5.4/clang_64/bin/macdeployqt"
OPTIONS_FOR_MACDEPLOYQT = "-verbose=0 -dmg"

# build :
print("=== compiling {0} ===".format(SUMMARY))
print("===")
print("===   This file must be launched from the root directory,")
print("===   not from the {0}/ folder.".format(TEMP_FOLDER))
print("===")
print("===   Everything is compiled in the {0}/ folder.".format(TEMP_FOLDER))
print("===")
print("===   The binary file created by the compilation will be")
print("===   copied into the builds/ folder")
print("===")
print("")

print("== create builds/ folder if it doesn't exist")
ossystem("mkdir -p ../builds/")

print("== filling {0}/".format(TEMP_FOLDER))
ossystem("mkdir -p {0}/".format(TEMP_FOLDER))
ossystem("rm -rf {0}/*".format(TEMP_FOLDER))
ossystem("rsync -a . {0}/ --exclude {0}/".format(TEMP_FOLDER))
    
print("== 2osx/ > {0}/".format(TEMP_FOLDER))
print("... dipylonreader.pro")
ossystem("cp 2osx/dipylonreader.pro {0}/".format(TEMP_FOLDER))

os.chdir("{0}/".format(TEMP_FOLDER))
print("== now in {0}/".format(TEMP_FOLDER))

print("== removing // DEBUGx prefix ?")
if ARGS.debug == 1:
    print("... removing the // DEBUG1 prefix")
    ossystem("find . -name '*.cpp' -exec sed -i '' s://\ DEBUG1\ ::g {} \;")
    ossystem("find . -name '*.h'   -exec sed -i '' s://\ DEBUG1\ ::g {} \;")
    
print("== calling qmake")
ossystem(PATH_TO_QMAKE + " -makefile dipylonreader.pro")

print("== calling make")
ossystem("make -j2")

print("== copying the binary into the builds/ folder")
ossystem("cp -rf ./build/dipylonreader.app/ ../../builds/{0}.app".format(EXEC_NAME))
print("== setting the name of the executable in the bundle. ")
print("   (if the bundle's path is xyz.app, the executable must be xyz)")
ossystem("mv ../../builds/{0}.app/Contents/MacOS/dipylonreader "
         "../../builds/{0}.app/Contents/MacOS/{0}".format(EXEC_NAME))

print("== calling macdeployqt on the result")
ossystem(PATH_TO_MACDEPLOYQT + " ../../builds/{0}.app".format(EXEC_NAME) + " " + OPTIONS_FOR_MACDEPLOYQT)

print("== setting Info.plist from 2osx/Info.plist.template")
print("... reading 2osx/Info.plist.template")
ossystem("cp 2osx/Info.plist.template ../../builds/{0}.app/Contents/Info.plist".format(EXEC_NAME))
with open("../../builds/{0}.app/Contents/Info.plist".format(EXEC_NAME), 'r') as plist_file:
    plist_data = plist_file.read()
print("... writing Info.plist")
plist_data = plist_data.replace("@@CFBundleExecutable@@",
                                EXEC_NAME)
with open("../../builds/{0}.app/Contents/Info.plist".format(EXEC_NAME), 'w') as plist_file:
    plist_file.write(plist_data)

time_end = datetime.now()
print("==> total time = ", str(time_end-start_time))

print("")
print("tried to build " + EXEC_NAME)

print("== let's launch the program !")
ossystem("../../builds/{0}.app/Contents/MacOS/{0}".format(EXEC_NAME))