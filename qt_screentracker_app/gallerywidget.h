#ifndef GALLERYWIDGET_H
#define GALLERYWIDGET_H

#include <QWidget>

#include "fixedqueue.h"

class QGridLayout;

#define GALLERY_ROWS_NUM 3

class GalleryWidget : public QWidget
{
    Q_OBJECT

public:
    GalleryWidget(QWidget* parent = nullptr);
    ~GalleryWidget();

    int cellsCount() const { return GALLERY_ROWS_NUM*GALLERY_ROWS_NUM; }
    void push(const QPixmap& pixmap, const QString hash, double diffPerc);
    void clear();

private:
    QGridLayout* m_gridLayout = nullptr;
    FixedQueue<std::tuple<QPixmap, QString, double>, GALLERY_ROWS_NUM*GALLERY_ROWS_NUM> m_fixedqueue;

    void refreshView();
};

#endif // GALLERYWIDGET_H
