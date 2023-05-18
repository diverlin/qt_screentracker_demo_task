#include "gallerywidget.h"
#include "imagewidget.h"

#include <QGridLayout>
#include <QDebug>

GalleryWidget::GalleryWidget(QWidget* parent)
    : QWidget(parent)
{
    m_gridLayout = new QGridLayout;
    setLayout(m_gridLayout);

    for (int row=0; row<GALLERY_ROWS_NUM; ++row) {
        for (int col=0; col<GALLERY_ROWS_NUM; ++col) {
            ImageWidget* iw = new ImageWidget(this);
            iw->setFixedSize(300, 200);
            iw->setStyleSheet("background: red;");
            m_gridLayout->addWidget(iw, row, col);
        }
    }
}

GalleryWidget::~GalleryWidget()
{
}

void GalleryWidget::push(const QPixmap& pixmap, const QString hash, double diffPerc)
{
    m_fixedqueue.push(std::tuple<QPixmap, QString, double>(pixmap, hash, diffPerc));
    refreshView();
}

void GalleryWidget::reset()
{
    m_fixedqueue.clear();
    refreshView();
}

void GalleryWidget::refreshView()
{
    for (int i=0; i<GALLERY_ROWS_NUM; ++i) {
        for (int j=0; j<GALLERY_ROWS_NUM; ++j) {
            size_t index = j+GALLERY_ROWS_NUM*i;
            QLayoutItem* item = m_gridLayout->itemAtPosition(i, j);
            if (item) {
                QWidget* widget = item->widget();
                if (widget) {
                    ImageWidget* iw = qobject_cast<ImageWidget*>(widget);
                    if (iw) {
                        if (index < m_fixedqueue.size()) {
                            QPixmap pixmap;
                            QString hash;
                            double diffPerc;
                            std::tie(pixmap, hash, diffPerc) = m_fixedqueue.at(index);
                            iw->setImage(pixmap, hash, diffPerc);
                        } else {
                            iw->clear();
                        }
                    }
                }
            }
        }
    }
}
