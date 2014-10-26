#!/usr/bin/env python

################################################################################
#
# build_dipylonreader_win32static.py
#
# Python2/3 script.
# to be used only on a system with a shell.
#
################################################################################
#
# This script launches the compilation of the Dipylon's project
#
# o this script seeks in fixedparameters.h the project's version :
#   expected format is :
#       const QString application_version = "@@@version number@@@";
#
#       where @@@version number@@@ can be anything, "0.4.7" or "1.2.3-special-release"
# 
################################################################################
# version 1 (2014.10.26) : first version to be committed.
################################################################################

import os

SUMMARY = "Linux > Windows32/static/using MXE"

#...............................................................................
# system call
#...............................................................................
def ossystem(arg):
    os.system(arg)
    #print(arg)
    
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
TEMP_FOLDER = "temp__build_win32_static"

# setting the executable name :
EXEC_NAME  = "dipylonreader_win_32bits_static_v{0}_build{1}.exe".format(VERSION_FOR_EXEC_NAME,
                                                                        BUILD_NUMBER)

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
ossystem("mkdir -p ../builds")

NEWPATH = "/home/suizokukan/mxe/usr/bin:" + os.environ['PATH']
#print("== export MXE binary folder to PATH")
#print(os.environ['PATH'])
#ossystem("export PATH=~/mxe/usr/bin:$PATH")
os.environ['PATH'] = "/home/suizokukan/mxe/usr/bin:" + os.environ['PATH']
#ossystem("echo $PATH")

print("== filling {0}/".format(TEMP_FOLDER))
ossystem("mkdir -p {0}/".format(TEMP_FOLDER))
ossystem("rm -rf {0}/*".format(TEMP_FOLDER))
ossystem("rsync -a . {0}/ --exclude {0}/ --exclude 2win32_static".format(TEMP_FOLDER))

print("== 2win32_static/* > {0}/".format(TEMP_FOLDER))
print("... dipylonreader.pro")
ossystem("cp 2win32_static/dipylonreader.pro {0}/dipylonreader.pro".format(TEMP_FOLDER))
print("... win_app_icon.ico")
ossystem("cp 2win32_static/ressources/images/icons/win_app_icon.ico {0}/ressources/images/icons/".format(TEMP_FOLDER))
print("... dipylonreader.rc")
ossystem("cp 2win32_static/dipylonreader.rc {0}/".format(TEMP_FOLDER))

os.chdir("{0}/".format(TEMP_FOLDER))
print("== now in {0}/".format(TEMP_FOLDER))

print("== calling qmake")
ossystem("~/mxe/usr/i686-pc-mingw32/qt5/bin/qmake -makefile dipylonreader.pro".format(TEMP_FOLDER))

print("== calling make")
ossystem("pwd")
ossystem("make")

print("== copying the binary into the builds/ folder")
ossystem("cp build/dipylonreader.exe ../../builds/{0}".format(EXEC_NAME))