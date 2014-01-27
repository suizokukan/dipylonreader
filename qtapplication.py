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
        ❏Dipulon❏ qtapplication.py

        /-----------------------------------------------------------------\
        | File                                          Help
        |  Open(m1)
        |  Save as(m2)
        |  -----------
        |  Exit(m3)                                     About(m4)
        |
        |-----------------------------------------------------------------
        |
        | /------------------------\
        | | combo_readinglevel     |
        | \------------------------/
        |
        |-----------------------------------------------------------------
        |
        |   MainApplication.mainWidget(QtGui.QWidget)
        |   MainApplication.main_layout = QtGui.QVBoxLayout(self.mainWidget)
        |       |
        |       \---MainApplication.splitter = QtGui.QSplitter(QtCore.Qt.Vertical)
        |
        |   . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
        |   .                                                       .
        |   .   MainApplication.SourceText (QtGui.QTextEdit)        .
        |   . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
        |   . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
        |   .                                                       .
        |   .   MainApplication.Notes (QtGui.QTextEdit)             .
        |   . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
"""


from PyQt4 import QtGui
from PyQt4 import QtCore
import os

import config

################################################################################
class SourceText(QtGui.QTextEdit):
    """
        class SourceText
    """

    #///////////////////////////////////////////////////////////////////////////
    def __init__(self, parent, MainApplication_object):
        """
                SourceText.__init__
        """

        QtGui.QTextEdit.__init__(self, parent)
        self.MainApplication_object = MainApplication_object

################################################################################
class Notes(QtGui.QTextEdit):
    """
        class Notes
    """

    #///////////////////////////////////////////////////////////////////////////
    def __init__(self, parent, MainApplication_object):
        """
                Notes.__init__
        """

        QtGui.QTextEdit.__init__(self, parent)
        self.MainApplication_object = MainApplication_object

################################################################################
class MainApplication(QtGui.QMainWindow):
    """
        class MainApplication
    """

    #///////////////////////////////////////////////////////////////////////////
    def __init__(self, input_textfile = None):
        """
                MainApplication.__init__
        """

        QtGui.QMainWindow.__init__(self)

        self.define_known_actions()

        self.define_the_main_toolbar()

        self.statusBar = self.statusBar()

        self.define_the_main_menubar()

        self.mainWidget=QtGui.QWidget(self)
        self.setCentralWidget(self.mainWidget)
        self.layout_of_the_MainWindow()

        QtGui.QApplication.setStyle(QtGui.QStyleFactory.create('Cleanlooks'))
        self.setWindowTitle('Dipylon')

        icon_file = os.path.abspath(os.path.join(os.path.abspath( os.path.dirname( __file__)),
                                                 "icons",
                                                 "dipylon64x64.png" ))
        self.setWindowIcon(QtGui.QIcon( icon_file ))

        self.show()

    #///////////////////////////////////////////////////////////////////////////
    def layout_of_the_MainWindow(self):
        """
                MainApplication.layout_of_the_MainWindow
        """
        main_layout = QtGui.QVBoxLayout(self.mainWidget)

        self.sourcetext = SourceText(self.mainWidget, self)

        self.sourcetext.setStyleSheet(config.CONFIG_INI["aspect"]["sourcetext"])
        self.sourcetext.setFrameShape(QtGui.QFrame.StyledPanel)
        self.sourcetext.setReadOnly(True)

        self.notes = QtGui.QTextEdit(self.mainWidget)
        self.notes.setFrameShape(QtGui.QFrame.StyledPanel)
        self.notes.setStyleSheet(config.CONFIG_INI["aspect"]["notes"])

        splitter = QtGui.QSplitter(QtCore.Qt.Vertical)
        splitter.addWidget(self.sourcetext)
        splitter.addWidget(self.notes)
        splitter.setSizes( (400,300) )

        main_layout.addWidget(splitter)

    #///////////////////////////////////////////////////////////////////////////
    def define_known_actions(self):
        """
                MainApplication.define_known_actions
        """
        pass

    #///////////////////////////////////////////////////////////////////////////
    def define_the_main_toolbar(self):
        """
                MainApplication.define_the_main_toolbar
        """
        self.main_toolbar = self.addToolBar('MyToolBar')

        button_readinglevel = QtGui.QPushButton(self)
        button_readinglevel.setText(">>>")
        self.main_toolbar.addWidget( button_readinglevel )
        
        readinglevel_0 = QtGui.QRadioButton(self)
        readinglevel_0.setText("text")
        readinglevel_1 = QtGui.QRadioButton(self)
        readinglevel_1.setText("sentence")
        readinglevel_2 = QtGui.QRadioButton(self)
        readinglevel_2.setText("proposition")
        readinglevel_3 = QtGui.QRadioButton(self)
        readinglevel_3.setText("group of words")
        readinglevel_4 = QtGui.QRadioButton(self)
        readinglevel_4.setText("word")
        self.main_toolbar.addWidget( readinglevel_0 )
        self.main_toolbar.addWidget( readinglevel_1 )
        self.main_toolbar.addWidget( readinglevel_2 )
        self.main_toolbar.addWidget( readinglevel_3 )
        self.main_toolbar.addWidget( readinglevel_4 )

        button_action = QtGui.QPushButton(self)
        button_action.setText(">>>")
        self.main_toolbar.addWidget( button_action )

        self.toolbar_widget = QtGui.QWidget(self.main_toolbar)
        self.toolbar_layout = QtGui.QVBoxLayout()
        self.toolbar_widget.setLayout(self.toolbar_layout)

        self.toolbar_layout.addWidget(self.main_toolbar)
        
    #///////////////////////////////////////////////////////////////////////////
    def define_the_main_menubar(self):
        """
                MainApplication.define_the_main_menubar
        """

        menubar = self.menuBar()

        fileMenu = menubar.addMenu("&File")
        fileMenu.addSeparator()

        helpMenu = menubar.addMenu( "?" )
        helpMenu.addSeparator()

