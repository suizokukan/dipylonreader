#!/usr/bin/env python

################################################################################
#
# build_dipylonreader_win64static.py
#
# Python2/3 script.
# to be used only on a system with a shell.
#
################################################################################
#
# This script launches the compilation of the Dipylon's project
#
# o --console=yes, --console=no
#       Add a console to the application ?
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
# version 3 (2014.11.08) : improved TEMP_FOLDER
#
# version 2 (2014.11.21) : new option : --console=yes|no
#
# version 1 (2014.11.05) : first version to be committed.
#
################################################################################

import os
import argparse

VERSION = "build_dipylonreader_win64static : v3"
SUMMARY = "Linux > Windows64/static/using MXE"

# system call
def ossystem(arg):
    os.system(arg)
    #print(arg)

# command line options :
PARSER = argparse.ArgumentParser(description=SUMMARY)

PARSER.add_argument("--debug",
                    help="level of the calls to DebugMessage() to be kept : =0 if nothing to be kept.",
                    choices={0,1},
                    required=True,
                    type=int)

PARSER.add_argument("--console",
                    help="add a console to the application, or not",
                    choices={"yes","no"},
                    required=True,
                    type=str)

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
TEMP_FOLDER = "temp__build_win64_static_debug{0}_console{1}".format(ARGS.debug,
                                                                    ARGS.console)

# setting the executable name :
EXEC_NAME  = "dipylonreader_win_64bits_static_v{0}_debug{1}_console{2}_build{3}.exe".format(VERSION_FOR_EXEC_NAME,
                                                                                            ARGS.debug,
                                                                                            ARGS.console,
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
os.environ['PATH'] = "/home/suizokukan/mxe_64/usr/bin:" + os.environ['PATH']

print("== filling {0}/".format(TEMP_FOLDER))
ossystem("mkdir -p {0}/".format(TEMP_FOLDER))
ossystem("rm -rf {0}/*".format(TEMP_FOLDER))
ossystem("rsync -a . {0}/ --exclude {0}/ --exclude 2win64_static".format(TEMP_FOLDER))

print("== 2win64_static/* > {0}/".format(TEMP_FOLDER))
print("... dipylonreader.pro")
ossystem("cp 2win64_static/dipylonreader.pro {0}/dipylonreader.pro".format(TEMP_FOLDER))
print("... win_app_icon.ico")
ossystem("cp 2win64_static/ressources/images/icons/win_app_icon.ico {0}/ressources/images/icons/".format(TEMP_FOLDER))
print("... dipylonreader.rc")
ossystem("cp 2win64_static/dipylonreader.rc {0}/".format(TEMP_FOLDER))

os.chdir("{0}/".format(TEMP_FOLDER))
print("== now in {0}/".format(TEMP_FOLDER))

print("== removing // DEBUGx prefix ?")
if ARGS.debug == 1:
    print("... removing the // DEBUG1 prefix")
    ossystem("find . -name \"*.cpp\" -exec sed -i 's:// DEBUG1 ::g' {} \;")
    ossystem("find . -name \"*.h\"   -exec sed -i 's:// DEBUG1 ::g' {} \;")

print("== modifiying dipylonreader.pro")
with open("dipylonreader.pro", 'r') as pro_file:
    pro_file_content = pro_file.read()
if ARGS.console == "yes":
  pro_file_content = pro_file_content.replace("@@CONSOLE@@", "CONFIG += CONSOLE")
else:
  pro_file_content = pro_file_content.replace("@@CONSOLE@@", "CONFIG -= CONSOLE")
with open("dipylonreader.pro", 'w') as pro_file:
    pro_file.write(pro_file_content)

print("== calling qmake")
ossystem("~/mxe_64/usr/x86_64-w64-mingw32/qt5/bin/qmake -makefile dipylonreader.pro".format(TEMP_FOLDER))

print("== calling make")
ossystem("pwd")
ossystem("make")

print("== copying the binary into the builds/ folder")
ossystem("cp build/dipylonreader.exe ../../builds/{0}".format(EXEC_NAME))
