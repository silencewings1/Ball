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

#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>


class glwidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit glwidget(QWidget *parent = 0);
    ~glwidget();

protected:
    void  initializeGL();
    void  resizeGL(int w, int h);
    void  paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    //void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);

signals:
    void sendMotion(const float *);

private slots:
    void motionDisplay(const float *);

private:
    void draw();
    GLfloat tranX;
    GLfloat tranY;
    GLfloat tranZ;
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    QPoint lastPos;
    typedef struct b //定义储存球体的结构
    {
        GLfloat x;

    } Ball;
    Ball ball;

};

#endif // GLWIDGET_H
