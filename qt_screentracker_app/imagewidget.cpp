#include "imagewidget.h"

#include <QDebug>

ImageWidget::ImageWidget(QWidget* parent)
    : QLabel(parent)
{
    setScaledContents(true);
}

ImageWidget::~ImageWidget()
{
}

void ImageWidget::setImage(const QPixmap& pixmap, const QString& hash, double diffPerc)
{
    QLabel::setPixmap(pixmap);
}

void ImageWidget::clear()
{
    QLabel::setPixmap(QPixmap()); // set null pixmap
}
