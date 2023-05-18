#ifndef SCREENSSHOOTER_H
#define SCREENSSHOOTER_H

#include <QObject>
#include <QTimer>

class ScreensShooter : public QObject
{
    Q_OBJECT

    const int SCREENSHOOT_INTERVAL_MS = 60*1000;

public:
    ScreensShooter(QObject* parent = nullptr);
    ~ScreensShooter();

    bool isRunning() const { return m_timer.isActive(); }

    void start();
    void stop();

    void makeScreensShot();

signals:
    void screenShotIsReady(QString filePath);

private:
    QTimer m_timer;

    void makeScreensShotGeneric();
#ifdef Q_OS_LINUX
    bool isRunningOnWaylandDisplayServer() const;
    void makeScreensShotOnWaylandDisplayServer();
#endif

    void saveImageFile(const QPixmap&);
};

#endif // SCREENSSHOOTER_H
