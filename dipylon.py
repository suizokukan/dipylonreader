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
        ❏Dipulon❏ dipylon.py

        entry-point for the Dipylon program.
"""

from PyQt4 import QtGui
from PyQt4 import QtCore
import sys
from qtapplication import MainApplication
from config import init_config_ini

#///////////////////////////////////////////////////////////////////////////////
def create_and_launch_the_Qt_application(input_textfile = None):
    """
        function create_and_launch_the_Qt_application : entry point in the Qt
        part of the program.
    """

    app = QtGui.QApplication(sys.argv)
    ex = MainApplication(input_textfile)

    # i18n :
    t = QtCore.QTranslator(None)
    t.load("qt_{0}.qm".format("fra"),
           QtCore.QLibraryInfo.location(QtCore.QLibraryInfo.TranslationsPath))
    app.installTranslator(t)

    return app.exec_()


################################################################################
# ENTRY POINT
################################################################################
init_config_ini()

if len(sys.argv)==2:
    create_and_launch_the_Qt_application(sys.argv[1])
else:
    create_and_launch_the_Qt_application()
