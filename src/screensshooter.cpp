#include "screensshooter.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QPixmap>

#ifdef Q_OS_LINUX
#include <QProcessEnvironment>
#endif

#include <QDebug>

ScreensShooter::ScreensShooter(QObject* parent)
    : QObject(parent)
{
    m_timer.setInterval(SCREENSHOOT_INTERVAL_MS);

    connect(&m_timer, &QTimer::timeout, this, &ScreensShooter::makeScreensShot);
}

ScreensShooter::~ScreensShooter()
{
}

void ScreensShooter::start()
{
    m_timer.start();
    makeScreensShot();
}

void ScreensShooter::stop()
{
    m_timer.stop();
}

void ScreensShooter::makeScreensShot()
{
#ifdef Q_OS_LINUX
    qInfo()<<"QGuiApplication::platformName()=" << QGuiApplication::platformName();
    if (isRunningOnWaylandDisplayServer()) {
        makeScreensShotOnWaylandDisplayServer();
    } else {
        makeScreensShotGeneric();
    }
#else
    makeScreensShotGeneric();
#endif // Q_OS_LINUX
}

void ScreensShooter::makeScreensShotGeneric()
{
    // create a pixmap to hold the combined screenshot of all screens
    QPixmap combinedScreenshot;

    // get a list of all screens
    QList<QScreen*> screens = QGuiApplication::screens();

    // iterate over each screen and capture its screenshot
    for (QScreen* screen: qAsConst(screens)) {
        // capture the screen's screenshot
        qDebug() << "proc screen" << screen->name();
        QPixmap screenScreenshot = screen->grabWindow(0);

        // If this is the first screen, initialize the combined screenshot pixmap
        if (combinedScreenshot.isNull()) {
            combinedScreenshot = screenScreenshot;
        } else {
            // Combine the screen screenshot with the existing combined screenshot
            combinedScreenshot = QPixmap::grabWindow(QApplication::desktop()->winId()).copy(0, 0, combinedScreenshot.width(), combinedScreenshot.height());
        }
    }

    QString filePath = "combined_screenshot.png";

    // Save the screenshot to a file
    combinedScreenshot.save(filePath);
    qDebug() << "save" << filePath;
    emit screenShotIsReady(filePath);
}

#ifdef Q_OS_LINUX
bool ScreensShooter::isRunningOnWaylandDisplayServer() const
{
    QString value = QProcessEnvironment::systemEnvironment().value("XDG_SESSION_TYPE");
    return value.toLower() == "wayland";

}
void ScreensShooter::makeScreensShotOnWaylandDisplayServer()
{
    qCritical() << "isRunningOnWaylandDisplayServer not implemented yet";
    assert(false);
//    QString filePath = "combined_screenshot.png";

//    // Save the screenshot to a file
//    screenshot.save(filePath);

//    qDebug() << "save" << filePath;
//    emit screenShotIsReady(filePath);
}
#endif // Q_OS_LINUX
