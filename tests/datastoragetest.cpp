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
    Q_ASSERT(QFileInfo::exists(filePath));

    // remove db
    Q_ASSERT(QFile(filePath).remove());
    Q_ASSERT(!QFileInfo::exists(filePath));
}

void DataStorageTest::testDbReadWrite()
{
    // create db
    DataStorage db("test.db");

    // write data
    Q_ASSERT(db.insertRows("1", "xxx", 0.2));
    Q_ASSERT(db.insertRows("2", "yyy", 0.3));
    Q_ASSERT(db.insertRows("3", "zzz", 0.4));

    // read data
    std::vector<std::tuple<QString, QString, double>> rows;
    Q_ASSERT(db.readRows(rows));
    Q_ASSERT(rows.size()==3);
    QString id, md5Sum;
    double percDiff;

    // test read row1
    std::tie(id, md5Sum, percDiff) = rows[0];
    Q_ASSERT(id == "1");
    Q_ASSERT(md5Sum == "xxx");
    Q_ASSERT(qFuzzyCompare(percDiff, 0.2));

    // test read row2
    std::tie(id, md5Sum, percDiff) = rows[1];
    Q_ASSERT(id == "2");
    Q_ASSERT(md5Sum == "yyy");
    Q_ASSERT(qFuzzyCompare(percDiff, 0.3));

    // test read row3
    std::tie(id, md5Sum, percDiff) = rows[2];
    Q_ASSERT(id == "3");
    Q_ASSERT(md5Sum == "zzz");
    Q_ASSERT(qFuzzyCompare(percDiff, 0.4));

    // remove db
    Q_ASSERT(QFile(db.filePath()).remove());
    Q_ASSERT(!QFileInfo::exists(db.filePath()));
}
