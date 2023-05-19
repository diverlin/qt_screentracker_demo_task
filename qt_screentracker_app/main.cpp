#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

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
