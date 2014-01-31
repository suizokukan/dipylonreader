#!/usr/bin/python3
# -*- coding: utf-8 -*-
################################################################################
#    Dipylon Copyright (C) 2012 Suizokukan
#    Contact: suizokukan _A.T._ orange dot fr
#
#    This file is part of Dipylon.
#    Dipylon is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Dipylon is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Dipylon.  If not, see <http://www.gnu.org/licenses/>.
################################################################################
"""
        ❏Dipylon❏ system/communia.py

        This file defines the name of the program and the version of the
        program.
"""

from system.numversion import VersionOfTheProgram

OPTIONS = { "name_of_the_program" : "δίπυλον",           #: (type: str)
            "ascii_name_of_the_program" : "Dipylon",     #: (type: str)
            "ascii_name_of_the_program_for_directories" : "dipylon",  #: (type: str)
            #: (type: str, NOT an VersionOfTheProgram object)  :
            "version_of_the_program" : str(VersionOfTheProgram())
           }
