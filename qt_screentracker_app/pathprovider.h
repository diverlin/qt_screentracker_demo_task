#ifndef PATHPROVIDER_H
#define PATHPROVIDER_H

#include <QString>

class PathProvider {
public:
    ~PathProvider()=default;

    static PathProvider& instance();

    const QString& imageLocation();
    const QString& dbLocation();

private:
    PathProvider()=default;

    QString m_dataLocation;
    QString m_imageLocation;
    QString m_dbLocation;

    const QString& dataLocation();
    static void ensureFolderPresense(const QString&);
};

#endif // PATHPROVIDER_H
