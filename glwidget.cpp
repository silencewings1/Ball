#include "glwidget.h"

glwidget::glwidget(QWidget *parent) : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    tranX = 0.0;
    tranY = 0.0;
    tranZ = -10.0;
    rotationX = -21.0;
    rotationY = -57.0;
    rotationZ = -0.0;
    ball.x = 2;
    connect(this,SIGNAL(sendMotion(const float *)),this,SLOT(motionDisplay(const float *)),Qt::QueuedConnection);

}

glwidget::~glwidget()
{

}

void glwidget::initializeGL()
{
    // 启用阴影平滑
    glShadeModel( GL_SMOOTH );
    // 黑色背景
    glClearColor( 1.0, 1.0, 1.0, 0.0 );
    // 设置深度缓存
    glClearDepth( 1.0 );
    // 启用深度测试
    glEnable( GL_DEPTH_TEST );
    // 所作深度测试的类型
    glDepthFunc( GL_LEQUAL );
    // 告诉系统对透视进行修正
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    //glutSwapBuffers();//设立双缓冲

    setFocusPolicy(Qt::StrongFocus);

}

void glwidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(w) / h;
    glFrustum(-x,+x,-1.0,+1.0,4.0,15.0);
    glMatrixMode(GL_MODELVIEW);

}

void glwidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);    // 清除屏幕和深度缓存
    glLoadIdentity();
    // 重置当前模型的观察矩阵
    draw();
}

void glwidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void glwidget::mouseReleaseEvent(QMouseEvent *event){
    GLfloat motion[2];
    motion[0] = GLfloat(event->x() - lastPos.x()) / width();
    motion[1] = GLfloat(event->y() - lastPos.y()) / height();
    emit sendMotion(motion);
}

void glwidget::mouseMoveEvent(QMouseEvent *event)
{
    //    GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
    //    GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();
    //    if(event->buttons() & Qt::LeftButton){
    //        rotationX -= 180 * dy;
    //        rotationY -= 180 * dx;
    //        updateGL();
    //    }
    //    else if(event->buttons() & Qt::RightButton){
    //        tranX += 5*dx;
    //        tranY -= 5*dy;
    //        updateGL();
    //    }
    //    lastPos = event->pos();
}


void glwidget::wheelEvent(QWheelEvent *event)
{
    tranZ += -event->delta()*0.001f;
    updateGL();
}

//#include <QKeyEvent>
void glwidget::keyPressEvent(QKeyEvent *event){

    // Test KeyPress
    switch(event->key()){
    case Qt::Key_L:
        qDebug("Key_L ");
        break;
    case Qt::Key_Up:
        tranY += 0.05f;
        updateGL();
        break;
    case Qt::Key_Down:
        tranY -= 0.05f;
        updateGL();
        break;
    case Qt::Key_Left:
        tranX -= 0.05f;
        updateGL();
        break;
    case Qt::Key_Right:
        tranX += 0.05f;
        updateGL();
        break;
    }

}

void glwidget::motionDisplay(const float * motion){
    GLfloat dx = motion[0];
    GLfloat dy = motion[1];
    qDebug("Pos: %d %d",dx,dy);
    GLfloat u = 0.1f;
    GLfloat t = 0.0f;
    while(abs(1-u*t)>0.0f){
        dx *= 1-u*t;
        dy *= 1-u*t;
        tranX += dx;
        tranY -= dy;
        rotationX += 180.0f*dy;
        rotationY += 180.0f*dx;
        t++;
        Sleep(100);
        updateGL();
    }
}


void glwidget::draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(0.0, 0.0, -5.0);
    glTranslatef(tranX,tranY,tranZ);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);

    GLUquadricObj *quadObj; //创建一个二次曲面
    quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj,GLU_SILHOUETTE);
    glShadeModel(GL_SMOOTH);
    glColor3f(0.0f,0.0f,1.0f);
    gluSphere(quadObj,0.5f,50.0f,50.0f);
    gluDeleteQuadric(quadObj);
    //glutSolidSphere(2,50,50);

}

