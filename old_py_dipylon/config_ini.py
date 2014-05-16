#!./python_link
# -*- coding: utf-8 -*-
################################################################################
#    Dipylon Copyright (C) 2008 Xavier Faure
#    Contact: faure dot epistulam dot mihi dot scripsisti at orange dot fr
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
        ❏Dipylon❏ config_ini.py
"""

import configparser, os, codecs

CONFIG_INI = None

#///////////////////////////////////////////////////////////////////////////////
def read_configuration_file():
    """
        function read_configuration_file()
        
        read the config.ini and return the result.
    """
    data = configparser.ConfigParser()
    config_ini_filename = os.path.join(os.path.dirname(os.path.realpath(__file__)), "config.ini" )
    
    # something's wrong with configparser : instead of simply writing
    #      DATA.read( open(config_ini_filename, "r", encoding="utf-8") )
    # we have to use this strange hack :
    data.readfp( codecs.open(config_ini_filename, "r", "utf-8") )
            
    return data
