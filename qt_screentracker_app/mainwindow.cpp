#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "screensshooter.h"
#include "datastorage.h"
#include "pathprovider.h"
#include "jobfactory.h"

#include <QImageReader>
#include <QFileInfo>
#include <QColorSpace>
#include <QDir>
#include <QStyle>
#include <QProgressBar>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_screensShooter(new ScreensShooter(this))
    , m_dataStorage(new DataStorage("data.db"))
    , m_jobFactory(new JobFactory(this, /*multithreading*/true))
{
    m_ui->setupUi(this);

    m_realTimeTimer.setInterval(20);
    connect(&m_realTimeTimer, &QTimer::timeout, this, [this](){
        m_ui->lbTimer->setText(QString("%1ms").arg(m_elapsedTimer.elapsed()));
    });

    connect(m_ui->pbToggleTimer, &QPushButton::clicked, this, [this](){
        if (m_screensShooter->isRunning()) {
            m_screensShooter->stop();
            m_ui->pbToggleTimer->setText(tr("ON Timer"));
            m_ui->pbToggleTimer->setProperty("running", false);

            m_realTimeTimer.stop();
            m_ui->lbTimer->setText("0ms");
        } else {
            m_screensShooter->start();
            m_ui->pbToggleTimer->setText(tr("OFF Timer"));
            m_ui->pbToggleTimer->setProperty("running", true);

            m_realTimeTimer.start();
            m_elapsedTimer.start();
        }
        m_ui->pbToggleTimer->style()->unpolish(m_ui->pbToggleTimer);
        m_ui->pbToggleTimer->style()->polish(m_ui->pbToggleTimer);
    });

    connect(m_screensShooter, &ScreensShooter::screenShotIsReady, [this](QString imageFilePath){
        QString prevImagePath = getPrevImagePath();
        m_jobFactory->pushJob(imageFilePath, getPrevImagePath());
    });

    connect(m_jobFactory, &JobFactory::jobDone, this, [this](QString imageFilePath, QString hash, double simPerc){
        QString baseFileName = QFileInfo(imageFilePath).baseName();
        m_dataStorage->insertRows(baseFileName, hash, simPerc);
        QPixmap pixmap = loadPixmap(imageFilePath);
        m_ui->gallery->push(pixmap, hash, simPerc);

        m_prevImagePath = imageFilePath;
    });

    // for testing
    connect(m_ui->pbMakeScreenShot, &QPushButton::clicked, this, [this](){
        m_screensShooter->makeScreensShot();
    });

    connect(m_ui->pbClearHistory, &QPushButton::clicked, this, [this](){
        m_dataStorage->reset();
        clear();
        loadFromDataStorage();
    });
    // for testing

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

void MainWindow::clear()
{
    m_ui->gallery->clear();
    QDir directory(PathProvider::instance().imageLocation());
    QStringList fileNames = directory.entryList(QDir::Files | QDir::NoDotAndDotDot);
    for (const QString& fileName: qAsConst(fileNames)) {
        QString filePath = directory.filePath(fileName);
        if (filePath.endsWith("png")) {
            qInfo() << "remove" << filePath;
            QFile::remove(filePath);
        }
    }
}

void MainWindow::loadFromDataStorage()
{
    std::vector<std::tuple<QString, QString, double>> rows;

    m_dataStorage->readRows(m_ui->gallery->cellsCount(), rows);
    std::vector<std::tuple<QString, QString, double>>::reverse_iterator it = rows.rbegin();
    for (; it!=rows.rend(); ++it) {
        const std::tuple<QString, QString, double>& row = *it;
        QString baseFileName;
        QString hash;
        double diffPerc;
        std::tie(baseFileName, hash, diffPerc) = row;
        QString filePath = PathProvider::instance().imageLocation()+"/"+baseFileName+".png";
        QPixmap pixmap = loadPixmap(filePath);
        m_ui->gallery->push(pixmap, hash, diffPerc);
    }
}
