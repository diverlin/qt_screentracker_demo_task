#ifndef DATASTORAGETEST_H
#define DATASTORAGETEST_H

#include <QObject>

class DataStorageTest : public QObject {
    Q_OBJECT
public:
    DataStorageTest();
    ~DataStorageTest();

private slots:
    void testBase();
};


#endif // DATASTORAGETEST_H
