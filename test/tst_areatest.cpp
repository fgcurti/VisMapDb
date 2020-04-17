#include <QtTest>
#include "information.h"

// add necessary includes here

class areatest : public QObject
{
    Q_OBJECT

public:
    areatest();
    ~areatest();

private slots:
    void test_case_area();
    void test_case_perimeter();

};

areatest::areatest()
{

}

areatest::~areatest()
{

}

void areatest::test_case_area()
{
    Information info;
    double result = info.calcArea(2, 2);
    QCOMPARE(result, 4);
}

void areatest::test_case_perimeter()
{
    Information info;
    double result = info.calcPerimeter(2, 2);
    QCOMPARE(result, 8);
}

QTEST_APPLESS_MAIN(areatest)

#include "tst_areatest.moc"
