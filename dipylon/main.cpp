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

    ❏Dipylon❏ : main.cpp

*******************************************************************************/

#include "qt/dipylonui.h"

#include <QApplication>

//$$$
#include "pos/posinaudio2posintext.h"
#include "pos/posintext/posintextranges.h"
#include "pos/posintext/vectorposintextranges.h"
#include "pos/posintext2posinaudio.h"
#include <QDebug>

/*______________________________________________________________________________

  Main entry point.

  See http://qt-project.org/doc/qt-5/qapplication.html#QApplication about "argc"
  and "argv".
______________________________________________________________________________*/
int main(int argc, char **argv)
{
    Q_INIT_RESOURCE(dipylon);

    // $$$
    PosInTextRanges p1 = PosInTextRanges();
    PosInTextRanges p2 = PosInTextRanges("94-107+98-109");
    qDebug() << p2.to_str();
    qDebug() << p2.contains(95);
    qDebug() << p2.contains(95,109);
    qDebug() << p2.size();
    PosInTextRanges p3 = PosInTextRanges("94-107+97-109");
    qDebug() << (p2 == p3);
    qDebug() << (p2 != p3);

    VectorPosInTextRanges v1 = \
    VectorPosInTextRanges(  { PosInTextRanges( { {10,20}, {150,250} } ),
                              PosInTextRanges( { {0,5}, {11, 20} } ),
                              PosInTextRanges( { {8, 9}, {91,92} } ),
                              PosInTextRanges( { {1, 2}, {190,191} } ),
                              PosInTextRanges( { {0,5}, {10, 20} } ),
          });
    qDebug() << v1.to_str();
    v1.sort();
    qDebug() << v1.to_str();
    qDebug() << v1.size();

    PosInText2Str posintext2str = {
        { {{ {1,2}, {3,4} },}, "example1"},
        { {{ {1,2}, {3,5} },}, "example2"},
        { {{ {1,2}, {3,8} },}, "example3"},
      };
    qDebug() << posintext2str[{{ {1,2}, {3,4} },}];

    PosInText2PosInAudio text2audio = {
        { {{ {1,2}, {3,4} },},  {1500, 1598} },
        { {{ {5,6}, {9,12} },},  {1750, 1790} },
      };
    qDebug() << text2audio[{{ {1,2}, {3,4} },}].first << text2audio[{{ {1,2}, {3,4} },}].second;
    qDebug() << text2audio.contains(6).to_str();


    PosInText2PosInAudio& text2audio_ref = text2audio;
    PosInAudio2PosInText audio2text = PosInAudio2PosInText(text2audio_ref);

    DipylonUI myapp(argc, argv);

    return myapp.go();
}
