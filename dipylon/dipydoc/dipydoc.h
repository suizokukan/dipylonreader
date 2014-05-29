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

    ❏Dipylon❏ : dipydoc/dipydoc.h

    Define the DipyDoc class, dealing with DIPYDOC documents.

*******************************************************************************/

#ifndef DIPYDOC_H
#define DIPYDOC_H

#include "../postxt/pos2str.h"

#include <QString>
#include <QFileInfo>
#include <QTextStream>

class DipyDoc
{
    private:
        bool    _well_initialized;
        int     _internal_state;

        void    check_path(QString path);

    public:
        // constants used to define the internal_state attribute :
        const int INTERNALSTATE_OK = 0;
        const int INTERNALSTATE_UNKNOWNPATH = 1;
        const int INTERNALSTATE_PATHISAFILE = 2;
        const int INTERNALSTATE_MISSINGTEXT = 3;

        // name of the files in a dipydoc directory :
        const QString TEXTFILE_NAME = "text";

                DipyDoc(QString);
        int     internal_state(void) const;
        bool    well_initialized(void) const;

        QString text;
};

#endif
