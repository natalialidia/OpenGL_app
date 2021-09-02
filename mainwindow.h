#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
    public slots:
        void updatePaperCounter();
        void updateCountdown();

    private:
        Ui::MainWindow *ui;
        QTimer *timer;
        QTimer *countdown;
};
#endif // MAINWINDOW_H
