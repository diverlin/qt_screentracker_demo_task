#ifndef JOBFACTORY_H
#define JOBFACTORY_H

#include <QThread>
#include <QMutex>

#include <QObject>
#include <QMap>

class BaseWorker : public QObject
{
    Q_OBJECT

public:
    BaseWorker()=default;
    virtual ~BaseWorker()=default;

public slots:
    virtual void doWork() = 0;
};

class HashWorker final: public BaseWorker
{
    Q_OBJECT

public:
    HashWorker(const QString& imageFilePath);
    ~HashWorker() override final;
    QString hash() { return m_hash; }

public slots:
    void doWork() override final;

signals:
    void workFinished(QString);

private:
    QString m_imageFilePath;
    QString m_hash;
};

class SimularityPercentageWorker final : public BaseWorker
{
    Q_OBJECT

public:
    SimularityPercentageWorker(const QString& imageFilePath, const QString& prevImageFilePath);
    ~SimularityPercentageWorker() override final;

    double simPerc() { return m_simPerc; }

public slots:
    void doWork() override final;

signals:
    void workFinished(double);

private:
    QString m_imageFilePath;
    QString m_prevImageFilePath;
    double m_simPerc = 0.0;
};


class JobFactory : public QObject
{
    Q_OBJECT

public:
    JobFactory(QObject* parent, bool multithreading = true);
    ~JobFactory();

    void pushJob(const QString& currentImageFilePath, const QString& prevImageFilePath = "");

signals:
    void jobDone(QString imageFilePath, QString hash, double simPerc);

private:
    bool m_multithreading = true;

    QMutex m_jobsResultMutex;
    QMap<QString, QVariant> m_jobsResult;
};

#endif // JOBFACTORY_H
