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

      Use Gaps objects to store a list of integers. Gaps objects are nothing
    but vector<pair<int,int>> .

      A Gaps object can be initialized from a QString (see GAPS_STR infra).
      After beeing initialized, check the (bool)well_initialized attribute.

    GAPS_STR format : "45-97", "45-97+123-136+999-1001", ...
        no spaces allowed.
        MAIN_SEPARATOR, SECONDARY_SEPARATOR : only one character.
        at least one gap must be defined (no empty string)
        x0 must be <= x1 (no "45-22")

*******************************************************************************/

#include "gaps.h"
#include <QString>
#include <QStringList>

/*______________________________________________________________________________

        Gaps::Gaps (constructor from a QString). 

        Initialize well_initialized (=either true if everything's ok, either 
        false).
______________________________________________________________________________*/
Gaps::Gaps(QString *string)
{
  this->well_initialized = true;

  QStringList splitted_string = string->split(this->MAIN_SEPARATOR);

  QStringList::const_iterator i;
  for (i = splitted_string.constBegin(); i != splitted_string.constEnd(); ++i)
    {
        QStringList x0x1 = i->split(this->SECONDARY_SEPARATOR);
        int x0 = x0x1[0].toInt();
        int x1 = x0x1[0].toInt();
        this->push_back( std::make_pair(x0,x1) );

        // see GAPS_STR format : x0 must be <= x1
        if (x0 > x1)
        {
          this->well_initialized = false;
        }
    }

  // see GAPS_STR format : at least one gap must be defined.
  if( this->size() == 0 )
  {
    this->well_initialized = false;
  }
}

/*______________________________________________________________________________

        Gaps::toStr : return a QString representing the object according to
                      the GAP_STR format (see above)                     
______________________________________________________________________________*/
QString Gaps::toStr(void)
{
  QString res("");

  // empty vector ? nothing to do.
  if( this->empty() )
  {
    return res;
  }

  // we go through the object with an iterator :
  vector < std::pair<int,int> >::iterator i;

  for (i = this->begin(); i != this->end(); ++i)
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

        Gaps::is_inside : return either true if (int)v is inside one gap of the
                          object, either false.
______________________________________________________________________________*/
bool Gaps::is_inside(int v)
{
  bool res = false;

  vector < std::pair<int,int> >::iterator i;

  for (i = this->begin(); i != this->end(); ++i)
    {
      if( (i->first <= v) && (v <= i->second) )
      {
        res = true;
        break;
      }        
    }

  return res;
}
