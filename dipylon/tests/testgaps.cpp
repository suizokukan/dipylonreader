#include "../gaps.h"

#include <QtTest/QtTest>

class TestGaps: public QObject
{
    Q_OBJECT

    Gaps *g;

private slots:

    void initTestCase()
    {     
      
      QString str = QString("94-95+97-98+101-105");
      this->g = new Gaps(&str);
    }

    void myFirstTest()
    { 
      QVERIFY( this->g->well_initialized() == true );
    }

    void cleanupTestCase()
    {
      delete this->g;
    }
};

QTEST_MAIN(TestGaps)
#include "testgaps.moc"
