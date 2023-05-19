#include "imagewidget.h"

#include <QVBoxLayout>
#include <QDebug>

ImageWidget::ImageWidget(QWidget* parent)
    : QLabel(parent)
{
    setScaledContents(true);

    m_overlayContainer = new QWidget(this);
    m_overlayContainer->move(6,6);
    QVBoxLayout* overlayLayout = new QVBoxLayout;
    m_overlayContainer->setLayout(overlayLayout);

    m_lbHashOverlay = new QLabel(m_overlayContainer);
    m_lbSimularityOverlay = new QLabel(m_overlayContainer);

    overlayLayout->addWidget(m_lbHashOverlay);
    overlayLayout->addWidget(m_lbSimularityOverlay);

    m_overlayContainer->hide();
}

ImageWidget::~ImageWidget()
{
}

void ImageWidget::setImage(const QPixmap& pixmap, const QString& hash, double simPerc)
{
    QLabel::setPixmap(pixmap);
    m_lbHashOverlay->setText(hash);
    m_lbSimularityOverlay->setText(QString("simularity: %1%").arg(int(simPerc)));
    m_overlayContainer->show();
}

void ImageWidget::clear()
{
    QLabel::setPixmap(QPixmap()); // set null pixmap
    m_overlayContainer->hide();
}

