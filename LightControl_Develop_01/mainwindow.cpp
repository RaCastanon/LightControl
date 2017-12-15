#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

//Global variables
QSerialPort serial;
QTimer *timerOne;
Mat inputImage;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Configure timer one
    timerOne = new QTimer(this);
    connect(timerOne, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    //Disable not required buttons
    ui->grayScale->setDisabled(true);
    ui->middlePoints->setDisabled(true);
    ui->getIntensity->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Function name: OpenImageButton()
 * Developer:     Raul Castañon
 * Details:       Function used to open and show an image
 */
void MainWindow::on_OpenImageButton_clicked()
{
    QString inputImg = QFileDialog::getOpenFileName();
    inputImage = imread(inputImg.toLatin1().data());
    //Verify if there is an image
    if(!(inputImage.empty()))
    {
        //Show image
        namedWindow(NAMED_WINDOW, WINDOW_NORMAL);
        imshow(NAMED_WINDOW, inputImage);
        //Enable grayscale button
        ui->grayScale->setEnabled(true);
        //Disable OpenImage button
        ui->OpenImageButton->setEnabled(false);
    }
}

/* Function name: closeApp()
 * Developer:     Raul Castañon
 * Details:       Close application
 */
void MainWindow::on_closeApp_clicked()
{
    //Check if we need to stop timer
    if(true == timerOne->isActive())
    {
        timerOne->stop();
    }
    //Check if we need to close SerialPort
    close();
}

/* Function name: on_grayScale_clicked()
 * Developer:     Raul Castañon
 * Details:       Convert image in grayscale format
 */
void MainWindow::on_grayScale_clicked()
{
    if(false == inputImage.empty())
    {
        //Set image in grayscale format
        cvtColor(inputImage, inputImage, CV_RGB2GRAY);
        //Show result in same window
        imshow(NAMED_WINDOW, inputImage);
        ui->middlePoints->setEnabled(true);
        ui->grayScale->setEnabled(false);
    }
}
