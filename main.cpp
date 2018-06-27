#include "mainwindow.h"
#include <QApplication>
#include "QTime"
#include "QCoreApplication"
#include "QEventLoop"

void delay()
{
    QTime dieTime = QTime::currentTime().addSecs(3);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    while (true) {
        if (!w.input.compare("Exit")) {
            break;
        }
        w.proceed();
        QShowEvent();
        w.showMaximized();
        delay();
    }

//    QGraphicsScene scene;
//    QGraphicsView view(&scene);
//    QPixmap pixmapl(":/images/Lexa1.jpeg");
//    QPixmap pixmapf(":/images/Flying_cat.jpeg");
//    QGraphicsPixmapItem item(pixmapl);
//    scene.addItem(&item);
//    view.show();

    return a.exec();
}
