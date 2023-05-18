#include "datastoragetest.h"
#include <datastorage.h>

#include <QTest>
#include <QFileInfo>
#include <QDebug>

void DataStorageTest::testDbCreation()
{
    // create db
    DataStorage db("test.db");
    QString filePath = db.filePath();
    qInfo()<< "checking" << filePath << "existance";
    QVERIFY(QFileInfo::exists(filePath));

    // remove db
    QVERIFY(QFile(filePath).remove());
    QVERIFY(!QFileInfo::exists(filePath));
}

void DataStorageTest::testDbReadWrite()
{
    // create db
    DataStorage db("test.db");

    // write data
    QVERIFY(db.insertRows("1", "xxx", 0.2));
    QVERIFY(db.insertRows("2", "yyy", 0.3));
    QVERIFY(db.insertRows("3", "zzz", 0.4));

    // read data
    std::vector<std::tuple<QString, QString, double>> rows;
    QVERIFY(db.readRows(100, rows));
    QCOMPARE(rows.size(),3);
    QString id, md5Sum;
    double percDiff;

    // test read row1
    std::tie(id, md5Sum, percDiff) = rows[0];
    QCOMPARE(id, "1");
    QCOMPARE(md5Sum, "xxx");
    QCOMPARE(percDiff, 0.2);

    // test read row2
    std::tie(id, md5Sum, percDiff) = rows[1];
    QCOMPARE(id, "2");
    QCOMPARE(md5Sum, "yyy");
    QCOMPARE(percDiff, 0.3);

    // test read row3
    std::tie(id, md5Sum, percDiff) = rows[2];
    QCOMPARE(id, "3");
    QCOMPARE(md5Sum, "zzz");
    QCOMPARE(percDiff, 0.4);

    // remove db
    QVERIFY(QFile(db.filePath()).remove());
    QVERIFY(!QFileInfo::exists(db.filePath()));
}
