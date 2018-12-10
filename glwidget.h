#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QGLWidget>
#include <QtOpenGL>
#include "QVector"
//#include "mywidget.h"
#include <QColorDialog>
#include <QTimer>

#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include "triangle.h"
#include "camera.h"

class glwidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit glwidget(QWidget *parent = 0);
    ~glwidget();

    //读写stl的接口函数
    void getTriangle(QVector<Triangle> triangleList);
    void setFrictionCof(GLfloat value){this->u = value;}

protected:
    //GL related
    void  initializeGL();
    void  resizeGL(int w, int h);
    void  paintGL();

    //mouse & key
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    //void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void motionDisplay();

private:
    void draw();
    void drawTri();
    void drawBase();
    QVector<Triangle> myList;
    bool isRead = false;

    GLCamera cam;
    void RotateX(float angle);
    void RotateY(float angle);

    GLfloat tranX;
    GLfloat tranY;
    GLfloat tranZ;
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    QPoint lastPos;

    GLfloat u; //friction cof

    // mouse motion
    struct Motion{
        GLfloat dx;
        GLfloat dy;
        double m[16]={1,0,0,0,
                      0,1,0,0,
                      0,0,1,0,
                      0,0,0,1};
        bool flag = false;
    };
    Motion motion;

};

#endif // GLWIDGET_H
