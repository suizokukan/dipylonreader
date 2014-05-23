#include "../gaps.h"

#include <QtTest/QtTest>

/*______________________________________________________________________________

        TestGaps class : test of Gaps module.

______________________________________________________________________________*/
class TestGaps: public QObject
{
    Q_OBJECT

private slots:

    void initTestCase()
    {}

    /*
        A Gaps object is created from a normal string with two adjacent characters.
    */
    void test0()
    { 
      QString str = QString("0…1+1…2");
      Gaps g(&str);

      QVERIFY( g.well_initialized() == true );
      QVERIFY( g.internal_state() == g.INTERNALSTATE_OK );
    }

    /*
        A Gaps object is created from a normal string.
    */
    void test1()
    { 
      QString str = QString("94…98+99…100+101…105+123…125");
      Gaps g(&str);

      QVERIFY( g.well_initialized() == true );
      QVERIFY( g.internal_state() == g.INTERNALSTATE_OK );
      QVERIFY( g.size() == 4 );

      QVERIFY( g.is_inside(0) == false );
      QVERIFY( g.is_inside(97) == true );
      QVERIFY( g.is_inside(98) == true );
      QVERIFY( g.is_inside(125) == true );
      QVERIFY( g.is_inside(126) == false );
    }

    /*
        A Gaps object is created from a normal string with spaces
    */
    void test2()
    { 
      QString str = QString("  94… 95 +   97  …  98 +  101 …  105  ");
      Gaps g(&str);

      QVERIFY( g.well_initialized() == true );
      QVERIFY( g.internal_state() == g.INTERNALSTATE_OK );
      QVERIFY( g.size() == 3 );

      QVERIFY( g.is_inside(0) == false );
      QVERIFY( g.is_inside(94) == true );
      QVERIFY( g.is_inside(95) == true );
      QVERIFY( g.is_inside(96) == false );
      QVERIFY( g.is_inside(105) == true );
      QVERIFY( g.is_inside(106) == false );
    }

    /*
        A Gaps object is created from an empty string -> error.
    */
    void test3()
    { 
      QString str = QString("");
      Gaps g(&str);

      QVERIFY( g.well_initialized() == false );
      QVERIFY( g.internal_state() == g.INTERNALSTATE_EMPTYSTR );
    }

    /*
        A Gaps object is created from a ill-formed string -> error
    */
    void test4a()
    { 
      QString str = QString("49…");
      Gaps g(&str);

      QVERIFY( g.well_initialized() == false );
      QVERIFY( g.internal_state() == g.INTERNALSTATE_X0X1 );
    }

    /*
        A Gaps object is created from a ill-formed string -> error
    */
    void test4b()
    { 
      QString str = QString("49…89+145");
      Gaps g(&str);

      QVERIFY( g.well_initialized() == false );
      QVERIFY( g.internal_state() == g.INTERNALSTATE_SECONDSEP );
    }

    /*
        A Gaps object is created from a ill-formed string (x0==x1) -> error
    */
    void test4c()
    { 
      QString str = QString("49…89+144…144");
      Gaps g(&str);

      QVERIFY( g.well_initialized() == false );
      QVERIFY( g.internal_state() == g.INTERNALSTATE_X0X1 );
    }

    /*
        A Gaps object is created from a ill-formed string (x0>x1) -> error
    */
    void test4d()
    { 
      QString str = QString("49…89+144…143");
      Gaps g(&str);

      QVERIFY( g.well_initialized() == false );
      QVERIFY( g.internal_state() == g.INTERNALSTATE_X0X1 );
    }

    /*
        A Gaps object is created with overlapping gaps -> error
    */
    void test5a()
    { 
      QString str = QString("49…89+50…150");
      Gaps g(&str);

      QVERIFY( g.well_initialized() == false );
      QVERIFY( g.internal_state() == g.INTERNALSTATE_OVERLAPPING );
    }

    /*
        A Gaps object is created with overlapping gaps -> error
    */
    void test5b()
    { 
      QString str = QString("49…89+95…150+3…50");
      Gaps g(&str);

      QVERIFY( g.well_initialized() == false );
      QVERIFY( g.internal_state() == g.INTERNALSTATE_OVERLAPPING );
    }

    void cleanupTestCase()
    {}
};

QTEST_MAIN(TestGaps)
#include "testgaps.moc"
