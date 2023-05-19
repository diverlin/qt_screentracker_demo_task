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

private:
    QWidget* m_overlayContainer = nullptr;
    QLabel* m_lbHashOverlay = nullptr;
    QLabel* m_lbSimularityOverlay = nullptr;
};

#endif // IMAGEWIDGET_H
