#ifndef IMAGECOMPARATORTEST_H
#define IMAGECOMPARATORTEST_H

#include <QObject>

class ImageComparatorTest : public QObject {
    Q_OBJECT
public:
    ImageComparatorTest()=default;
    ~ImageComparatorTest()=default;

private slots:
    void testMatch_0_Perc();
    void testMatch_50_Perc();
    void testMatch_100_Perc();
};

#endif // IMAGECOMPARATORTEST_H
