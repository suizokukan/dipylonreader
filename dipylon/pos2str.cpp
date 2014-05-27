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

    ❏Dipylon❏ : pos2str.cpp

    see pos2str.h for more documentation

*******************************************************************************/

#include "pos2str.h"

/*______________________________________________________________________________

        Pos2Str:: constructor from a list of integers and strings.
______________________________________________________________________________*/
Pos2Str::Pos2Str( std::initializer_list< IntegersAndAString > values)
{
  // i : iterator over this->values :
  for(auto i = values.begin(); i != values.end(); ++i)
  {
    this->map.insert( std::pair<PosRanges, QString>( PosRanges(i->integers), 
                                                               i->string)
                    );
  }
}

/*______________________________________________________________________________

        Pos2Str::size() : return the size of the (private) object "map".
______________________________________________________________________________*/
size_t Pos2Str::size(void)
{
  return this->map.size();
}


/*______________________________________________________________________________

        Pos2Str::operator[]() : give access to the (private) object "map".
______________________________________________________________________________*/
QString& Pos2Str::operator[]( std::vector< std::pair<int, int> > key)
{
  return this->map[key];
}
