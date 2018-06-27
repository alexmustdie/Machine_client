#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"


zmq::context_t context(1);
zmq::socket_t socket(context, ZMQ_REQ);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   std::ifstream f;
   f.open("ip.txt"); //конструктор
   std::string s_ip;
   f>>s_ip;
   std::cout << s_ip.c_str() << std::endl;
   f.close();
   ui->setupUi(this);
   scn = new QGraphicsScene(this);
   std::cout << "Launching the program" << std::endl;
   std::cout << "Establishing connection" << std::endl;
   //QString output = "Done!";
   socket.connect(&s_ip[0]);
   std::cout << "Connection successful" << std::endl;
   input = "Stand by";
   image = new QImage(":/images/standby.jpg");
   fullOutput = "";
   fullOutputNum = 1;
   std::cout << "Tuning player" << std::endl;
   player = new QMediaPlayer(this);
   vw = new QVideoWidget(this);
   player->setVideoOutput(vw);
   player->setVolume(0);  //sound off
   QRect rec = QApplication::desktop()->screenGeometry();
   float height = rec.height();
   float width = rec.width();
   vw->move(width/20, height/20);
   vw->resize(width/1.5, height/1.5);
   vw->hide();

}

void delay(qint64 tmp)
{
    QTime dieTime = QTime::currentTime().addSecs(tmp);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::VideoPlay(QString filename)
{
    //player->setMedia(QUrl::fromLocalFile(filename));
    player->setMedia(QUrl("qrc:/videos/" + filename));
    vw->show();
    player->play();
    delay(1);
    player->duration();
    qint64 tmp = player->duration();
    delay(tmp/1000.0f - 1);
    std::cout << tmp << std::endl;
    vw->hide();
    std::cout << "Video has been played!" << std::endl;

}

int MainWindow::proceed()
{
    scn->clear();
    //while (input != "Ending")
    //{
    zmq::message_t request; //c_str();
    socket.send(input.c_str(), input.length());
    std::cout << "Message sent " + input << std::endl;
    std::cout << "Waiting for reply" << std::endl;
    zmq::message_t reply;
    socket.recv(&reply);
    std::cout << "Reply recieved" << std::endl;
    std::cout << "Saving data to input" << std::endl;
    input = std::string(static_cast<char*>(reply.data()), reply.size());
    if (!input.empty() && (input[input.size() - 1] == '\n' || input[input.size() - 1] == '\r'))
    {
        input.erase(input.size() - 1);
    }
    std::cout << "Saving successful " << input << " " << input.size() << std::endl;
    //}

    if (input == "mscdocument Bolt;")
    {
        isBolt = true;
        isRing = false;
        isShovel = false;
        std::cout << "Bolt" << std::endl;
    } else if (input == "mscdocument Ring;")
    {
        isBolt = false;
        isRing = true;
        isShovel = false;
        std::cout << "Ring" << std::endl;
    } else if (input == "mscdocument Shovel;")
    {
        isBolt = false;
        isRing = false;
        isShovel = true;
        std::cout << "Shovel" << std::endl;
    } else if (input == "Stop")
    {
        //SIGNALS begin
        image = new QImage(":/images/stop.png");
    } else if (input == "Exit")
    {
        image = new QImage(":/images/keepcalm.png");
        //SIGNALS end
    } else {
    if (isBolt)
    {
        //BOLT begin
        if (input == "TAT: out intialize() to SUT; /*1*/")
        {
            image = new QImage(":/images/Bolt1.jpeg");
        } else

        if (input == "TAT: out setPosition ( 0, 0, 0 ) to SUT; /*2*/")
        {
            //VideoPlay("/home/user/TestVideoPlayer/shipping1.wmv");
            //image = new QImage(":/images/Bolt1.jpeg");
            VideoPlay("installation1.wmv");
        } else

        if (input == "TAT: out setTool(_rook) to SUT; /*3*/")
        {
            image = new QImage(":/images/Bolt2.jpeg");
        } else

        if (input == "TAT: out moveTool ( 0, 0, 100, 0, 0 ) to SUT; /*4*/")
        {
            image = new QImage(":/images/Bolt3.jpeg");
        } else

        if (input == "TAT: out setTool(_rubber) to SUT; /*5*/")
        {
            image = new QImage(":/images/Bolt4.jpeg");
        } else

        if (input == "TAT: out moveTool ( 0, 0, 0, 0, 0 ) to SUT; /*6*/")
        {
            image = new QImage(":/images/Bolt5.jpeg");
        } else

        if (input == "TAT: out setTool(_blank) to SUT; /*7*/")
        {
            image = new QImage(":/images/Bolt6.jpeg");
        } else

        if (input == "TAT: out EndWork() to SUT; /*8*/")
        {
            //image = new QImage(":/images/Bolt6.jpeg");
            VideoPlay("shipping1.wmv");
        }
        //BOLT end
    } else if (isRing)
    {
        //RING begin
        if (input == "TAT: out initialize() to SUT; /*1*/")
        {
            image = new QImage(":/images/Ring1.jpeg");
        } else

        if (input == "TAT: out setPosition ( 50, 50, 100 ) to SUT; /*2*/")
        {
            //VideoPlay("/home/user/TestVideoPlayer/shipping1.wmv");
            //image = new QImage(":/images/Ring1.jpeg");
            VideoPlay("installation2.wmv");
        } else

        if (input == "TAT: out setTool(_spike) to SUT; /*3*/")
        {
            image = new QImage(":/images/Ring2.jpeg");
        } else

        if (input == "TAT: out moveTool ( 45, 45, 100, 0, 0 ) to SUT; /*4*/")
        {
            image = new QImage(":/images/Ring3.jpeg");
        } else

        if (input == "TAT: out setTool(_blank) to SUT; /*5*/")
        {
            image = new QImage(":/images/Ring3.jpeg");
        } else

        if (input == "TAT: out moveTool ( 50, 50, 110, 0, 0 ) to SUT; /*6*/")
        {
            image = new QImage(":/images/Ring3.jpeg");
        } else

        if (input == "TAT: out setTool(_needle) to SUT; /*7*/")
        {
            image = new QImage(":/images/Ring4.jpeg");
        } else

        if (input == "TAT: out moveTool ( 50, 50, 112, 0, 0 ) to SUT; /*8*/")
        {
            image = new QImage(":/images/Ring5.jpeg");
        } else

        if (input == "TAT: out setTool(_blank) to SUT; /*9*/")
        {
            image = new QImage(":/images/Ring5.jpeg");
        } else

        if (input == "TAT: out moveTool ( 60, 55, 110, 0, 0 ) to SUT; /*10*/")
        {
            image = new QImage(":/images/Ring5.jpeg");
        } else

        if (input == "TAT: out setTool(_press) to SUT; /*11*/")
        {
            image = new QImage(":/images/Ring6.jpeg");
        } else

        if (input == "TAT: out moveTool ( 60, 55, 0, 0, 0 ) to SUT; /*12*/")
        {
            image = new QImage(":/images/Ring7.jpeg");
        } else

        if (input == "TAT: out moveTool ( 0, 0, 50, 0, 0 ) to SUT; /*13*/")
        {
            image = new QImage(":/images/Ring8.jpeg");
        } else

        if (input == "TAT: out setTool(_blank) to SUT; /*14*/")
        {
            image = new QImage(":/images/Ring8.jpeg");
        } else

        if (input == "TAT: out EndWork() to SUT; /*15*/")
        {
            //image = new QImage(":/images/Ring8.jpeg");
            VideoPlay("shipping1.wmv");
        }
        //RING end
    } else if (isShovel)
    {
        //SHOVEL begin input.erase(input.size() - 1)
        if (input == "TAT: out initialize() to SUT; /*1*/ ")
        {
            image = new QImage(":/images/Shovel1.jpeg");
        } else

        if (input == "TAT: out setPosition ( 0, 0, 100 ) to SUT; /*2*/")
        {
            //VideoPlay("/home/user/TestVideoPlayer/shipping1.wmv");
            //image = new QImage(":/images/Shovel2.jpeg");
            VideoPlay("installation3.wmv");
        } else

        if (input == "TAT: out setTool(_spike) to SUT; /*3*/")
        {
            image = new QImage(":/images/Shovel2.jpeg");
        } else

        if (input == "TAT: out moveTool ( 0, 0, 75, 0, 0 ) to SUT; /*4*/")
        {
            image = new QImage(":/images/Shovel3.jpeg");
        } else

        if (input == "TAT: out moveTool ( 25, 25, 100, 0, 0 ) to SUT; /*5*/")
        {
            image = new QImage(":/images/Shovel4.jpeg");
        } else

        if (input == "TAT: out setTool(_blank) to SUT; /*6*/")
        {
            image = new QImage(":/images/Shovel4.jpeg");
        } else

        if (input == "TAT: out moveTool ( -10, 0, 75, 0, 0 ) to SUT; /*7*/")
        {
            image = new QImage(":/images/Shovel5.jpeg");
        } else

        if (input == "TAT: out setTool(_needle) to SUT;  /*8*/")
        {
            image = new QImage(":/images/Shovel5.jpeg");
        } else

        if (input == "TAT: out moveTool ( 0, 0, 50, 0, 0 ) to SUT; /*9*/")
        {
            image = new QImage(":/images/Shovel6.jpeg");
        } else

        if (input == "TAT: out moveTool ( -15, 0, 60, 0, 0 ) to SUT; /*10*/")
        {
            image = new QImage(":/images/Shovel7.jpeg");
        } else

        if (input == "TAT: out setTool(_blank) to SUT;  /*11*/")
        {
            image = new QImage(":/images/Shovel7.jpeg");
        } else

        if (input == "TAT: out moveTool ( 0, 0, 100, 0, 0 ) to SUT; /*12*/")
        {
            image = new QImage(":/images/Shovel7.jpeg");
        } else

        if (input == "TAT: out setTool(_spike) to SUT; /*13*/")
        {
            image = new QImage(":/images/Shovel8.jpeg");
        } else

        if (input == "TAT: out shave ( 25, 0, 2, 0, 1 ) to SUT; /*14*/")
        {
            image = new QImage(":/images/Shovel9.jpeg");
        } else

        if (input == "TAT: out shave ( 25, 0, 5, 0, 0 ) to SUT; /*15*/")
        {
            image = new QImage(":/images/Shovel10.jpeg");
        } else

        if (input == "TAT: out setTool(_blank) to SUT; /*переход  16*/")
        {
            image = new QImage(":/images/Shovel10.jpeg");
        } else

        if (input == "TAT: out moveTool ( 0, 0, 50, 0, 0 ) to SUT; /*17*/")
        {
            image = new QImage(":/images/Shovel11.jpeg");
        } else

        if (input == "TAT: out setTool(_drill) to SUT; /*18*/")
        {
            image = new QImage(":/images/Shovel11.jpeg");
        } else

        if (input == "TAT: out drill () to SUT; /*19*/")
        {
            image = new QImage(":/images/Shovel12.jpeg");
        } else

        if (input == "TAT: out EndWork() to SUT;  /*20*/")
        {
            //image = new QImage(":/images/Shovel12.jpeg");
            VideoPlay("shipping1.wmv");
        }
        //SHOVEL end
    }
    }

    // object defined in header
    ui->graphicsView->setScene(scn);
    if (input != "Null") {
        QString qInput = QString::fromStdString(input);
        ui->lineEdit->setText(qInput);
        fullOutput += QString::number(fullOutputNum) + " " + qInput + "\n";
        ui->textEdit->setText(fullOutput);
        fullOutputNum++;
    }
    scn->addPixmap(QPixmap::fromImage(*image));
    return 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    socket.close();
}


void MainWindow::showEvent(QShowEvent *)
{
    ui->graphicsView->fitInView(scn->sceneRect(),Qt::KeepAspectRatio);
}
