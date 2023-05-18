#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QString>

class DataStorage {
public:
    DataStorage(const QString& dbFileName);
    ~DataStorage();

private:
    QString m_dbFileName;

    bool createTable();
    bool insertRows(const QString& fileName, const QString& md5Sum, double diffPerc);
    bool readRows();
};


#endif // DATASTORAGE_H
