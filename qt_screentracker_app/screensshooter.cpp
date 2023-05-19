#include "screensshooter.h"
#include "pathprovider.h"

#include <QApplication>
#if QT_VERSION <= QT_VERSION_CHECK(6, 0, 0)
#include <QDesktopWidget>
#endif
#include <QScreen>
#include <QPixmap>
#include <QDateTime>
#include <QRandomGenerator>
#include <QPainter>

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
            combinedScreenshot = joinPixmaps(combinedScreenshot, screenScreenshot);
        }
    }

    saveImageFile(combinedScreenshot);
}

QPixmap ScreensShooter::joinPixmaps(const QPixmap& pixmap1, const QPixmap& pixmap2)
{
    int width = pixmap1.width() + pixmap2.width();
    int height = qMax(pixmap1.height(), pixmap2.height());

    QPixmap joinedPixmap(width, height);
    joinedPixmap.fill(Qt::transparent);

    QPainter painter(&joinedPixmap);
    painter.drawPixmap(0, 0, pixmap1);
    painter.drawPixmap(pixmap1.width(), 0, pixmap2);
    painter.end();

    return joinedPixmap;
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
    QString randomSuffix = QString::number(QRandomGenerator::global()->generate());

    QString fileName = QString("screensshot_%1_%2.png").arg(QDateTime::currentDateTime().toString()).arg(randomSuffix);
    fileName = fileName.replace(" ", "_");
    fileName = fileName.replace(":", "__");
    QString filePath = PathProvider::instance().imageLocation() + "/" + fileName;

    // Save the screenshot to a file
    image.save(filePath);
    qInfo() << "save" << filePath;
    emit screenShotIsReady(filePath);
}
