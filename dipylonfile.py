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
        ❏Dipulon❏ dipylonfile.py
"""

# doc de référence :
# http://pyqt.sourceforge.net/Docs/PyQt4/classes.html

import cgi
from gaps import Gaps
import xml.etree.ElementTree as ElementTree

LISTOFNOTESCATEGORIES = ["word",
                         "words",
                         "extract"]

################################################################################
class Note(object):
    def __init__(self, gaps, corresponding_text, note, category, aspect):
        self.gaps = gaps
        self.corresponding_text = corresponding_text
        self.note = note
        self.category = category
        self.aspect = aspect

    def __repr__(self):
        msg = "(Note) gaps={0}; corresponding_text={1}; note={2}; aspect={3}"
        return msg.format(self.gaps,
                          self.corresponding_text,
                          self.note,
                          self.aspect)                                                                           

################################################################################
class DipylonFile(object):

    #///////////////////////////////////////////////////////////////////////////    
    def __init__(self, filename):
        self.init_from_dipylon_file(filename)

    #///////////////////////////////////////////////////////////////////////////
    def get_notes(self, cursor_position, category = None):
        """
                DipylonFile.get_notes
                
                Return the notes relative to a <cursor_position> and belonging
                to a certain <category>. If <category> is equal to None, all
                categories may be added to the result.
        """
        res = []
        
        if category is not None:
            _categories = (category,)
        else:
            _categories = LISTOFNOTESCATEGORIES[:]

        for _category in _categories:
            for _gaps in self.datalanguages['fra']['notes'][_category]:
                gaps = Gaps().init_from_xmlrepresentation(_gaps)

                if gaps.contain_a_position(cursor_position):

                    note = self.datalanguages['fra']['notes'][_category][gaps.get_xmlrepresentation()]
                    
                    res.append( Note( gaps = gaps,
                                      corresponding_text = note['corresponding_text'],
                                      note = note['note'],
                                      category = _category,
                                      aspect = note['aspect'],
                                      ))

        return res

    #///////////////////////////////////////////////////////////////////////////
    def init_from_dipylon_file(self, filename):

        with open(filename, 'r') as srcfile:

            text = []
            xmldata = []
            inside_xml = False
            for _line in srcfile.readlines():
                line = _line[:-1]
                
                if line == '*=*=*':
                    inside_xml = True
                elif not inside_xml:
                    text.append(line)
                else:
                    xmldata.append(line)

            self.text = "\n".join(text)
            self.text = self.text.replace("\n", "<br/>")
            self.text = self.text.replace(" ", "&nbsp;")

            self.root = ElementTree.fromstring("\n".join(xmldata))

            self.dipylon_format_file = self.root.find("./dipylon_format_file").text

            _title = "./source_text/title"
            _author= "./source_text/author"
            _language = "./source_text/language"
            _source = "./source_text/source"
            _font = "./source_text/font"
            self.source_text = { "title"        : self.root.find(_title).text,
                                 "author"       : self.root.find(_author).text,
                                 "language"     : self.root.find(_language).text,
                                 "source"       : self.root.find(_source).text,
                                 "font"         : self.root.find(_font).text
                                }

            self.datalanguages = {}
            for language in self.root.findall("./defined_languages/language"):

                language_name = language.text

                _title = "./header/language[@name='{0}']/informations/title".format(language_name)
                _author = "./header/language[@name='{0}']/informations/author".format(language_name)
                _workreference = "./header/language[@name='{0}']/informations/workreference".format(language_name)
                self.datalanguages[ language_name ] = { "title" : self.root.find(_title).text,
                                                    "author" : self.root.find(_author).text,
                                                    "workreference" : self.root.find(_workreference).text,
                                                    "translations" : {},
                                                    "notes" : dict( (cat,{}) for cat in LISTOFNOTESCATEGORIES )
                                                    }

                _translations = "./translations/language[@name='{0}']/extract".format(language_name)
                
                for translation in self.root.findall(_translations):
                    gaps = Gaps().init_from_xmlrepresentation( translation.attrib["gaps"] )
                    self.datalanguages[ language_name ]["translations"][gaps.get_xmlrepresentation()] = translation.text

                _notes = "./notes/language[@name='{0}']/note".format(language_name)
                
                for note in self.root.findall(_notes):
                    gaps = Gaps().init_from_xmlrepresentation( note.attrib["gaps"] )
                    corresponding_text = note.attrib["corresponding_text"]
                    category = note.attrib["category"]
                    aspect = note.attrib["aspect"]
                    
                    self.datalanguages[ language_name ]["notes"][category][gaps.get_xmlrepresentation()] = {"note" : note.text,
                                                                                                            "corresponding_text" : corresponding_text,
                                                                                                            "aspect" : aspect,
                                                                                                            }

        return self
