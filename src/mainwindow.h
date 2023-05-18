#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ScreensShooter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* m_ui = nullptr;
    ScreensShooter* m_screensShooter = nullptr;

    QString m_prevImagePath;
    const QString& getPrevImagePath() const { return m_prevImagePath; }
};

#endif // MAINWINDOW_H
