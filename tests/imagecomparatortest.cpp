#include "imagecomparatortest.h"
#include <imagecomparator.h>

#include <QTest>

void ImageComparatorTest::testSimularity_50_Perc()
{
    double diffPerc = ImageComparator::calculateImagesSimularity(QString(":/resource/white_100.png"), QString(":/resource/white_50_black_50.png"));
    QCOMPARE(int(diffPerc), 50);

    diffPerc = ImageComparator::calculateImagesSimularity(QString(":/resource/black_100.png"), QString(":/resource/white_50_black_50.png"));
    QCOMPARE(int(diffPerc), 50);
}

void ImageComparatorTest::testSimularity_0_Perc()
{
    double diffPerc = ImageComparator::calculateImagesSimularity(QString(":/resource/white_100.png"), QString(":/resource/black_100.png"));
    QCOMPARE(int(diffPerc), 0);
}

void ImageComparatorTest::testSimularity_100_Perc()
{
    double diffPerc = ImageComparator::calculateImagesSimularity(QString(":/resource/white_100.png"), QString(":/resource/white_100.png"));
    QCOMPARE(int(diffPerc), 100);

    diffPerc = ImageComparator::calculateImagesSimularity(QString(":/resource/black_100.png"), QString(":/resource/black_100.png"));
    QCOMPARE(int(diffPerc), 100);

    diffPerc = ImageComparator::calculateImagesSimularity(QString(":/resource/white_50_black_50.png"), QString(":/resource/white_50_black_50.png"));
    QCOMPARE(int(diffPerc), 100);
}
