#ifndef IMAGECOMPARATORTEST_H
#define IMAGECOMPARATORTEST_H

#include <QObject>

class ImageComparatorTest : public QObject {
    Q_OBJECT
public:
    ImageComparatorTest()=default;
    ~ImageComparatorTest()=default;

private slots:
    void testDiff_0_Perc();
    void testDiff_50_Perc();
    void testDiff_100_Perc();
};

#endif // IMAGECOMPARATORTEST_H
