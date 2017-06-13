#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QDebug>
#include <QMediaPlayer>
#include <QVideoProbe>
#include <QVideoFrame>
#include <QGraphicsVideoItem>
#include <QVideoWidget>
#include <QColor>
#include <QMouseEvent>
#include "videosurface.h"
#include "filterattributes.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void slotOpenFile();
    void slotRecvImage(QImage *img);
    void slotChangeFilter(int filter);
    void slotChangeParameterInFilter(int value);
    void slotChangePositionInMovie();
    void slotDurationChanged(qint64 duration);
    void slotChangePositionByMovie(qint64 value);
    void slotPlay();
    void slotPause();   
signals:
void signalSendImage(QImage *img);
private:
    Ui::MainWindow *ui;    
    QMediaPlayer *qMediaPlayerPlayer;
    int filter;
    bool movieIsOpen;
    bool userInterfaceChangeMoviePosition;
};

#endif // MAINWINDOW_H
