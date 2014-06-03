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

    ❏Dipylon❏ : postxt/pos2str.cpp

    see pos2str.h for more documentation

*******************************************************************************/

#include "postxt/pos2str.h"

/*______________________________________________________________________________

        Pos2Str:: empty constructor.

                  initialize _well_initialized and _internal_state .
______________________________________________________________________________*/
Pos2Str::Pos2Str( void )
{
  this->_well_initialized = true;
  this->_internal_state = INTERNALSTATE_OK;
}

/*______________________________________________________________________________

        Pos2Str:: constructor from an initializer list of integers and strings.

                  initialize _well_initialized and _internal_state .

        E.g. :

          Pos2Str pos2str = {
            { {{ {10,11}, {13,14} },}, "example1"},
            { {{ {17,18}, {19,20} },}, "example2"},
            { {{ {21,22}, {23,28} },}, "example3"},
          };
______________________________________________________________________________*/
Pos2Str::Pos2Str( std::initializer_list< IntegersAndAString > values)
{
  this->_well_initialized = true;
  this->_internal_state = INTERNALSTATE_OK;

  // i : iterator over this->values :
  for(auto i = values.begin(); i != values.end(); ++i)
  {
    this->map.insert( std::pair<PosRanges, QString>( PosRanges(i->integers), 
                                                               i->string)
                    );
  }

  // is everything ok ?
  this->checks();
}

/*______________________________________________________________________________

        Pos2Str::operator[] : give access to the (private) object "map".
______________________________________________________________________________*/
QString& Pos2Str::operator[]( VectorPairTextPos key)
{
  return this->map[key];
}

/*______________________________________________________________________________

        Pos2Str::operator= : give access to the (private) object "map".

        see http://en.cppreference.com/w/cpp/language/move_operator
______________________________________________________________________________*/
Pos2Str& Pos2Str::operator=( Pos2Str&& other)
{
  this->_internal_state = other._internal_state;
  this->_well_initialized = other._well_initialized;
  this->map = std::move(other.map);
  return *this; 
}

/*______________________________________________________________________________

        Pos2Str::checks() : do some tests and if something's wrong,
                            modified _well_initialized and _internal_state .

        tests:

            o are the PosRanges objects well initialized ?
                if not, INTERNALSTATE_BADPOSRANGES

______________________________________________________________________________*/
void Pos2Str::checks(void)
{
  /*
    are the PosRanges objects ok ?
  */
  // i is an iterator over a pair<PosRanges, QString> :
  for(auto i = this->map.begin(); i != this->map.end(); ++i)
  {
    // i->first is a PosRanges object.
    if( i->first._well_initialized == false )
    {
      this->_well_initialized = false;
      this->_internal_state = INTERNALSTATE_BADPOSRANGES;
      return;
    }
  }
}

/*______________________________________________________________________________

        Pos2Str::internal_state : return the value of the private attribute
                                  this->_internal_state
_____________________________________________________________________________*/
int Pos2Str::internal_state(void) const
{
  return this->_internal_state;
}

/*______________________________________________________________________________

        Pos2Str::is_inside(TextPos x0) : search the first (PosRanges)key in this
                                         that matches this->key.is_inside(x0)

       This function returns a PosRanges. The result is an
       empty PosRanges if indexes in "this" do not contain "x0".

_____________________________________________________________________________*/
PosRanges Pos2Str::is_inside(TextPos x0) const
{
  // i is an iterator over a pair<PosRanges, QString> :
  for(auto i = this->map.begin(); i != this->map.end(); ++i)
  {
    // i->first is a PosRanges object.
    if( i->first.is_inside(x0) == true )
    {
      // ok, the searched PosRanges has been found and can be returned :
      return i->first;
    }
  }
 
  // no result : the function returns an empty vector.
  return PosRanges();
}

/*______________________________________________________________________________

        Pos2Str::is_inside(TextPos x0, x1) : search the first (PosRanges)key in this
                                             that matches this->key.is_inside(x0, x1)

       This function returns a vector of PosRanges. The result is an empty
       vector if this do not contain "x0...x1"

_____________________________________________________________________________*/
VectorPosRanges Pos2Str::is_inside(TextPos x0, TextPos x1) const
{
  std::vector<PosRanges> res;

  // i is an iterator over a pair<PosRanges, QString> :
  for(auto i = this->map.begin(); i != this->map.end(); ++i)
  {
    // i->first is a PosRanges object.
    if( i->first.is_inside(x0, x1) == true )
    {
      // ok, the searched PosRanges has been found :
      res.push_back( i->first );
    }
  }

  return res;
}

/*______________________________________________________________________________

        Pos2Str::size() : return the size of the (private) object "map".
______________________________________________________________________________*/
size_t Pos2Str::size(void) const
{
  return this->map.size();
}

/*______________________________________________________________________________

        Pos2Str::well_initialized() : return the value of the private attribute
                                      this->_well_initialized
_____________________________________________________________________________*/
bool Pos2Str::well_initialized(void) const
{
  return this->_well_initialized;
}


