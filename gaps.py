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
        ❏Dipulon❏ gaps.py
"""

################################################################################
class Gaps(list):
    """
        class Gaps

        A Gaps object is a list of 2-tuplet, like [ (3,5), (9,10) ]
    """

    #///////////////////////////////////////////////////////////////////////////
    def __repr__(self):
        """
                Gaps.__repr__
        """
        return "Gaps"+list.__repr__(self)

    #///////////////////////////////////////////////////////////////////////////
    def contain_a_position(self, pos):
        """
                Gaps.contain_a_position
        """
        res = False
        
        for gap in self:
            if gap[0] <= pos <= gap[1]:
                res = True
                break
            
        return res


    #///////////////////////////////////////////////////////////////////////////
    def get_xmlrepresentation(self):
        """
                Gaps.get_xmlrepresentation
        """
        res = []
        for gap in self:
            res.append( str(gap[0]) + "..." + str(gap[1]) )
        return ";".join(res)

    #///////////////////////////////////////////////////////////////////////////
    def init_from_xmlrepresentation(self, src):
        """
                Gaps.init_from_xmlrepresentation

                src     : (str) like "0...4;9...12"
        """
        self.clear()

        for str_gap in src.split(";"):
            three_dots = str_gap.find("...")
            x0 = int(str_gap[:three_dots])
            x1 = int(str_gap[three_dots+len("..."):])
            self.append( (x0,x1) )

        return self
