#include "glwidget.h"
#include <iostream>

glwidget::glwidget(QWidget *parent) : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    tranX = 0.0;
    tranY = 0.0;
    tranZ = 0.0;
    rotationX = 0.0;
    rotationY = 0.0;
    rotationZ = 0.0;
    u = 0.1;
    g = 0.02;
    L = 0.1;
    radius = 0.5;
    btn_right_release = false;
    motion.dx = 0.0;
    motion.dy = 0.0;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(motionDisplay()));
    timer->start(20);
}

glwidget::~glwidget()
{

}

/******************************************************************************
 *                             GL Related
 *****************************************************************************/
void glwidget::initializeGL()
{
    // 启用阴影平滑
    glShadeModel( GL_SMOOTH );
    // 黑色背景
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    // 设置深度缓存
    glClearDepth( 1.0 );
    // 启用深度测试
    glEnable( GL_DEPTH_TEST );
    // 所作深度测试的类型
    glDepthFunc( GL_LEQUAL );
    // 告诉系统对透视进行修正
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    //glutSwapBuffers();//设立双缓冲

    GLfloat light0Position[] = {0.0f, -50.0f, 50.0f, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    setFocusPolicy(Qt::StrongFocus);

    Vector3d pos(0.0, 0.0, 30.0);
    Vector3d target(0.0, 0.0, 0.0);
    Vector3d up(0.0, 1.0, 0.0);
    cam.setCamera(pos, target, up);
}

void glwidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(w) / GLfloat(h);
    glFrustum(-0.5*x,+0.5*x,-0.5,+0.5,4.0,100.0);
    //cam.setShape(45.0,x, 4.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void glwidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// 清除屏幕和深度缓存
    GLfloat light0Position[] = {0.0f, -50.0f, 50.0f, 0.0}; //dot light
    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
    glLoadIdentity();
    cam.setModelViewMatrix();

    if(isRead)
        drawTri();
    drawBase();
}

void glwidget::drawBase()
{
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glPushMatrix();

    glTranslatef(0.0,0.0,0.0);
    glRotatef(0, 1.0, 0.0, 0.0);
    glRotatef(0, 0.0, 1.0, 0.0);
    glRotatef(0, 0.0, 0.0, 1.0);
    glEnable(GL_LIGHTING);
    glBegin(GL_POLYGON);
    glColor4f(0.5,0.5,0.5,0.5f);
    glDepthMask(GL_FALSE);

    glBegin(GL_POLYGON);
    float u = 5.0f;
    glVertex3f(-u,-u,0);
    glVertex3f(u,-u,0);
    glVertex3f(u,u,0);
    glVertex3f(-u,u,0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0,0,3.5);
    glEnd();

    glPopMatrix();
    glDepthMask(GL_TRUE);
    glDisable(GL_LIGHTING);
    glDisable((GL_COLOR_MATERIAL));

}

void glwidget::drawTri()
{
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glDepthMask(GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glTranslatef(tranX,tranY,tranZ);//-3.0f);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);

    //    GLfloat a = 1.0f;
    //    for(int i = 0;i<ballVList.size();i++)
    //    {

    //        glBegin(GL_LINES);
    //        glColor3f(0.3f,0.3f,1.0f);
    //        glVertex3f(ballVList[i].V[0].x/a,ballVList[i].V[0].y/a,ballVList[i].V[0].z/a);
    //        glVertex3f(ballVList[i].V[1].x/a,ballVList[i].V[1].y/a,ballVList[i].V[1].z/a);

    //        glVertex3f(ballVList[i].V[1].x/a,ballVList[i].V[1].y/a,ballVList[i].V[1].z/a);
    //        glVertex3f(ballVList[i].V[2].x/a,ballVList[i].V[2].y/a,ballVList[i].V[2].z/a);

    //        glVertex3f(ballVList[i].V[2].x/a,ballVList[i].V[2].y/a,ballVList[i].V[2].z/a);
    //        glVertex3f(ballVList[i].V[0].x/a,ballVList[i].V[0].y/a,ballVList[i].V[0].z/a);
    //        glEnd();

    //    }

    //    //    for(int i=1;i<Ctrace.size();i++){
    //    //        glBegin(GL_LINES);
    //    //        glColor3f(1.0f,0.0f,0.0f);

    //    //        //glVertex3f()
    //    //        glEnd();
    //    //    }

    GLfloat a = 1.0f;
    glBegin(GL_TRIANGLES);
    glShadeModel(GL_SMOOTH);
    glColor4f(0.4f, 0.4f, 1.0f,1);
    for(int i = 0;i<ballVList.size();i++)
    {
        glNormal3f(ballVList[i].N.x,ballVList[i].N.y,ballVList[i].N.z);
        glVertex3f(ballVList[i].V[0].x/a,ballVList[i].V[0].y/a,ballVList[i].V[0].z/a);
        glVertex3f(ballVList[i].V[1].x/a,ballVList[i].V[1].y/a,ballVList[i].V[1].z/a);
        glVertex3f(ballVList[i].V[2].x/a,ballVList[i].V[2].y/a,ballVList[i].V[2].z/a);
    }
    glEnd();
    glDisable(GL_LIGHTING);
    glDisable((GL_COLOR_MATERIAL));
    glPopMatrix();
}

void glwidget::getTriangle(QVector<Triangle> triangleList)
{
    ballVList = triangleList;
    isRead = true;
}

/******************************************************************************
 *                             Mouse & Key
 *****************************************************************************/
void glwidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();

    GLfloat xtmp = rotationX;
    GLfloat ytmp = rotationY;
    GLfloat ztmp = rotationZ;
    rotationX = 0.0;
    rotationY = 0.0;
    rotationZ = 0.0;
    updateGL();
    if (event->buttons() & Qt::LeftButton){
        if(btn_right_release == true){
            glGetDoublev(GL_MODELVIEW_MATRIX, motion.m);
            btn_right_release = false;
        }
    }
    rotationX = xtmp;
    rotationY = ytmp;
    rotationZ = ztmp;
}

void glwidget::mouseReleaseEvent(QMouseEvent *event)
{
    motion.dx += GLdouble(event->x() - lastPos.x()) / width();
    motion.dy += GLdouble(event->y() - lastPos.y()) / width();

    if (Qt::RightButton == event->button()){
        btn_right_release = true;
    }
}

void glwidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    if (event->buttons() & Qt::RightButton)
    {
        //右键绕x，y轴旋转
        RotateX(dx);
        RotateY(dy);
        lastPos = event->pos();
    }
    else if(event->buttons() & Qt::MiddleButton)
    {
        //中键平移
        cam.slide(-(float)dx*0.01f,(float)dy*0.01f,0);
        lastPos = event->pos();
    }
    updateGL();
}

void glwidget::wheelEvent(QWheelEvent *event)
{
    float dz=-event->delta()*0.01f;
    cam.slide(0,0,dz);
    updateGL();
}

//#include <QKeyEvent>
void glwidget::keyPressEvent(QKeyEvent *event)
{
    // Test KeyPress
    switch(event->key()){

    //相机平动
    case Qt::Key_W:
        cam.slide(0,0.2f,0);
        updateGL();
        break;
    case Qt::Key_S:
        cam.slide(0,-0.2f,0);
        updateGL();
        break;
    case Qt::Key_A:
        cam.slide(-0.2f,0,0);
        updateGL();
        break;
    case Qt::Key_D:
        cam.slide(0.2f,0,0);
        updateGL();
        break;

        //相机转动
    case Qt::Key_I:
        RotateY(-1.0f);
        updateGL();
        break;
    case Qt::Key_M:
        RotateY(1.0f);
        updateGL();
        break;
    case Qt::Key_Q:
        RotateX(-1.0f);
        updateGL();
        break;
    case Qt::Key_E:
        RotateX(1.0f);
        updateGL();
        break;
    }

}


/******************************************************************************
 *                             Logic
 *****************************************************************************/
void glwidget::motionDisplay(){
    double * m = motion.m;
    Eigen::MatrixXd T(3, 3);
    T << m[0], m[4], m[8],
            m[1], m[5], m[9],
            m[2], m[6], m[10];
    Eigen::Vector3d p_cam(-motion.dx, motion.dy, 0);
    Eigen::Vector3d p_world = T.inverse() * p_cam;
    std::cout<<"T: "<<T<<std::endl;

    tranX -= p_world(0)/2.0;
    tranY -= p_world(1)/2.0;
    tranZ -= p_world(2)/2.0;
    //    Point3f c(tranX, tranY, tranZ);
    //    Ctrace.push(c);
    //    if(Ctrace.size() >= 50)
    //        Ctrace.pop();
    std::cout<<"tranX: "<<tranX<<std::endl;
    std::cout<<"tranY: "<<tranY<<std::endl;
    std::cout<<"tranZ: "<<tranZ<<std::endl;
    std::cout<<"rotationX: "<<rotationX<<std::endl;
    std::cout<<"rotationY: "<<rotationY<<std::endl;
    std::cout<<"rotationZ: "<<rotationZ<<std::endl;

    if(tranZ-radius < 0){
        tranZ = radius-g/10.0;
        p_world(2) = -p_world(2)*(1-L);
    }else{
        p_world(2) += g;
    }

    // ball rotation
    if(tranZ-radius <= 0){
        rotationX += 180.0*motion.dy;
        rotationY += 180.0*motion.dx;
    }

    // ball transition
    p_cam = T * p_world;
    motion.dx = -p_cam(0);
    motion.dy = p_cam(1);
    if(tranZ-radius <= 0){
        motion.dx = motion.dx*(1-u);
        motion.dy = motion.dy*(1-u);
    }

    updateGL();
}


void glwidget::RotateX(float angle)
{
    float d=cam.getDist();
    int cnt=100;
    float theta=angle/cnt;
    float slide_d=-2*d*sin(theta*3.14159265/360);
    cam.yaw(theta/2);
    for(;cnt!=0;--cnt)
    {
        cam.slide(slide_d,0,0);
        cam.yaw(theta);
    }
    cam.yaw(-theta/2);
}

void glwidget::RotateY(float angle)
{
    float d=cam.getDist();
    int cnt=100;
    float theta=angle/cnt;
    float slide_d=2*d*sin(theta*3.14159265/360);
    cam.pitch(theta/2);
    for(;cnt!=0;--cnt)
    {
        cam.slide(0,slide_d,0);
        cam.pitch(theta);
    }
    cam.pitch(-theta/2);
}
