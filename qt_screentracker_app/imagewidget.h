#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QLabel>

class ImageWidget : public QLabel
{
    Q_OBJECT

public:
    ImageWidget(QWidget* parent = nullptr);
    ~ImageWidget();

    void setImage(const QPixmap& pixmap, const QString& hash, double diffPerc);
    void clear();
};

#endif // IMAGEWIDGET_H
