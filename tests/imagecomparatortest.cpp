#include "imagecomparatortest.h"
#include <imagecomparator.h>

#include <QTest>

void ImageComparatorTest::testDiff_0_Perc()
{
    double diffPerc = ImageComparator::calculateImageDifference(QString(":/resource/white_100.png"), QString(":/resource/white_100.png"));
    QCOMPARE(int(diffPerc), 0);

    diffPerc = ImageComparator::calculateImageDifference(QString(":/resource/black_100.png"), QString(":/resource/black_100.png"));
    QCOMPARE(int(diffPerc), 0);

    diffPerc = ImageComparator::calculateImageDifference(QString(":/resource/white_50_black_50.png"), QString(":/resource/white_50_black_50.png"));
    QCOMPARE(int(diffPerc), 0);
}

void ImageComparatorTest::testDiff_50_Perc()
{
    double diffPerc = ImageComparator::calculateImageDifference(QString(":/resource/white_100.png"), QString(":/resource/white_50_black_50.png"));
    QCOMPARE(int(diffPerc), 50);

    diffPerc = ImageComparator::calculateImageDifference(QString(":/resource/black_100.png"), QString(":/resource/white_50_black_50.png"));
    QCOMPARE(int(diffPerc), 50);
}

void ImageComparatorTest::testDiff_100_Perc()
{
    double diffPerc = ImageComparator::calculateImageDifference(QString(":/resource/white_100.png"), QString(":/resource/black_100.png"));
    QCOMPARE(int(diffPerc), 100);
}
