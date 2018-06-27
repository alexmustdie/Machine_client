#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string.h>
#include <unistd.h>
#include "iostream"
#include <zmq.hpp>
#include <iostream>
#include <fstream>

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QKeyEvent>
#include <QImage>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QTime>
#include <QDesktopWidget>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int proceed();
    std::string input;
    void VideoPlay(QString filename);

private:
    void showEvent(QShowEvent *event);
    Ui::MainWindow *ui;
    QImage *image;
    QGraphicsScene *scn;
    QString *output;
    QString fullOutput;
    int fullOutputNum;
    bool isBolt = false;
    bool isRing = false;
    bool isShovel = false;
    QMediaPlayer* player;
    QVideoWidget* vw;
};

#endif // MAINWINDOW_H
