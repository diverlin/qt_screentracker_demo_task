#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "screensshooter.h"
#include "hashsumutils.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_screensShooter(new ScreensShooter(this))
{
    m_ui->setupUi(this);

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

    connect(m_screensShooter, &ScreensShooter::screenShotIsReady, [](QString filePath){
        QString hash = HashSumUtils::getHashSumOfFile(filePath);
        qInfo() << "get hash" << hash << "for" << filePath;
    });
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

