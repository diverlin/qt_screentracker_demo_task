#include "imagewidget.h"

#include <QDebug>

ImageWidget::ImageWidget(QWidget* parent)
    : QLabel(parent)
    , m_overlay(new QLabel(this))
{
    setScaledContents(true);
    m_overlay->hide();
}

ImageWidget::~ImageWidget()
{
}

void ImageWidget::setImage(const QPixmap& pixmap, const QString& hash, double diffPerc)
{
    QLabel::setPixmap(pixmap);
    m_overlay->setText(hash);
    m_overlay->show();
}

void ImageWidget::clear()
{
    QLabel::setPixmap(QPixmap()); // set null pixmap
    m_overlay->hide();
}

