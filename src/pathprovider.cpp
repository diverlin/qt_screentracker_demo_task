#include "pathprovider.h"

#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

PathProvider& PathProvider::instance()
{
    static PathProvider path;
    return path;
}

void PathProvider::ensureFolderPresense(const QString& path)
{
    // let's check if the path is not a file to avoid collision with folder name
    QFileInfo fi(path);
    if (fi.exists() && fi.isFile()) {
        qInfo() << path << " is file, but must be a folder, let's remove the file, in order create folder";
        QFile::remove(path);
    }

    // create image storage location if it doesn't exists
    if (!QFileInfo::exists(path)) {
        if (!QDir(path).mkpath(path)) {
            qCritical() << "Failed to create path" << path;
        } else {
            qInfo() << "location" << path << " was created";
        }
    }
}

const QString& PathProvider::dataLocation()
{
    if (m_dataLocation.isEmpty()) {
        m_dataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    }
    PathProvider::ensureFolderPresense(m_dataLocation);
    return m_dataLocation;
}

const QString& PathProvider::imageLocation()
{
    if (m_imageLocation.isEmpty()) {
        m_imageLocation = dataLocation();
        m_imageLocation += "/images";
    }
    PathProvider::ensureFolderPresense(m_imageLocation);
    return m_imageLocation;
}

const QString& PathProvider::dbLocation()
{
    return dataLocation();
}
