#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <chrono>
#include <time.h>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QTime>
#include <QRunnable>
#include <QThreadPool>

class Runner : public QObject, public QRunnable
{
    Q_OBJECT

public:
    Runner(QMainWindow *parent);
    void run() override;
    bool finished;

    QMainWindow *mainWindow;

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loop();
    bool isFinished();

    QPushButton *btnStart;

    Runner *nessy;
    Runner *yeti;
    Runner *kraken;

public slots:
    void start();

};
#endif // MAINWINDOW_H
