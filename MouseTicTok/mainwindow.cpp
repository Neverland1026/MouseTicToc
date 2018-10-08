#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化变量
    timer = new QTimer(this);
    desktop = QApplication::desktop();
    button_width = 200;
    button_height = 50;
    connect(timer, SIGNAL(timeout()), this, SLOT(mouseClickToDownCPU()));

    //设置窗口大小
    this->setFixedSize(button_width,button_height);

    //设置窗口置顶 居中
    this->move((desktop->width() - this->width())/2, 0/*(desktop->height() - this->height())/2*/);

    //设置pushbutton的大小
    ui->pushButton->setFixedWidth(button_width);
    ui->pushButton->setFixedHeight(button_height);

    //设置属性（如果为了统一管理样式，
    //便于子窗口和控件继承，可以把下列语句放到main函数里），
    //只设置这些的话窗口无法移动
    //this->setWindowOpacity(0.5); //窗口整体透明度，0-1 从全透明到不透明
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //设置无边框风格
    this->setAttribute(Qt::WA_TranslucentBackground); //设置背景透明，允许鼠标穿透

    // 加载QSS样式
    //this->loadStyleSheet("../MouseTicTok/QSS/style.qss");
    ui->pushButton->setStyleSheet("QPushButton#pushButton {"
                                  "color:white;"
                                  "border-radius:25px;"
                                  "font-size:30px;"
                                  "background: rgb(0,205,102)"
                                  "}");

    //响应事件
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(btnClick()));


}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete desktop;
}

void MainWindow::loadStyleSheet(const QString &styleSheetFile)
{
    QFile file(styleSheetFile);
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());//读取样式表文件
        this->setStyleSheet(styleSheet);//把文件内容传参
        file.close();
    }
    else
    {
        QMessageBox::information(this,"tip","cannot find qss file");
    }
}


void MainWindow::btnClick(){
    if(ui->pushButton->text() == "TicToc"){
        ui->pushButton->setText(QString("Banned!!!"));
        ui->pushButton->setStyleSheet("QPushButton#pushButton {"
                                      "color:white;"
                                      "border-radius:25px;"
                                      "font-size:30px;"
                                      "background:red;"
                                      "}");
        //开始点击鼠标
        timer->start(5000);  //每5s执行依次单击事件
    }
    else{
        ui->pushButton->setText(QString("TicToc"));
        ui->pushButton->setStyleSheet("QPushButton#pushButton {"
                                      "color:white;"
                                      "border-radius:25px;"
                                      "font-size:30px;"
                                      "background:rgb(0,205,102)"
                                      "}");
        //关闭点击事件
        timer->stop();
    }
}

void MainWindow::mouseClickToDownCPU(){
    qDebug() << "tic";
    //实现降低CPU的事件
    QPoint pos(0, 0);
    //press
    QMouseEvent event0(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(this, &event0);
    //release
    QMouseEvent event1(QEvent::MouseButtonRelease, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(this, &event1);

}

void MainWindow::mousePressEvent(QMouseEvent * event){\
    static int count = 0;
    if(event->button() == Qt::RightButton)
    {
        count++;
        if(count >= 3){
            timer->stop();
            this->close();
        }
    }
}

