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

import cgi
from gaps import Gaps
import xml.etree.ElementTree as ElementTree

################################################################################
class DipylonFile(object):

    #///////////////////////////////////////////////////////////////////////////    
    def __init__(self, filename):
        self.init_from_dipylon_file(filename)

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
            self.source_text = { "title" : self.root.find(_title).text,
                                 "author" : self.root.find(_author).text,
                                 "language" : self.root.find(_language).text,
                                 "source" : self.root.find(_source).text,
                                }

            self.datalanguages = {}
            for language in self.root.findall("./defined_languages/language"):

                language_name = language.text

                _title = "./header/language[@name='{0}']/informations/title".format(language_name)
                _author = "./header/language[@name='{0}']/informations/author".format(language_name)
                _workreference = "./header/language[@name='{0}']/informations/workreference".format(language_name)
                _translation = "./translations/language[@name='{0}']/extract".format(language_name)

                self.datalanguages[ language_name ] = { "title" : self.root.find(_title).text,
                                                    "author" : self.root.find(_author).text,
                                                    "workreference" : self.root.find(_workreference).text,
                                                    "translations" : {}
                                                    }

                for translation in self.root.findall(_translation):
                    gaps = Gaps().init_from_xmlrepresentation( translation.attrib["gaps"] )
                    self.datalanguages[ language_name ]["translations"][gaps.get_xmlrepresentation()] = translation.text

        return self
