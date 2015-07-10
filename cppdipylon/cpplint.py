#!/usr/bin/python3
# -*- coding: utf-8 -*-
################################################################################
#
# cpplint.py
#
# Python2/3 script.
# to be used only on a system with a shell.
#
################################################################################
#
# This script analyses the files of the project and stores the result in 
# the output file.
# 
################################################################################
# version 3 (2014.10.03) : display total errors found.
# version 2 (2014.10.01) : improved the way the target files are found so that
#                          there's no doubloon left.
# version 1 (2014.10.01) : first version to be committed.
################################################################################

import os

invoking_cpplint = "python2 ~/projets/cpplint.py --linelength=120 --filter=-runtime/references"

output_filename = 'cpplint_py__output'

paths_to_be_analyzed = ('debugmsg', 
                        'dipydoc', 
                        'languages', 
                        'misc', 
                        'pos', 
                        'qt')

print("== cpplint.py : {0} > {1}".format(paths_to_be_analyzed, output_filename))

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
ossystem("rm -f "+output_filename)

################################################################################
# (1) searching the directories to be analyzed.
################################################################################
target_directories = []
for _root, _dirs, _files in os.walk("."):
    for target_dir in _dirs:
        if _root == '.' and target_dir in paths_to_be_analyzed:
            target_directories.append(_root+"/"+target_dir)

target_directories = sorted(target_directories)

################################################################################
# (2) calling cpplint for each file.
################################################################################
for target_dir in target_directories:
    for root, dirs, files in os.walk(target_dir):
        for _file in files:
            if _file.endswith(".cpp") or _file.endswith(".h"):
                print("= analysing " + root+"/"+_file)
                ossystem("{0} \"{1}\" &>>cpplint_py__tmp".format(invoking_cpplint,
                                                                 root+"/"+_file))

                ossystem("cat cpplint_py__tmp >> "+output_filename)
                ossystem("rm cpplint_py__tmp")

################################################################################
# (3) cleaning the temporary output file :
################################################################################
ossystem("rm -f cpplint_py__tmp")

################################################################################
# (4) reading the main output file to count the errors
################################################################################
numerr = 0
with open(output_filename, 'r') as outputfile:
    for line in outputfile.readlines():
        if line.startswith("Total errors found: "):
            numerr += int(line[:-1].split("Total errors found: ")[1])
print("== total error founds : ", numerr)
