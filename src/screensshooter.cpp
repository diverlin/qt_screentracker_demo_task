#include "screensshooter.h"

#include <QApplication>
#if QT_VERSION <= QT_VERSION_CHECK(6, 0, 0)
#include <QDesktopWidget>
#endif
#include <QScreen>
#include <QPixmap>
#include <QStandardPaths>
#include <QDir>

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
#if QT_VERSION <= QT_VERSION_CHECK(6, 0, 0)
            combinedScreenshot = QPixmap::grabWindow(QApplication::desktop()->winId()).copy(0, 0, combinedScreenshot.width(), combinedScreenshot.height());
#else
            qCritical() << "multimonitor image saving is not implemented on Qt6 variant, please use Qt5 for now or implement it on Qt6";
#endif
        }
    }

    saveImageFile(combinedScreenshot);
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
    saveImageFile(image);
}
#endif // Q_OS_LINUX

void ScreensShooter::saveImageFile(const QPixmap& image)
{
    if (m_imageLocationRoot.isEmpty()) {
        m_imageLocationRoot = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        m_imageLocationRoot += "/images";

        // let's check if the path is not a file to avoid collision with folder name
        QFileInfo fi(m_imageLocationRoot);
        if (fi.exists() && fi.isFile()) {
            qInfo() << m_imageLocationRoot << " is file, but must be a folder, let's remove the file, in order create folder";
            QFile::remove(m_imageLocationRoot);
        }

        // create image storage location if it doesn't exists
        if (!QFileInfo::exists(m_imageLocationRoot)) {
            if (!QDir(m_imageLocationRoot).mkpath(m_imageLocationRoot)) {
                qCritical() << "Failed to create path" << m_imageLocationRoot;
            } else {
                qInfo() << "images storage location" << m_imageLocationRoot << " was created";
            }
        }
    }

    QString fileName = QString("screensshot_%1.png").arg(QDateTime::currentDateTime().toString()).replace(" ", "_");
    QString filePath = m_imageLocationRoot + "/" + fileName;

    // Save the screenshot to a file
    image.save(filePath);
    qInfo() << "save" << filePath;
    emit screenShotIsReady(filePath);
}
