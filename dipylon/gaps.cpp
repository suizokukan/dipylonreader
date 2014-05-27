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

    ❏Dipylon❏ : gaps.cpp

    see gaps.h for the documentation

*******************************************************************************/

#include "gaps.h"
#include "hash.h"

#include <vector>
#include <string>

#include <QString>
#include <QStringList>

/*______________________________________________________________________________

        int Gaps::Gaps : constructor from a QString.

        Initialize vec, (int)_internal_state and (bool)_well_initialized.

        If an error occurs, _well_initialized is set to false and
        _internal_state explains the error.
______________________________________________________________________________*/
Gaps::Gaps(const QString& src_qstring)
{
  this->vec = std::vector<std::pair<int,int> >();
  this->_internal_state = this->INTERNALSTATE_OK;

  // error : if src_qstring is empty, the initialisation can't be correct :
  this->_well_initialized = (src_qstring.size() > 0);
  
  // shall we go further ?
  if( this->_well_initialized == false )
  {
    // ... no.
    this->_internal_state = this->INTERNALSTATE_EMPTY;
    return;
  }

  // let's initialize this vector from src_qstring :
  QStringList splitted_strings = src_qstring.split(this->MAIN_SEPARATOR);
  if( splitted_strings.length() == 0 )
  {
    // error : ill-formed src_qstring (no MAIN_SEPARATOR)
    this->_well_initialized = false;
    this->_internal_state = this->INTERNALSTATE_NOMAINSEP;
    return;
  }

  // i is a QStringList iterator :
  for (auto i = splitted_strings.constBegin(); i != splitted_strings.constEnd(); ++i)
    {
      QStringList x0x1 = i->split(this->SECONDARY_SEPARATOR);

      if( x0x1.length() != 2 )
      {
         // error : ill-formed src_qstring :
         this->_well_initialized = false;
         this->_internal_state = this->INTERNALSTATE_SECONDSEP;
         break;
      }
      else
      {
        int x0 = x0x1[0].toInt();
        int x1 = x0x1[1].toInt();
        this->vec.push_back( std::make_pair(x0,x1) );

        // see GAPS_STR format : x0 must be < x1
        if (x0 >= x1)
          {
            this->_well_initialized = false;
            this->_internal_state = this->INTERNALSTATE_X0X1;
            break;
          }
      }
    }

  // see GAPS_STR format : at least one gap must be defined.
  if( this->_well_initialized == true && 
      this->vec.size() == 0 )
  {
      this->_well_initialized = false;
      this->_internal_state = this->INTERNALSTATE_EMPTY;
      return;
  }

  // last check : no overlapping ?
  if ( this->check_overlapping() == true )
  {
    this->_well_initialized = false;
    this->_internal_state = this->INTERNALSTATE_OVERLAPPING;
  }
}

/*______________________________________________________________________________

        int Gaps::Gaps : constructor from a list of pair of integers.

        Initialize vec, (int)_internal_state and (bool)_well_initialized.

        If an error occurs, _well_initialized is set to false and
        _internal_state explains the error.
______________________________________________________________________________*/
Gaps::Gaps(std::initializer_list< std::pair<int, int> > values) : vec(values)
{
  this->_internal_state = this->INTERNALSTATE_OK;

  // error : if values is empty, the initialisation can't be correct :
  this->_well_initialized = (values.size() > 0);
  
  // shall we go further ?
  if( this->_well_initialized == false )
  {
    // ... no.
    this->_internal_state = this->INTERNALSTATE_EMPTY;
    return;
  }

  // X0X1 test :
  for (auto i = this->vec.begin(); i != this->vec.end(); ++i)
    {
        if (i->first >= i->second)
          {
            this->_well_initialized = false;
            this->_internal_state = this->INTERNALSTATE_X0X1;
            break;
          }
    }

  // last check : no overlapping ?
  if ( this->check_overlapping() == true )
  {
    this->_well_initialized = false;
    this->_internal_state = this->INTERNALSTATE_OVERLAPPING;
  }
}

/*______________________________________________________________________________

        Gaps::internal_state() : return true if two gaps or more overlap 
                                 themselves.
______________________________________________________________________________*/
bool Gaps::check_overlapping(void)
{
  bool res = false;

  // i, j are std::vector < std::pair<int,int> >
  for (auto i = this->vec.begin(); i != this->vec.end(); ++i)
  {
    for (auto j = this->vec.begin(); j != this->vec.end(); ++j)
    {
      if( i != j )
      {
        if( ((i->first < j->first) && (j->first < i->second)) ||
            ((i->first < j->second) && (j->second < i->second)) )
        {
          res = true;
          break;
        }
      }
    }

    if( res == true )
    {
      break;
    }
  }

  return res;
}

/*______________________________________________________________________________

        Gaps::internal_state() : return the value of the private attribute
                                 this->_internal_state

                                 see INTERNALSTATE_* constants.

        NB : this function is debug-intended.
______________________________________________________________________________*/
int Gaps::internal_state(void)
{
  return this->_internal_state;
}

/*______________________________________________________________________________

        Gaps::is_inside() : return either true if (int)v is inside one gap of the
                            object, either false.
______________________________________________________________________________*/
bool Gaps::is_inside(int v)
{
  bool res = false;

  // i is a std::vector < std::pair<int,int> > iterator.
  for (auto i = this->vec.begin(); i != this->vec.end(); ++i)
    {
      if( (i->first <= v) && (v <= i->second) )
      {
        res = true;
        break;
      }        
    }

  return res;
}

/*______________________________________________________________________________

        Gaps::size() : return the size of the (private)vec.
______________________________________________________________________________*/
size_t Gaps::size(void)
{
  return this->vec.size();
}

/*______________________________________________________________________________

        Gaps::to_str() : return a QString representing the object according to
                        the GAP_STR format (see above)                     
______________________________________________________________________________*/
QString Gaps::to_str(void)
{
  QString res("");

  // empty vector ? nothing to do.
  if( this->vec.empty() )
  {
    return res;
  }

  // we go through the object with an iterator :
  // i is a std::vector < std::pair<int,int> > iterator
  for (auto i = this->vec.begin(); i != this->vec.end(); ++i)
    {
      res += QString().number( i->first );
      res += this->SECONDARY_SEPARATOR;
      res += QString().number( i->second );
      res += this->MAIN_SEPARATOR;
    }

  // removing the last SECONDARY_SEPARATOR character :
  res.chop(1);

  return res;
}

/*______________________________________________________________________________

        Gaps::well_initialized() : return the value of the private attribute
                                   this->_well_initialized.
______________________________________________________________________________*/
bool Gaps::well_initialized(void)
{
    return this->_well_initialized;
}

/*______________________________________________________________________________

        Gaps::==() : defines the comparison between two Gaps objects
______________________________________________________________________________*/
bool Gaps::operator==(const Gaps& aliud)
{
  return (this->_well_initialized == aliud._well_initialized) && (this->vec == aliud.vec);
}

/*______________________________________________________________________________

        Gaps::!=() : defines the comparison between two Gaps objects
______________________________________________________________________________*/
bool Gaps::operator!=(const Gaps& aliud)
{
  return !(this->operator==(aliud));
}

/*______________________________________________________________________________

        GapsHasher::operator()

        from a David Schwartz idea (http://stackoverflow.com/questions/23859844)

______________________________________________________________________________*/
std::size_t GapsHasher::operator()(const Gaps& k) const
{
  {
    std::size_t hash = 0;
    for (auto i = k.vec.begin(); i != k.vec.end(); ++i)
    {
      hash_combine( hash, i->first);
      hash_combine( hash, i->second);
    }
    return hash;
  }
}
