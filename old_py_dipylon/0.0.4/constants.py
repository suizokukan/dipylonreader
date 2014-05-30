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
        ❏Dipulon❏ constants.py

        * NOTE_ASPECT__WORD
        * NOTE_ASPECT__WORDS
        * NOTE_ASPECT__EXTRACT
"""

from PyQt4 import QtGui

# (Note) word aspect :
# for every aspect's name :
#
# * RGB color
#
NOTE_ASPECT__WORD = {
                        "default" : (0xDD0000),
                    }

# (Note) words aspect :
# for every aspect's name :
#
# * RGB color
#
NOTE_ASPECT__WORDS= {
                        "default" : (0x0000DD),
                    }

# (Note) extracts' aspect :
# for every aspect's name :
#
# * RGB color
# * underline style (http://pyqt.sourceforge.net/Docs/PyQt4/qtextcharformat.html#UnderlineStyle-enum)
#
NOTE_ASPECT__EXTRACT = {
                        "default" : (0x000000,
                                     QtGui.QTextCharFormat.SingleUnderline),
                       }
