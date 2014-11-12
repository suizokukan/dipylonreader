#!/usr/bin/env python

################################################################################
#
# build_linux64dynamic.py
#
# Python2/3 script.
# to be used only on a system with a shell.
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
# version 6 (2014.11.11) : new name + display executable's name
#
# version 5 (2014.11.09) : make uses -j2 + display total amount of time
#
# version 4 (2014.11.01) : new EXEC_NAME, ending with "_v{0}_debug{1}_build{2}"
#
# version 3 (2014.10.31) : temp folder's name depends on ARGS.debug value
#
# version 2 (2014.10.31) : command line options "--debug", "--version" and "--help"
#
# version 1 (2014.10.26) : first version to be committed.
#
################################################################################

import os
import argparse
from datetime import datetime

start_time = datetime.now()

VERSION = "build_linux64dynamic : v6"
SUMMARY = "Linux > Linux64/dynamic"

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
TEMP_FOLDER = "temp__build_linux64_dynamic_debug{0}".format(ARGS.debug)

# setting the executable name :
EXEC_NAME  = "dipylonreader_linux_64bits_dynamic_v{0}_debug{1}_build{2}".format(VERSION_FOR_EXEC_NAME,
                                                                                ARGS.debug,
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

print("== filling {0}/".format(TEMP_FOLDER))
ossystem("mkdir -p {0}/".format(TEMP_FOLDER))
ossystem("rm -rf {0}/*".format(TEMP_FOLDER))
ossystem("rsync -a . {0}/ --exclude {0}/".format(TEMP_FOLDER))

os.chdir("{0}/".format(TEMP_FOLDER))
print("== now in {0}/".format(TEMP_FOLDER))

print("== removing // DEBUGx prefix ?")
if ARGS.debug == 1:
    print("... removing the // DEBUG1 prefix")
    ossystem("find . -name \"*.cpp\" -exec sed -i 's:// DEBUG1 ::g' {} \;")
    ossystem("find . -name \"*.h\"   -exec sed -i 's:// DEBUG1 ::g' {} \;")
    
print("== calling qmake")
ossystem("qmake-qt5 -makefile dipylonreader.pro")

print("== calling make")
ossystem("make -j2")

print("== copying the binary into the builds/ folder")
ossystem("cp ./build/dipylonreader ../../builds/{0}".format(EXEC_NAME))

time_end = datetime.now()
print("==> total time = ", str(time_end-start_time))

print()
print("tried to build " + EXEC_NAME)

