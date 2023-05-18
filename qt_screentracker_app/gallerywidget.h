#ifndef GALLERYWIDGET_H
#define GALLERYWIDGET_H

#include <QWidget>

class QGridLayout;

class GalleryWidget : public QWidget
{
    Q_OBJECT

public:
    GalleryWidget(QWidget* parent = nullptr);
    ~GalleryWidget();

private:
    QGridLayout* m_gridLayout = nullptr;
};

#endif // GALLERYWIDGET_H
