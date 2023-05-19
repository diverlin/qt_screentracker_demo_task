#include "jobfactory.h"

#include "hashsumutils.h"
#include "imagecomparator.h"

#include <QFileInfo>
#include <QMutexLocker>
#include <QDebug>


HashWorker::HashWorker(const QString& imageFilePath)
    :
      m_imageFilePath(imageFilePath)
{

}

HashWorker::~HashWorker()
{
    qInfo() << "thread=" << QThread::currentThreadId() << "~HashWorker for"<< m_imageFilePath;
}

void HashWorker::doWork()
{
    qInfo() << "thread=" << QThread::currentThreadId() << "HashWorker::doWork for" << m_imageFilePath;
    m_hash = HashSumUtils::getHashSumOfFile(m_imageFilePath);
    emit workFinished(m_hash);
    deleteLater();
}


SimularityPercentageWorker::SimularityPercentageWorker(const QString& imageFilePath, const QString& prevImageFilePath)
    :
      m_imageFilePath(imageFilePath)
    , m_prevImageFilePath(prevImageFilePath)
{

}

SimularityPercentageWorker::~SimularityPercentageWorker()
{
    qDebug() << "thread=" << QThread::currentThreadId() << "~SimularityPercentageWorker for" << m_imageFilePath;
}

void SimularityPercentageWorker::doWork()
{
    qInfo() << "thread=" << QThread::currentThreadId() << "SimularityPercentageWorker::doWork for" << m_imageFilePath;
    if (!m_prevImageFilePath.isEmpty()) {
        m_simPerc = ImageComparator::calculateImagesSimularity(m_prevImageFilePath, m_imageFilePath);
    }
    emit workFinished(m_simPerc);
    deleteLater();
}




JobFactory::JobFactory(QObject* parent, bool multithreading)
    : QObject(parent)
    , m_multithreading(multithreading)
    , m_jobsResultMutex(QMutex::Recursive)
{

}

JobFactory::~JobFactory()
{
}

void JobFactory::pushJob(const QString& currentImagePath, const QString& prevImagePath)
{
    if (m_multithreading) {
        // hash thread
        {
        HashWorker* hashWorker = new HashWorker(currentImagePath);
        QThread* hashThread = new QThread;
        hashWorker->moveToThread(hashThread);

        // Connect signals and slots between the worker and the thread
        connect(hashThread, &QThread::started, hashWorker, &HashWorker::doWork);
        connect(hashWorker, &HashWorker::workFinished, this, [currentImagePath, this](QString hash) {
            QString key = QFileInfo(currentImagePath).baseName();

            QMutexLocker lock(&m_jobsResultMutex);
            m_jobsResult[key+"_hash"] = QVariant(hash);
            if (m_jobsResult.contains(key+"_simPerc")) {
                emit jobDone(currentImagePath, m_jobsResult[key+"_hash"].toString(), m_jobsResult[key+"_simPerc"].toDouble());
            }
        });
        connect(hashThread, &QThread::finished, hashThread, &QObject::deleteLater);
        //connect(hashThread, &QThread::finished, hashWorker, &BaseWorker::markForDeletion);

        hashThread->start();
        }

        // simularity perc thread
        {
        SimularityPercentageWorker* simPercWorker = new SimularityPercentageWorker(currentImagePath, prevImagePath);
        QThread* simPercThread = new QThread;
        simPercWorker->moveToThread(simPercThread);

        // Connect signals and slots between the worker and the thread
        connect(simPercThread, &QThread::started, simPercWorker, &SimularityPercentageWorker::doWork);
        connect(simPercWorker, &SimularityPercentageWorker::workFinished, this, [currentImagePath, this](double simPerc) {
            QString key = QFileInfo(currentImagePath).baseName();

            QMutexLocker lock(&m_jobsResultMutex);
            m_jobsResult[key+"_simPerc"] = QVariant(simPerc);
            if (m_jobsResult.contains(key+"_hash")) {
                emit jobDone(currentImagePath, m_jobsResult[key+"_hash"].toString(), m_jobsResult[key+"_simPerc"].toDouble());
            }
        });
        connect(simPercThread, &QThread::finished, simPercThread, &QObject::deleteLater);
        //connect(simPercThread, &QThread::finished, simPercWorker, &BaseWorker::markForDeletion);

        simPercThread->start();
        }
    } else {
        qWarning() << "JobFactory is running in single thread mode, this is slow and used for tests";
        HashWorker hashWorker(currentImagePath);
        hashWorker.doWork();
        QString hash = hashWorker.hash();

        SimularityPercentageWorker simWorker(currentImagePath, prevImagePath);
        simWorker.doWork();
        double simPerc = simWorker.simPerc();

        emit jobDone(currentImagePath, hash, simPerc);
    }
}




