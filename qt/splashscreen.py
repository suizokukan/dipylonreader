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
        ❏Dipylon❏ splashscreen.py
"""

from PyQt5 import QtWidgets
from PyQt5 import QtGui
from PyQt5 import QtCore

from system import numversion as numversion
import system.communia
VERSION = numversion.VersionOfTheProgram().numversion

import os

from qt import constants

################################################################################
class SplashScreen(QtWidgets.QSplashScreen):
    """
        class SplashScreen
    """

    message = "<span style=\"color:#223399\">" \
              "<b>Dipylon</b>'s version={0}<br/>" \

    #///////////////////////////////////////////////////////////////////////////
    def __init__(self):
        """
                SplashScreen.__init__
        """
        splash_image = QtGui.QPixmap( os.path.join('images', 'splashscreen.png'))

        QtWidgets.QSplashScreen.__init__(self,
                                         splash_image,
                                         QtCore.Qt.WindowStaysOnTopHint)

        self.setWindowTitle(constants.GENERIC_WINDOW_TITLE)

        msg = SplashScreen.message.format(VERSION)

        self.showMessage(msg,
		                 QtCore.Qt.AlignLeft | QtCore.Qt.AlignTop)
        
        self.mousePressEvent = self.event__mousepress
        self.keyPressEvent = self.event__keypressevent

    #///////////////////////////////////////////////////////////////////////////
    def event__mousepress(self, event):
        """
                SplashScreen.event__mousepress
        """
        self.close()

    #///////////////////////////////////////////////////////////////////////////
    def event__keypressevent(self, event):
        """
                SplashScreen.event__keypressevent
        """
        self.close()
