#include "mywidget.h"
#include "ui_mywidget.h"
#include "QVBoxLayout"
#include <QLayout>
#include "glwidget.h"

#include <QFileDialog>   //文件对话框

#include <QDebug>
#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"

myWidget::myWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myWidget),
    Myglwidget(new glwidget)
{
    ui->setupUi(this);
    QVBoxLayout* mylayout = new QVBoxLayout;
    //Myglwidget->moveToThread(&threadforball);
    //threadforball.start();
    mylayout->addWidget(Myglwidget);
    this->ui->widget->setLayout(mylayout);

}

myWidget::~myWidget()
{
    delete ui;
}

/******************************************************************************
 *                             Btn Events
 *****************************************************************************/
void myWidget::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"Open","../Ball/resource","STL(*.stl)");
    if(path.isEmpty() == false)
    {
        cout<<"SUCCEFF";
        ui->lineEdit->setText(path);
        QByteArray ba = path.toLocal8Bit();
        const char *cpath = ba.data();
        stlFile readFile;
        isOk = readFile.ReadFile(cpath);
        //QVector<Triangle> triangleList;
        triangleList = readFile.GetTriangleList();

        if(isOk == true)   //读取成功
        {
            cout<<"read successfully";
            Myglwidget->getTriangle(triangleList);
        }
        else
        {
            cout<<"read fail";
        }
    }
    else
    {
        cout<<"文件路径获取失败";
    }
}

void myWidget::on_reset_ball_pressed()
{
    if(Myglwidget){
        Myglwidget->setRadius(0.5);
        Myglwidget->setTranX(0.0);
        Myglwidget->setTranY(0.0);
        Myglwidget->setTranZ(Myglwidget->getRadius());
        Myglwidget->setRotX(0.0);
        Myglwidget->setRotY(0.0);
        Myglwidget->setRotZ(0.0);
        Myglwidget->setMotion(0.0,0.0);
    }
}

void myWidget::on_reset_view_pressed()
{
    if(Myglwidget){
        Vector3d pos(0.0, 0.0, 30.0);
        Vector3d target(0.0, 0.0, 0.0);
        Vector3d up(0.0, 1.0, 0.0);
        Myglwidget->setCam(pos, target, up);
    }
}

void myWidget::on_pushButton_exit_pressed()
{
    exit(0);
}

/******************************************************************************
 *                            Silder Events
 *****************************************************************************/
void myWidget::on_horizontalSlider_valueChanged(int value)
{
    Myglwidget->setFrictionCof(GLdouble(value)/100.0);
}


void myWidget::on_horizontalSlider_g_valueChanged(int value)
{
    Myglwidget->setGravity(GLdouble(value)/1000.0);
}

void myWidget::on_horizontalSlider_L_valueChanged(int value)
{
    Myglwidget->setLossCof(GLdouble(value)/10.0);
}
