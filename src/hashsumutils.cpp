#include "hashsumutils.h"

#include <QCryptographicHash>
#include <QFile>
#include <QDebug>

QString HashSumUtils::getHashSumOfFile(const QString& filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for hashing:" << file.errorString();
        return QString();
    }

    QCryptographicHash hash(QCryptographicHash::Md5);

    if (hash.addData(&file)) {
        QByteArray result = hash.result();
        return result.toHex();
    } else {
        qDebug() << "Failed to calculate hash.";
        return QString();
    }
}
