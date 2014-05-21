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

    Use Gaps objects to store a list of integers.

    GAP_STR format : "45-97+123-136+999-1001", no spaces allowed.

*******************************************************************************/

#include "gaps.h"
#include <QString>

/*______________________________________________________________________________

        Gaps::Gaps (constructor from a QString)
        
______________________________________________________________________________*/
Gaps::Gaps(QString *string)
{
/*
  QStringList splitted_string = string->split("+");

  QStringList::const_iterator constIterator;
  for (constIterator = splitted_string.constBegin(); 
       constIterator != splitted_string.constEnd();
       ++constIterator)
    {
        QStringList x0x1 = constIterator->split("-");
        this->push_back( std::make_pair(x0x1[0].toInt(),
                                        x0x1[1].toInt()) );
    }
*/
}

/*______________________________________________________________________________

        Gaps::toStr : return a QString representing the object according to
                      the GAP_STR format (see above)                     
        
______________________________________________________________________________*/
QString Gaps::toStr(void)
{
  QString res("");

  // empty vector ? nothing to do.
/*
  if( this->empty() )
  {
    return res;
  }

  vector < std::pair<int,int> >::iterator i;

  for (i = this->begin(); i != this->end(); ++i)
    {
      res += QString().number( (*i).first );
      res += "+";
      res += QString().number( (*i).second );
      res += "-";
    }

  res.chop(1);
*/
  return res;
}
