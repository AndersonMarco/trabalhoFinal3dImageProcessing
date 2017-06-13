#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qMediaPlayerPlayer=new QMediaPlayer(this);
    VideoSurface *videoSurface= new VideoSurface;
    qMediaPlayerPlayer->setVideoOutput(videoSurface);

    QObject::connect(this,SIGNAL(signalSendImage(QImage *)),ui->openGLWidget,SLOT(slotRecvImage(QImage *)));
    QObject::connect(ui->openGLWidget,SIGNAL(signalSendImage(QImage *)),this,SLOT(slotRecvImage(QImage *)));
    QObject::connect(videoSurface, SIGNAL(signalSendImage(QImage *)),ui->openGLWidget,SLOT(slotRecvImage(QImage *)));
    QObject::connect(qMediaPlayerPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(slotDurationChanged(qint64)));
    QObject::connect(qMediaPlayerPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(slotChangePositionByMovie(qint64)));
    QObject::connect(ui->horizontalSlider,SIGNAL(sliderReleased()),this, SLOT(slotChangePositionInMovie()));
    filter=FilterAttributes::filterTypeNone;
    ui->horizontalSliderParameter->setVisible(false);
    ui->labelParameter->setVisible(false);
    movieIsOpen=false;
    userInterfaceChangeMoviePosition=false;


}
void MainWindow::slotRecvImage(QImage *img){
    QString arq=QFileDialog::getSaveFileName(this,tr("Open File"),"","png (*.png);;jpg (*.jpg)" );
    if(arq.size()>0){
        img->save(arq);
    }
    delete img;
}

void MainWindow::slotOpenFile(){
    QString arq=QFileDialog::getOpenFileName(this, tr("Open File"),"","png (*.png);;jpg (*.jpg);;mp4 (*.mp4);;webm (*.webm)");
    ui->horizontalSlider->setValue(0);
    if(arq.size()>0){
        if(arq.right(3)=="jpg" || arq.right(3)=="png"){
            movieIsOpen=false;
            emit signalSendImage(new QImage (arq));
        }
        else{
            movieIsOpen=true;

            qMediaPlayerPlayer->setMedia(QUrl::fromLocalFile(arq));
            qMediaPlayerPlayer->play();            


        }
    }
}
void MainWindow::slotChangePositionByMovie(qint64 duration){
    ui->horizontalSlider->setValue(qMediaPlayerPlayer->position()/1000);
}
void MainWindow::slotDurationChanged(qint64 duration){

    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(duration/1000);
    ui->horizontalSlider->setValue(qMediaPlayerPlayer->position()/1000);
}
void MainWindow::slotChangePositionInMovie(){
    if(movieIsOpen){
        qMediaPlayerPlayer->setPosition((qint64)ui->horizontalSlider->value()*1000);
        qMediaPlayerPlayer->play();
    }
}
void MainWindow::slotPlay(){
    if(movieIsOpen) qMediaPlayerPlayer->play();
}
void MainWindow::slotPause(){
    if(movieIsOpen) qMediaPlayerPlayer->pause();
}

void MainWindow::slotChangeParameterInFilter(int value){
    float valueF=((float)value)/1000.0;

    ui->labelParameter->setText(QString::number(valueF));

    if(filter==FilterAttributes::filterTypeEdge) ui->openGLWidget->setEdgeThreshould(valueF);
    if(filter==FilterAttributes::filterTypeBloom) ui->openGLWidget->setLumThresh(valueF);
    if(filter==FilterAttributes::filterTypeGamma) ui->openGLWidget->setGamma(valueF);
    if(filter==FilterAttributes::filterTypeWave) ui->openGLWidget->setWaveFrequency(valueF);


}
void MainWindow::slotChangeFilter(int filter){
    if(filter==FilterAttributes::filterTypeNone || filter==FilterAttributes::filterTypeBlur || filter==FilterAttributes::filterTypeSharpen || filter==FilterAttributes::filterTypeUnsharpen || filter==FilterAttributes::filterTypeNegativo){
        ui->horizontalSliderParameter->setVisible(false);
        ui->labelParameter->setVisible(false);
    }
    if(filter==FilterAttributes::filterTypeEdge){
        ui->horizontalSliderParameter->setVisible(true);
        ui->labelParameter->setVisible(true);
        ui->labelParameter->setText("0.2");
        ui->horizontalSliderParameter->setMinimum(FilterAttributes::minFilterTypeEdge);
        ui->horizontalSliderParameter->setMaximum(FilterAttributes::maxFilterTypeEdge);
        ui->horizontalSliderParameter->setValue(200);
    }
    if(filter==FilterAttributes::filterTypeBloom){
        ui->horizontalSliderParameter->setVisible(true);
        ui->labelParameter->setVisible(true);
        ui->labelParameter->setText("0.5");
        ui->horizontalSliderParameter->setMinimum(FilterAttributes::minFilterTypeBloom);
        ui->horizontalSliderParameter->setMaximum(FilterAttributes::maxFilterTypeBloom);
        ui->horizontalSliderParameter->setValue(900);
    }
    if(filter==FilterAttributes::filterTypeGamma){
        ui->horizontalSliderParameter->setVisible(true);
        ui->labelParameter->setVisible(true);
        ui->labelParameter->setText("0.7");
        ui->horizontalSliderParameter->setMinimum(FilterAttributes::minFilterTypeGamma);
        ui->horizontalSliderParameter->setMaximum(FilterAttributes::maxFilterTypeGamma);
        ui->horizontalSliderParameter->setValue(700);
    }
    if(filter==FilterAttributes::filterTypeWave){
        ui->horizontalSliderParameter->setVisible(true);
        ui->labelParameter->setVisible(true);
        ui->labelParameter->setText("0.0");
        ui->horizontalSliderParameter->setMinimum(FilterAttributes::minFilterTypeWave);
        ui->horizontalSliderParameter->setMaximum(FilterAttributes::maxFilterTypeWave);
        ui->horizontalSliderParameter->setValue(0);

    }
    this->filter=filter;
}
MainWindow::~MainWindow()
{
    delete ui;

}
