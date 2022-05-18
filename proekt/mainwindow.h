#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Windows.h"
#include <QMainWindow>
#include <QWebEngineView>
#include <QUrl>
#include <QDebug>
#include <QThread>

#include "plane_frame.h"
#include "attitudeindicator.h"
#include "lnk_com_port.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class THR_uiOp;
class THR_planeOp;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QWebEngineView *wView;
    QPointer <plane_frame> frame;
    QPointer <AttitudeIndicator> indicator;
    LNK_COM_PORT arr_lnk_com_port[6];
    qint64 port_status = 0x000001;
    THR_uiOp* oper;
    THR_planeOp* plane_oper;

    void InitWebView();
    bool LoadMap();

    void InitAttitudeIndicator();
    void angleChanged(AttitudeIndicator* indic);


};
#endif // MAINWINDOW_H

class THR_uiOp: public QThread
{
    qint64* status_thr;
    Ui::MainWindow* ui_thr;
public:
    THR_uiOp(qint64* status, Ui::MainWindow* ui)
        : status_thr(status), ui_thr(ui){}
protected:
    void run();
};



class THR_planeOp: public QThread
{
    GLfloat* angle;
    GLfloat* height;
public:
    THR_planeOp(GLfloat* an, GLfloat* hght)
    {
        angle = an;
        height = hght;
    }
protected:
    void run()
    {
        /*while(true)
        {
            *angle += 3;
            sleep(1);
            *height +=0.01f;
        }*/
    }
};
