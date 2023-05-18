#include "gallerywidget.h"

#include <QGridLayout>

GalleryWidget::GalleryWidget(QWidget* parent)
    : QWidget(parent)
{
    m_gridLayout = new QGridLayout;
    setLayout(m_gridLayout);
}

GalleryWidget::~GalleryWidget()
{
}

