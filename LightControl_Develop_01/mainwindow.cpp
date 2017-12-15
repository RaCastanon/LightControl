#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

//Global variables
QSerialPort serial;
QTimer *timerOne;
Mat inputImage;

unsigned int intensityLevel = 0;

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

/* Function name: on_middlePoints_clicked()
 * Developer:     Raul Castañon
 * Details:       Get the middle points to process the calculation of intensity
 */
void MainWindow::on_middlePoints_clicked()
{
    //Get middle points of the img
    setMiddlePoints(inputImage.cols, inputImage.rows);
    //Put values on the GUI labels
    ui->P_one_cols->setText(QString::number(middlePoints[0][0]));
    ui->P_one_rows->setText(QString::number(middlePoints[0][1]));
    ui->P_two_cols->setText(QString::number(middlePoints[1][0]));
    ui->P_two_rows->setText(QString::number(middlePoints[1][1]));
    ui->P_three_cols->setText(QString::number(middlePoints[2][0]));
    ui->P_three_rows->setText(QString::number(middlePoints[2][1]));
    ui->P_four_cols->setText(QString::number(middlePoints[3][0]));
    ui->P_four_rows->setText(QString::number(middlePoints[3][1]));
    ui->P_five_cols->setText(QString::number(middlePoints[4][0]));
    ui->P_five_rows->setText(QString::number(middlePoints[4][1]));
    //Enable visualization of getIntensity button
    ui->getIntensity->setEnabled(true);
    //Disable current button
    ui->middlePoints->setEnabled(false);
}



/* Function name: on_getIntensity_clicked()
 * Developer:     Raul Castañon
 * Details:       Get intensity levels from the image
 */
void MainWindow::on_getIntensity_clicked()
{
    //Local variables
    Scalar promAreaOne, promAreaTwo, promAreaThree, promAreaFour, promAreaFive;
    Mat areaOne, areaTwo, areaThree, areaFour, areaFive;

    //Verify size of the area
    if((ui->widthArea->text().isEmpty())||(ui->hightArea->text().isEmpty()))
    {
        qDebug("Default size asigned");
        ui->widthArea->setText(QString::number(DEFAULT_SIZE_INTENSITY));
        ui->hightArea->setText(QString::number(DEFAULT_SIZE_INTENSITY));
    }
    //Get areas
    areaOne = inputImage(Rect(middlePoints[0][0], middlePoints[0][1], ui->widthArea->text().toInt(), ui->hightArea->text().toInt()));
    areaTwo = inputImage(Rect(middlePoints[1][0], middlePoints[1][1], ui->hightArea->text().toInt(), ui->hightArea->text().toInt()));
    areaThree = inputImage(Rect(middlePoints[2][0], middlePoints[2][1], ui->widthArea->text().toInt(), ui->hightArea->text().toInt()));
    areaFour = inputImage(Rect(middlePoints[3][0], middlePoints[3][1], ui->widthArea->text().toInt(), ui->hightArea->text().toInt()));
    areaFive = inputImage(Rect(middlePoints[4][0], middlePoints[4][1], ui->widthArea->text().toInt(), ui->hightArea->text().toInt()));
    //Get intensity level per area
    promAreaOne = mean(areaOne);
    promAreaTwo = mean(areaTwo);
    promAreaThree = mean(areaThree);
    promAreaFour = mean(areaFour);
    promAreaFive = mean(areaFive);
    //Show results
    ui->intensityLevel_1->setText(QString::number(promAreaOne[0]));
    ui->intensityLevel_2->setText(QString::number(promAreaTwo[0]));
    ui->intensityLevel_3->setText(QString::number(promAreaThree[0]));
    ui->intensityLevel_4->setText(QString::number(promAreaFour[0]));
    ui->intensityLevel_5->setText(QString::number(promAreaFive[0]));
    //Get intensity level mean
    intensityLevel = (int)((promAreaOne[0] + promAreaTwo[0] + promAreaThree[0] + promAreaFour[0] + promAreaFive[0]) / 5.0);
    ui->intensityLevel->setText(QString::number(intensityLevel));
}
