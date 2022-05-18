#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QThread>

GLfloat plane_angle = 0.0f;
GLfloat plane_height = 0.0f;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    indicator = new AttitudeIndicator();
    InitAttitudeIndicator();

    wView = new QWebEngineView();
    InitWebView();
    //wView->load(QUrl("https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B3%D0%BB%D0%B0%D0%B2%D0%BD%D0%B0%D1%8F_%D1%81%D1%82%D1%80%D0%B0%D0%BD%D0%B8%D1%86%D0%B0"));
    oper = new THR_uiOp(&port_status, ui);
    oper->start(QThread::NormalPriority);

    plane_oper = new THR_planeOp(&plane_angle, &plane_height);
    plane_oper->start(QThread::LowPriority);
}

MainWindow::~MainWindow()
{
    for(int i = 0; i < 6; i++)
    {
        arr_lnk_com_port[i].terminate();
    }
    oper->terminate();
    plane_oper->terminate();
    delete wView;
    delete frame;
    delete ui;
}

void MainWindow::InitWebView()
{
    if(ui->groupBox_2->layout())
    {
        QLayoutItem* child;
        while((child = ui->groupBox_2->layout()->takeAt(0)) != 0)
        {
            delete child->widget();
            delete child;
        }
        delete ui->groupBox_2->layout();
    }
    QGridLayout *layout = new QGridLayout(ui->groupBox_2);
    ui->groupBox_2->setLayout(layout);
    layout->addWidget(wView);
}
bool MainWindow::LoadMap()
{

    return true;
}

void MainWindow::InitAttitudeIndicator()
{

    if(ui->groupBox_3->layout())
    {
        QLayoutItem* child;
        while((child = ui->groupBox_3->layout()->takeAt(0)) != 0)
        {
            delete child->widget();
            delete child;
        }
        delete ui->groupBox_3->layout();
    }
    QGridLayout *layout = new QGridLayout(ui->groupBox_3);
    ui->groupBox_3->setLayout(layout);

    layout->addWidget(indicator);
}

void MainWindow::on_pushButton_6_clicked()
{
    frame = new plane_frame();
    frame->show();
}


void MainWindow::on_pushButton_3_clicked() // положение самолёта
{
    //Взаимодействие с картой - поставить точку нахождения самолёта
    /* Скрипт для карты
     * <script type="text/javascript" charset="utf-8" async src="https://api-maps.yandex.ru/services/constructor/1.0/js/?um=constructor%3A8c82999baeed8a1e32b7c195e68b9988d09d40b51260272dac062fe86a0ebae2&amp;width=500&amp;height=400&amp;lang=ru_RU&amp;scroll=true"></script>
    */
    return;
}
void MainWindow::angleChanged(AttitudeIndicator *indic)//проставить if на изменение угла и зависимости кнопок
{
    //indic->setAngle(indic->p_moveable_model);
}

void MainWindow::on_pushButton_4_clicked()
{
    for(int i = 0; i < 6; i++)
    {
        arr_lnk_com_port[i].start();
        qDebug() << "Поток №" << i + 1 <<" включен";
    }
}


void MainWindow::on_pushButton_clicked()
{
    wView->load(QUrl("https://obscure-caverns-05989.herokuapp.com/"));
}

void THR_uiOp::run()
{
    while(true) // сделать побитовое считывание через XOR c port_status
    {
//        ui_thr->label_15->setText("ахахахаха, я сломался");
//        sleep(1);
//        ui_thr->label_15->setText("Не установлено1");
    }
}

