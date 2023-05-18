#include <QCoreApplication>
#include <QTest>

#include "datastoragetest.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    int testResult = 0;

    testResult |= QTest::qExec(new DataStorageTest, argc, argv);

    return testResult;
}
