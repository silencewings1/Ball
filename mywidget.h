#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "readstlfil.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QGLWidget>
#include "glwidget.h"



#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

namespace Ui {
class myWidget;
}

class myWidget : public QWidget
{
    Q_OBJECT

public:
    explicit myWidget(QWidget *parent = 0);
    ~myWidget();


private slots:
    void on_pushButton_clicked();

private:
     QVector<Triangle> triangleList;
     glwidget*  Myglwidget = new glwidget;
     Ui::myWidget *ui;

};

#endif // MYWIDGET_H