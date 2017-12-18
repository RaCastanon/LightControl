#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Include libraries
#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QFileDialog>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include "methods.h"

//Definitions
#define SERIAL_COMM_ERROR "Error: could not open serial port"
#define CONNECTION_SUCESSFUL "Serial communication sucessful"
#define SERIAL_CLOSED "Serial port closed"
#define NAMED_WINDOW "Selected Image"
#define DEFAULT_TEST_POINT "180"
#define DEFAULT_SIZE_INTENSITY 50

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_OpenImageButton_clicked();

    void on_closeApp_clicked();

    void on_grayScale_clicked();

    void on_middlePoints_clicked();

    void on_getIntensity_clicked();

    void on_openSerialPort_clicked();

    void on_closeSerialPort_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
