#include "fixedqueuetest.h"
#include "fixedqueue.h"

#include <QTest>

void FixedQueueTest::testBase()
{
    FixedQueue<int, 5> q;
    q.push(1);
    q.push(2);
    q.push(3);

    QCOMPARE(q.size(), 3);

    q.push(4);
    q.push(5);

    QCOMPARE(q.size(), 5);

    q.push(6);

    QCOMPARE(q.size(), 5);

    QString buff;
    for (int el: q) {
        buff += QString::number(el);
    }

    QCOMPARE(buff, "65432");

    q.push(7);
    QCOMPARE(q.size(), 5);

    buff.clear();
    for (int el: q) {
        buff += QString::number(el);
    }

    QCOMPARE(buff, "76543");
}
