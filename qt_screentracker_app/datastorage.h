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

    bool insertRows(const QString& fileName, const QString& hash, double simPerc);

    bool readRows(size_t limit, std::vector<std::tuple<QString, QString, double>>& result) const;

    bool reset();

private:
    QString m_dbFilePath;

    bool createTable();
};


#endif // DATASTORAGE_H
