################################################################################
#
# create_demo_packages.py
#
# Python2 script.
# to be used only on a system with a shell.
#
################################################################################
#
# This script analyses the files of the project and stores the result in 
# the 'cpplint_py__output' file.
# 
################################################################################
# version 1 (2014.10.01) : first version to be committed.
################################################################################

import os

invoking_cpplint = "python2 ~/projets/cpplint.py --linelength=120"

paths_to_be_analyzed = ('./debugmsg', 
                        './dipydoc', 
                        './languages', 
                        './misc', 
                        './pos', 
                        './qt')

#...............................................................................
# system call
#...............................................................................
def ossystem(arg):
    os.system(arg)
    #print(arg)

################################################################################
# (0) cleaning output files
################################################################################
ossystem("rm -f cpplint_py__tmp")
ossystem("rm -f cpplint_py__output")

################################################################################
# (1) searching the directories to be analyzed.
################################################################################
target_directories = []
for _root, _dirs, _files in os.walk("."):
    for target_dir in _dirs:
        if _root in paths_to_be_analyzed or \
           "./"+target_dir in paths_to_be_analyzed:
            target_directories.append(_root+"/"+target_dir)

target_directories = sorted(target_directories)

################################################################################
# (2) calling cpplint for each file.
################################################################################
for target_dir in target_directories:
    for root, dirs, files in os.walk(target_dir):
        for _file in files:
            if _file.endswith(".cpp") or _file.endswith(".h"):
                ossystem("{0} \"{1}\" &>>cpplint_py__tmp".format(invoking_cpplint,
                                                                 target_dir+"/"+_file))

                ossystem("cat cpplint_py__tmp >> cpplint_py__output")
                ossystem("rm cpplint_py__tmp")

################################################################################
# (3) cleaning output file(s)
################################################################################
ossystem("rm -f cpplint_py__tmp")
