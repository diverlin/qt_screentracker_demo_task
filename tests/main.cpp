#include <QCoreApplication>
#include <QTest>

#include "datastoragetest.h"
#include "imagecomparatortest.h"
#include "fixedqueuetest.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    int testResult = 0;

    testResult |= QTest::qExec(new DataStorageTest, argc, argv);
    testResult |= QTest::qExec(new ImageComparatorTest, argc, argv);
    testResult |= QTest::qExec(new FixedQueueTest, argc, argv);

    return testResult;
}
