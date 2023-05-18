#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QString>

#include <vector>
#include <tuple>

class DataStorage {
public:
    DataStorage(const QString& dbFileName);
    ~DataStorage();

    const QString& filePath() const { return m_dbFilePath; }

    bool insertRows(const QString& fileName, const QString& md5Sum, double diffPerc);

    // todo: implement getting fixed number of latest rows
    bool readRows(std::vector<std::tuple<QString, QString, double>>& result) const;

private:
    QString m_dbFilePath;

    bool createTable();
};


#endif // DATASTORAGE_H
