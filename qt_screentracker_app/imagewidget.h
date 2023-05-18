#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QLabel>

class ImageWidget : public QLabel
{
    Q_OBJECT

public:
    ImageWidget(QWidget* parent = nullptr);
    ~ImageWidget();
};

#endif // IMAGEWIDGET_H
