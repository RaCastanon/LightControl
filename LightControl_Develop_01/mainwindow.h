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

// Definitions
#define DEFAULT_TEST_POINT "180"
#define DEFAULT_COM_PORT "COM10"
#define DEFAULT_PWM_VALUE "95\n"
#define DEFAULT_SIZE_INTENSITY 50
#define DEFAULT_TIMER_ON 2000
#define DEFAULT_VIDEO_NAME "Video window"
#define DEFAULT_WAITKEY_TIME 100
#define DEFAULT_VIDEO_CAM_PORT 0
#define DEFAULT_SETPOINT 120
#define DEFAULT_SET_POINT "120"
#define TIMER_ENABLED "Timer one is enabled"
#define TIMER_DISABLED "Timer one is disabled"
#define VIDEO_ENABLED "Video camera open"
#define VIDEO_DISABLED "Video camera closed"
#define CONNECTION_SUCESSFUL "Serial communication sucessful"
#define SERIAL_CLOSED "Serial port closed"
#define NAMED_WINDOW "Selected Image"

#define SERIAL_COMM_ERROR "Error 0: could not open serial port"
#define ERROR_PORT_OPEN "Error 1: Port already open"
#define ERROR_TIMER_OPEN "Error 2: Timer one is enabled"
#define ERROR_TIMER_TOCLOSE "Error 3: Timer one is not active"
#define ERROR_SET_POINT "Error 4: Default setPoint assigned"

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

    void on_setTimer_clicked();

    void on_stopTimer_clicked();

    void onTimeOut();

    void on_openVideoCam_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
