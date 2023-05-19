#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

void logMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message)
{
    static QFile logFile("log.txt");
    logFile.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream textStream(&logFile);
    switch (type) {
    case QtDebugMsg:
        textStream << "Debug: " << message << Qt::endl;
        break;
    case QtInfoMsg:
        textStream << "Info: " << message << Qt::endl;
        break;
    case QtWarningMsg:
        textStream << "Warning: " << message << Qt::endl;
        break;
    case QtCriticalMsg:
        textStream << "Critical: " << message << Qt::endl;
        break;
    case QtFatalMsg:
        textStream << "Fatal: " << message << Qt::endl;
        break;
    }

    logFile.close();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qInstallMessageHandler(logMessageHandler);

    QFile file(":/theme.css");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString styleSheet = file.readAll();
        app.setStyleSheet(styleSheet);
        file.close();
    }

    MainWindow window;
    window.show();
    return app.exec();
}
