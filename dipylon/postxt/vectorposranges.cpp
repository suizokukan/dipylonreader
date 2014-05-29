/*******************************************************************************

    Dipylon Copyright (C) 2008 Xavier Faure
    Contact: faure dot epistulam dot mihi dot scripsisti at orange dot fr

    This file is part of Dipylon.
    Dipylon is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Dipylon is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Dipylon.  If not, see <http://www.gnu.org/licenses/>.

    ____________________________________________________________________________

    ❏Dipylon❏ : postxt/vectorposranges.cpp

    see vectorposranges.h for the documentation

*******************************************************************************/

#include "postxt/vectorposranges.h"

/*______________________________________________________________________________

        PosRanges::PosRanges : constructor from a vector<PosRanges>
______________________________________________________________________________*/
VectorPosRanges::VectorPosRanges(std::vector<PosRanges> v) : std::vector<PosRanges>(v)
{
}

/*______________________________________________________________________________

        PosRanges::to_str : return a QString representation of this.

        NB : this function is debug-intended.
______________________________________________________________________________*/
QString VectorPosRanges::to_str(void)
{
  QString res = QString("");

  // i is an iterator over PosRanges objects :
  for(auto i = this->begin(); i!=this->end(); ++i)
  {
    res += i->to_str();
    res += this->MAIN_SEPARATOR;
  }

  // removing the last MAIN_SEPARATOR character :
  res.chop(1);

  return res;
}
