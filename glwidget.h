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
    void setFrictionCof(GLdouble value){u = value;}
    void setGravity(GLdouble value){g = value;}
    void setLossCof(GLdouble value){L = value;}


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

public:
    void setTranX(GLfloat value){tranX = value;}
    void setTranY(GLfloat value){tranY = value;}
    void setTranZ(GLfloat value){tranZ = value;}
    void setRotX(GLfloat value){rotationX = value;}
    void setRotY(GLfloat value){rotationY = value;}
    void setRotZ(GLfloat value){rotationZ = value;}
    void setRadius(GLdouble value){radius = value;}
    GLdouble getRadius(){return radius;}
    void setMotion(GLdouble x,GLdouble y){motion.dx=x;motion.dy=y;}
    void setCam(const Vector3d& pos, const Vector3d& target, const Vector3d& up){
        cam.setCamera(pos, target, up);
    }

private:
    void draw();
    void drawTri();
    void drawBase();
    QVector<Triangle> ballVList;
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
    bool btn_right_release;

    GLdouble u; //friction cof
    GLdouble g; //gravity cof
    GLdouble L; //loss cof
    GLdouble radius; //ball radius

    // mouse motion
    struct Motion{
        GLdouble dx;
        GLdouble dy;
        double m[16]={1,0,0,0,
                      0,1,0,0,
                      0,0,1,0,
                      0,0,0,1};
    };
    Motion motion;

};

#endif // GLWIDGET_H
