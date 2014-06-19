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
"""

from PyQt4 import QtGui
from PyQt4 import QtCore
import os

from constants import NOTE_ASPECT__WORD, NOTE_ASPECT__WORDS, NOTE_ASPECT__EXTRACT
from dipylonfile import DipylonFile
import config


################################################################################
class ReadingMode(object):
    """
        class ReadingMode
    """

    #///////////////////////////////////////////////////////////////////////////
    def __init__(self, default_mode = "word"):
        """
                ReadingMode.__init__
        """
        self.value = default_mode

    #///////////////////////////////////////////////////////////////////////////
    def get_usr_representation(self):
        """
                ReadingMode.get_usr_representation
        """
        return self.value

    #///////////////////////////////////////////////////////////////////////////
    def next_reading_mode(self):
        """
                ReadingMode.__init__
        """

        if self.value == "word":
            self.value = "sentence"

        elif self.value == "sentence":
            self.value = "word"

        else:
            raise Exception

################################################################################
class TextHighlighted(QtGui.QTextEdit):
    """
        class TextHighlighted
    """

    #///////////////////////////////////////////////////////////////////////////
    def __init__(self, parent, MainApplication_object):
        """
                TextHighlighted.__init__
        """
        QtGui.QTextEdit.__init__(self, parent)

        self.MainApplication_object = MainApplication_object

    #///////////////////////////////////////////////////////////////////////////
    def keyPressEvent(self, ev):
        """
                TextHighlighted.keyPressEvent
        """
        print("extHighlighted.keyPressEvent", ev.key())
        key = ev.key()

        if key == 32:
            # SPACE
            self.MainApplication_object.reading_mode.next_reading_mode()
            self.MainApplication_object.show_reading_mode()
            
        QtGui.QTextEdit.keyPressEvent(self,ev)

    #///////////////////////////////////////////////////////////////////////////
    def mousePressEvent(self, ev):
        """
                TextHighlighted.mousePressEvent
        """
        self.MainApplication_object.commentary.setText(
            "(mousePressEvent)" +\
            "anchor=" + str(self.anchorAt(ev.pos()))+\
            "pos=" + str(self.cursorForPosition(ev.pos()).positionInBlock())
            )

        QtGui.QTextEdit.mousePressEvent(self,ev)

    #///////////////////////////////////////////////////////////////////////////
    def mouseReleaseEvent(self, ev):
        """
                TextHighlighted.mouseReleaseEvent
        """

        cursor = self.textCursor()
        print("TextHighlighted.mouseReleaseEvent", cursor.selectedText(), cursor.hasSelection(), cursor.selectionStart(), cursor.selectionEnd())

        if not cursor.hasSelection():
            # something has been selected :
            notes = self.MainApplication_object.dipylonfile.get_notes(
                cursor_position = cursor.position(),
                language = self.MainApplication_object.user_language)

            for note in notes:
                for x0, x1 in note.gaps:
                    
                    cursor.setPosition(x0)
                    cursor.movePosition(QtGui.QTextCursor.Right, QtGui.QTextCursor.KeepAnchor, x1-x0+1)
                    modified_format = cursor.charFormat()

                    if note.category == 'word':
                        color = NOTE_ASPECT__WORD[note.aspect]
                        qcolor = QtGui.QColor().fromRgb(color)
                        modified_format.setForeground( QtGui.QBrush(qcolor) )

                    elif note.category == 'words':
                        color = NOTE_ASPECT__WORDS[note.aspect]
                        qcolor = QtGui.QColor().fromRgb(color)
                        qcolor.setAlpha(50)
                        modified_format.setBackground( QtGui.QBrush(qcolor) )

                    elif note.category == 'extract':
                        underline_color, underline_style = NOTE_ASPECT__EXTRACT[note.aspect]
                        qcolor = QtGui.QColor().fromRgb(underline_color)
                        modified_format.setUnderlineColor(qcolor)
                        modified_format.setUnderlineStyle(underline_style)
                        modified_format.setFontItalic(True)

                    else:
                        raise Exception

                    # we merge the current format with the modified format :
                    cursor.mergeCharFormat(modified_format)

        QtGui.QTextEdit.mouseReleaseEvent(self, ev)

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

        self.reading_mode = ReadingMode()
        self.show_reading_mode()
        
        self.define_the_main_menubar()

        self.mainWidget=QtGui.QWidget(self) # this widget contains the layout manage
        self.setCentralWidget(self.mainWidget)
        self.layout_of_the_MainWindow()

        QtGui.QApplication.setStyle(QtGui.QStyleFactory.create('Cleanlooks'))
        self.setWindowTitle('Dipylon')
        self.setWindowIcon(QtGui.QIcon('icon64x64.jpg'))

        # language used by the user :
        self.user_language = "fra"

        if input_textfile is not None:
            self.load_a_dipylonfile(filename = input_textfile)

        self.show()

    #///////////////////////////////////////////////////////////////////////////
    def action__open_a_file(self):
        """
                MainApplication.action__open_a_file

                File > Open
        """

        filename = QtGui.QFileDialog.getOpenFileName(self,
                                                      'Open file',
                                                      '.',
                                                      "dipylon (*.dipylon);; all (*)",
                                                      QtGui.QFileDialog.ReadOnly,
                                                      )

        if filename != "":
            self.file = QtCore.QFile(filename)
            if self.file.open(QtCore.QIODevice.ReadOnly):

                self.load_a_dipylonfile(filename)
            else:
                # pan !
                raise Exception("!")

    #///////////////////////////////////////////////////////////////////////////
    def layout_of_the_MainWindow(self):
        """
                MainApplication.layout_of_the_MainWindow
        """
        main_layout = QtGui.QVBoxLayout(self.mainWidget)

        self.text_highlighted = TextHighlighted(self.mainWidget, self)

        self.text_highlighted.setStyleSheet(config.CONFIG_INI["aspect"]["main editor"])
        self.text_highlighted.setFrameShape(QtGui.QFrame.StyledPanel)
        self.text_highlighted.setReadOnly(True)

        self.commentary = QtGui.QTextEdit(self.mainWidget)
        self.commentary.setFrameShape(QtGui.QFrame.StyledPanel)
        self.commentary.setStyleSheet(config.CONFIG_INI["aspect"]["notes editor"])

        splitter = QtGui.QSplitter(QtCore.Qt.Vertical)
        splitter.addWidget(self.text_highlighted)
        splitter.addWidget(self.commentary)
        splitter.setSizes( (400,300) )

        main_layout.addWidget(splitter)

    #///////////////////////////////////////////////////////////////////////////
    def define_known_actions(self):
        """
                MainApplication.define_known_actions
        """

        #   We define the path where lies the files from this source code file; this
        # method allows to launch the code from another path that the usual
        # 'root path'.
        icon_file = os.path.abspath(os.path.join(os.path.abspath( os.path.dirname( __file__)),
                                                 "icons",
                                                 "exit.jpg" ))
        self.MenuAction__Exit = QtGui.QAction(QtGui.QIcon(icon_file), "&Exit", self)
        self.MenuAction__Exit.setShortcut('Ctrl+Q')
        self.MenuAction__Exit.setStatusTip( "Exit" )
        self.MenuAction__Exit.triggered.connect(QtGui.qApp.quit)

        self.MenuAction__Load = QtGui.QAction( "&Load", self)
        self.MenuAction__Load.setShortcut('Ctrl+O')
        self.MenuAction__Load.setStatusTip( "&Load" )
        self.MenuAction__Load.triggered.connect(self.action__open_a_file)

        self.MenuAction__Save = QtGui.QAction( "&Save", self)
        self.MenuAction__Save.setShortcut('Ctrl+S')
        self.MenuAction__Save.setStatusTip( "&Save" )

        self.MenuAction__Help = QtGui.QAction( "&Help", self)
        self.MenuAction__Help.setStatusTip( "&Help" )
        self.MenuAction__Help.triggered.connect(self.event__MenuAction__Help)

        self.MenuAction__About = QtGui.QAction( "&About Dipylon", self)
        self.MenuAction__About.setStatusTip( "&About Dipylon" )
        self.MenuAction__About.triggered.connect(self.event__MenuAction__About)

        icon_file = os.path.abspath(os.path.join(os.path.abspath( os.path.dirname( __file__)),
                                                 "icons",
                                                 "POV_1.png" ))
        self.MenuAction__PointOfView_Char = QtGui.QAction(QtGui.QIcon(icon_file), 'POV1', self)
        self.MenuAction__PointOfView_Char.triggered.connect(QtGui.qApp.quit)

        icon_file = os.path.abspath(os.path.join(os.path.abspath( os.path.dirname( __file__)),
                                                 "icons",
                                                 "POV_2.png" ))
        self.MenuAction__PointOfView_Segment = QtGui.QAction(QtGui.QIcon(icon_file), 'POV2', self)
        self.MenuAction__PointOfView_Segment.triggered.connect(QtGui.qApp.quit)

        icon_file = os.path.abspath(os.path.join(os.path.abspath( os.path.dirname( __file__)),
                                                 "icons",
                                                 "POV_3.png" ))
        self.MenuAction__PointOfView_Phrase = QtGui.QAction(QtGui.QIcon(icon_file), 'POV3', self)
        self.MenuAction__PointOfView_Phrase.triggered.connect(QtGui.qApp.quit)

        icon_file = os.path.abspath(os.path.join(os.path.abspath( os.path.dirname( __file__)),
                                                 "icons",
                                                 "POV_4.png" ))
        self.MenuAction__PointOfView_Sentence = QtGui.QAction(QtGui.QIcon(icon_file), 'POV4', self)
        self.MenuAction__PointOfView_Sentence.triggered.connect(QtGui.qApp.quit)

    #///////////////////////////////////////////////////////////////////////////
    def define_the_main_toolbar(self):
        """
                MainApplication.define_the_main_toolbar
        """
        self.main_toolbar = self.addToolBar('Exit')
        self.main_toolbar.addAction(self.MenuAction__PointOfView_Char)
        self.main_toolbar.addAction(self.MenuAction__PointOfView_Segment)
        self.main_toolbar.addAction(self.MenuAction__PointOfView_Phrase)
        self.main_toolbar.addAction(self.MenuAction__PointOfView_Sentence)

        Combo__list_of_the_grammatical_structures = QtGui.QComboBox(self)
        Combo__list_of_the_grammatical_structures.addItem("1111111111111")
        Combo__list_of_the_grammatical_structures.addItem("2222222222")
        Combo__list_of_the_grammatical_structures.addItem("333333")
        self.main_toolbar.addWidget( Combo__list_of_the_grammatical_structures )

    #///////////////////////////////////////////////////////////////////////////
    def define_the_main_menubar(self):
        """
                MainApplication.define_the_main_menubar
        """

        menubar = self.menuBar()

        fileMenu = menubar.addMenu("&File")
        fileMenu.addAction(self.MenuAction__Load)
        fileMenu.addAction(self.MenuAction__Save)
        fileMenu.addSeparator()
        fileMenu.addAction(self.MenuAction__Exit)

        helpMenu = menubar.addMenu( "?" )
        helpMenu.addAction(self.MenuAction__Help)
        helpMenu.addSeparator()
        helpMenu.addAction(self.MenuAction__About)

    #///////////////////////////////////////////////////////////////////////////
    def event__MenuAction__About(self):
        """
                MainApplication.event__MenuAction__About
        """
        self.commentary.setText("about ...")

    #///////////////////////////////////////////////////////////////////////////
    def event__MenuAction__Help(self):
        """
                MainApplication.event__MenuAction__Help
        """
        self.commentary.setText("help ...")

    #///////////////////////////////////////////////////////////////////////////
    def load_a_dipylonfile(self, filename):
        """
                MainApplication.load_a_dipylonfile
        """
        self.dipylonfile = DipylonFile(filename)

        file = QtCore.QFile(filename)
        if file.open(QtCore.QIODevice.ReadOnly):
            stream = QtCore.QTextStream(file)
            self.text_highlighted.setHtml(self.dipylonfile.text)

            if self.dipylonfile.source_text['font'] == 'default':
                pass
            elif self.dipylonfile.source_text['font'] == 'fixed-width':
                self.text_highlighted.setFont( QtGui.QFont('DejaVu LGC Sans Mono') )
            else:
                raise Exception

        else:
            raise Exception("$$$ pan $$$")

    #///////////////////////////////////////////////////////////////////////////
    def show_reading_mode(self):
        """
                MainApplication.show_reading_mode
        """
        self.statusBar.showMessage("MODE : "+str(self.reading_mode.get_usr_representation()))
        