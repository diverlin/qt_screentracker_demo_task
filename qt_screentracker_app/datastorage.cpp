#include "datastorage.h"
#include "pathprovider.h"

#include <QtSql>

DataStorage::DataStorage(const QString& dbFileName)
    : m_dbFilePath(PathProvider::instance().dbLocation() + "/" + dbFileName)
{
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
    QString createQuery = "CREATE TABLE IF NOT EXISTS activity (id INTEGER PRIMARY KEY, baseFileName STRING, md5Sum STRING, diffPerc DOUBLE)";
    if (!query.exec(createQuery)) {
        qDebug() << "Failed to create table:" << query.lastError().text();
        return false;
    }

    db.close();
    return true;
}

bool DataStorage::insertRows(const QString& fileName, const QString& md5Sum, double diffPerc)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.open()) {
        qDebug() << "Failed to open database.";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO activity (baseFileName, md5Sum, diffPerc) VALUES (:baseFileName, :md5Sum, :diffPerc)");
    query.bindValue(":baseFileName", fileName);
    query.bindValue(":md5Sum", md5Sum);
    query.bindValue(":diffPerc", diffPerc);

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
    //QSqlQuery query(QString("SELECT * FROM activity LIMIT %1").arg(limit));

    while (query.next()) {
        int id = query.value("id").toInt();
        QString baseFileName = query.value("baseFileName").toString();
        QString md5Sum = query.value("md5Sum").toString();
        double diffPerc = query.value("diffPerc").toDouble();

        result.emplace_back(std::tuple<QString, QString, double>{baseFileName, md5Sum, diffPerc});
        qDebug() << "id:" << id << "baseFileName:" << baseFileName << "md5Sum:" << md5Sum << "diffPerc:" << diffPerc;
    }

    db.close();
    return true;
}


