#ifndef IMAGECOMPARATORTEST_H
#define IMAGECOMPARATORTEST_H

#include <QObject>

class ImageComparatorTest : public QObject {
    Q_OBJECT
public:
    ImageComparatorTest()=default;
    ~ImageComparatorTest()=default;

private slots:
    void testSimularity_0_Perc();
    void testSimularity_50_Perc();
    void testSimularity_100_Perc();
};

#endif // IMAGECOMPARATORTEST_H
