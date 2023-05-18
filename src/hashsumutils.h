#ifndef HASHSUMUTILS_H
#define HASHSUMUTILS_H

#include <QString>

class HashSumUtils {
public:
    static QString getHashSumOfFile(const QString& filePath);
};


#endif // HASHSUMUTILS_H
