#include "imagecomparator.h"

#include <QImage>
#include <QFile>
#include <QDebug>

double ImageComparator::calculateImagesSimularity(const QString& imagePath1, const QString& imagePath2)
{
    QImage image1(imagePath1);
    QImage image2(imagePath2);

    if (image1.isNull() || image2.isNull()) {
        qDebug() << "Failed to load images.";
        return -1.0;
    }

    if (image1.size() != image2.size()) {
        qDebug() << "Images have different dimensions.";
        return -1.0;
    }

    int numPixels = image1.width() * image1.height();
    int numDifferingPixels = 0;

    for (int y=0; y<image1.height(); ++y) {
        for (int x=0; x<image1.width(); ++x) {
            if (image1.pixel(x, y) != image2.pixel(x, y)) {
                ++numDifferingPixels;
            }
        }
    }

    double simularityPercentage = 100.0 - (static_cast<double>(numDifferingPixels) / numPixels) * 100.0;
    qDebug() << "Percentage simmularity:" << simularityPercentage;

    return simularityPercentage;
}
