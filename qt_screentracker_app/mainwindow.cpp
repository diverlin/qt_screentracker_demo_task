#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "screensshooter.h"
#include "hashsumutils.h"
#include "imagecomparator.h"
#include "datastorage.h"
#include "pathprovider.h"

#include <QImageReader>
#include <QFileInfo>
#include <QColorSpace>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_screensShooter(new ScreensShooter(this))
    , m_dataStorage(new DataStorage("data.db"))
{
    m_ui->setupUi(this);

    qDebug() << QImageReader::supportedImageFormats();

    connect(m_ui->pbToggleTimer, &QPushButton::clicked, this, [this](){
        m_screensShooter->makeScreensShot();
//        if (m_screenShooter->isRunning()) {
//            m_screenShooter->stop();
//            m_ui->pbToggle->setProperty("running", false);
//        } else {
//            m_screenShooter->start();
//            m_ui->pbToggle->setProperty("running", true);
//        }
    });

    connect(m_ui->pbClearHistory, &QPushButton::clicked, this, [this](){
        m_dataStorage->reset();
        reset();
        loadFromDataStorage();
    });

    connect(m_screensShooter, &ScreensShooter::screenShotIsReady, [this](QString filePath){
        QString hash = HashSumUtils::getHashSumOfFile(filePath);
        QString prevImagePath = getPrevImagePath();
        double percDiff = 100.0;
        if (!prevImagePath.isEmpty()) {
            percDiff = ImageComparator::calculateImageDifference(prevImagePath, filePath);
            qInfo() << "perc difference=" << percDiff << "%";
        }
        qInfo() << "hash=" << hash << "for" << filePath;

        QString baseFileName = QFileInfo(filePath).baseName();
        m_dataStorage->insertRows(baseFileName, hash, percDiff);
        QPixmap pixmap = loadPixmap(filePath);
        m_ui->gallery->push(pixmap, hash, percDiff);

        m_prevImagePath = filePath;
    });

    loadFromDataStorage();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

QPixmap MainWindow::loadPixmap(const QString& filePath)
{
    QImageReader reader(filePath);
    reader.setAutoTransform(true);
    QImage newImage = reader.read();
    if (newImage.isNull()) {
        qCritical() << QString("Cannot load %1; %2").arg(filePath).arg(reader.errorString());
        return QPixmap{};
    }
    if (newImage.colorSpace().isValid()) {
        newImage.convertToColorSpace(QColorSpace::SRgb);
    }
    return QPixmap::fromImage(newImage);
}

void MainWindow::reset()
{
    m_ui->gallery->reset();
}

void MainWindow::loadFromDataStorage()
{
    std::vector<std::tuple<QString, QString, double>> rows;
    m_dataStorage->readRows(m_ui->gallery->cellsCount(), rows);
    for (const std::tuple<QString, QString, double>& row: rows) {
        QString baseFileName;
        QString hash;
        double diffPerc;
        std::tie(baseFileName, hash, diffPerc) = row;
        QString filePath = PathProvider::instance().imageLocation()+"/"+baseFileName+".png";
        QPixmap pixmap = loadPixmap(filePath);
        m_ui->gallery->push(pixmap, hash, diffPerc);
    }
}
