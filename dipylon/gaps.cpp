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

#include <vector>

#include <QString>
#include <QStringList>

#include <QtWidgets>

/*______________________________________________________________________________

        Gaps::Gaps() (constructor from a QString). 

        Initialize vec, (int)_internal_state and (bool)_well_initialized.

        If an error occurs, _well_initialized is set to false and
        _internal_state explains the error.
______________________________________________________________________________*/
Gaps::Gaps(QString *src_qstring)
{
  // we create an empty vector :
  this->vec = std::vector<std::pair<int,int> >();

  // error : if src_qstring is empty, the initialisation can't be correct :
  this->_well_initialized = (src_qstring->size() > 0);
  
  // shall we go further ?
  if( this->_well_initialized == false )
  {
    // ... no.
    this->_internal_state = this->INTERNALSTATE_EMPTYSTR;
    return;
  }

  this->_internal_state = this->INTERNALSTATE_OK;

  // let's initialize this vector from src_qstring :
  QStringList splitted_strings = src_qstring->split(this->MAIN_SEPARATOR);
  if( splitted_strings.length() == 0 )
  {
    // error : ill-formed src_qstring (no MAIN_SEPARATOR)
    this->_well_initialized = false;
    this->_internal_state = this->INTERNALSTATE_NOMAINSEP;
    return;
  }

  QStringList::const_iterator i;
  for (i = splitted_strings.constBegin(); i != splitted_strings.constEnd(); ++i)
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
  if( this->vec.size() == 0 )
    {
      this->_well_initialized = false;
      this->_internal_state = this->INTERNALSTATE_EMPTYVEC;
    }
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

  std::vector < std::pair<int,int> >::iterator i;

  for (i = this->vec.begin(); i != this->vec.end(); ++i)
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

        Gaps::toStr() : return a QString representing the object according to
                        the GAP_STR format (see above)                     
______________________________________________________________________________*/
QString Gaps::toStr(void)
{
  QString res("");

  // empty vector ? nothing to do.
  if( this->vec.empty() )
  {
    return res;
  }

  // we go through the object with an iterator :
  std::vector < std::pair<int,int> >::iterator i;

  for (i = this->vec.begin(); i != this->vec.end(); ++i)
    {
      res += QString().number( i->first );
      res += this->MAIN_SEPARATOR;
      res += QString().number( i->second );
      res += this->SECONDARY_SEPARATOR;
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
