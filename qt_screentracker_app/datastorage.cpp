#include "datastorage.h"
#include "pathprovider.h"

#include <QtSql>

DataStorage::DataStorage(const QString& dbFileName)
    : m_dbFilePath(PathProvider::instance().dbLocation() + "/" + dbFileName)
{
    qInfo() << "db location" << m_dbFilePath;
    createTable();
}

DataStorage::~DataStorage()
{

}

bool DataStorage::reset()
{
    bool status = QFile::remove(m_dbFilePath);
    if (status) {
        createTable();
    } else {
        qCritical() << "unable to delete" << m_dbFilePath;
    }
    return status;
}

bool DataStorage::createTable() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(m_dbFilePath);

    if (!db.open()) {
        qDebug() << "Failed to open database.";
        return false;
    }

    QSqlQuery query;
    QString createQuery = "CREATE TABLE IF NOT EXISTS activity (id INTEGER PRIMARY KEY, baseFileName STRING, hash STRING, simPerc DOUBLE)";
    if (!query.exec(createQuery)) {
        qDebug() << "Failed to create table:" << query.lastError().text();
        return false;
    }

    db.close();
    return true;
}

bool DataStorage::insertRows(const QString& fileName, const QString& hash, double simPerc)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.open()) {
        qDebug() << "Failed to open database.";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO activity (baseFileName, hash, simPerc) VALUES (:baseFileName, :hash, :simPerc)");
    query.bindValue(":baseFileName", fileName);
    query.bindValue(":hash", hash);
    query.bindValue(":simPerc", simPerc);

    if (!query.exec()) {
        qDebug() << "Failed to insert row:" << query.lastError().text();
        return false;
    }

    db.close();
    return true;
}

bool DataStorage::readRows(size_t limit, std::vector<std::tuple<QString, QString, double>>& result) const
{
    result.clear();

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.open()) {
        qDebug() << "Failed to open database.";
        return false;
    }

    QSqlQuery query(QString("SELECT * FROM activity ORDER BY id DESC LIMIT %1").arg(limit));

    while (query.next()) {
        int id = query.value("id").toInt();
        QString baseFileName = query.value("baseFileName").toString();
        QString hash = query.value("hash").toString();
        double simPerc = query.value("simPerc").toDouble();

        result.emplace_back(std::tuple<QString, QString, double>{baseFileName, hash, simPerc});
        qDebug() << "id:" << id << "baseFileName:" << baseFileName << "hash:" << hash << "simPerc:" << simPerc;
    }

    db.close();
    return true;
}


