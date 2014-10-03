from PyQt4 import QtGui
from PyQt4 import QtCore
import sys
import os.path

class Zone1(QtGui.QFrame):

    def __init__(self, parent):
        QtGui.QFrame.__init__(self, parent)

#        self.MenuAction__Open = QtGui.QPushButton()
#        self.MenuAction__Save = QtGui.QPushButton()
#
#        self.edit1 = QtGui.QTextEdit(parent=self)
#        self.toolbox1 = QtGui.QToolBox(parent=self)
#
#        self.toolbox1.addItem(self.MenuAction__Open,
#                              QtGui.QIcon( 'open.png' ),
#                              "")
#
#        self.toolbox1.addItem(self.MenuAction__Save,
#                              QtGui.QIcon( 'save.png' ),
#                              "")
#
#        self.layout = QtGui.QHBoxLayout(self)
#        self.layout.addWidget(self.toolbox1)
#        self.layout.addWidget(self.edit1)

        self.setObjectName("myObject");
        self.setStyleSheet("#myObject { border: 5px solid green; padding: 0px}");

        #self.setFrameStyle(QtGui.QFrame.NoFrame);
        #self.setLineWidth(0)
        #self.setContentsMargins(0,0,0,0)

        self.edit1 = QtGui.QTextEdit(parent=self)
        self.toolbar1 = QtGui.QToolBar(parent=self)
        self.toolbar1.setFloatable(True)

        self.MenuAction__Open = QtGui.QAction("&Open", self)
        self.MenuAction__Open.setIcon(QtGui.QIcon( 'open.png'))
        self.MenuAction__Save = QtGui.QAction("&Save", self)
        self.MenuAction__Save.setIcon(QtGui.QIcon( 'save.png'))

        self.toolbar1.addAction(self.MenuAction__Open)
        self.toolbar1.addSeparator()
        self.toolbar1.addAction(self.MenuAction__Save)

        self.toolbar1.setOrientation(QtCore.Qt.Vertical)

        self.layout = QtGui.QHBoxLayout(self)
        self.layout.addWidget(self.toolbar1)
        self.layout.addWidget(self.edit1)

        self.setLayout(self.layout)

################################################################################
class MainApplication(QtGui.QMainWindow):

    #///////////////////////////////////////////////////////////////////////////
    def __init__(self, input_textfile = None):
        """
                MainApplication.__init__
        """

        QtGui.QMainWindow.__init__(self)

        self.splitter = QtGui.QSplitter(QtCore.Qt.Vertical)
        self.setCentralWidget(self.splitter)

        self.zone1 = Zone1(parent=self)
        self.zone2 = QtGui.QTextEdit(parent=self)

        self.splitter.addWidget(self.zone1)
        self.splitter.addWidget(self.zone2)

        QtGui.QApplication.setStyle(QtGui.QStyleFactory.create('Cleanlooks'))

        self.setStyleSheet("QFrame {border: 1px solid red}")

        self.show()


app = QtGui.QApplication(sys.argv)

application = MainApplication()
application.show()

app.exec_()
