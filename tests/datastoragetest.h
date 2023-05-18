#ifndef DATASTORAGETEST_H
#define DATASTORAGETEST_H

#include <QObject>

class DataStorageTest : public QObject {
    Q_OBJECT
public:
    DataStorageTest()=default;
    ~DataStorageTest()=default;

private slots:
    void testDbCreation();
    void testDbReadWrite();
};


#endif // DATASTORAGETEST_H
