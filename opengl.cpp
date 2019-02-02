#include "opengl.h"
#include <QOpenGLFunctions>
#include <QDebug>

static QString test=":/pic/test.png";
static QString box_pic =":/pic/box.png";
static QString background_pic =":/pic/sky.jpg";
static QString ground_pic =":/pic/ground.jpg";


mainOpenGL::mainOpenGL(QWidget *p):QOpenGLWidget(p)
{
    setGeometry(0,0,1600,900);
    show();
    setFocus();
    setMouseTracking(true);
    fps = new QTimer(this);
    connect(fps, SIGNAL(timeout()), this, SLOT(update()));
    fps->start(16);//FPS 60

    dx=0;
    dz=1.0f;
}

void mainOpenGL::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->initializeOpenGLFunctions();
    f->glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    f->glEnable(GL_DEPTH_TEST);
    f->glDepthFunc(GL_LEQUAL);
    f->glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    test_3d = new Sprite(box_pic ,0.5f,0.5f,5.0f,0.0f,0.0f,0.0f);
    //test_3d = new Sprite(test ,0,0,3.0f,0.0f,0.0f,0.0f);


    background = new Sprite(background_pic,0,0,0);
    ground = new Sprite(ground_pic);

    box1=new Sprite(test,2.5f,1.0f,70.0f,0,0,0);
    box2=new Sprite(test,-1.5f,0,29.0f,0,0,0);
    box3=new Sprite(test,1.0f,1.5f,22.0f,0,0,0);
    box4=new Sprite(test,-5.5f,0.0f,40.0f,0,0,0);
    box5=new Sprite(test,-3.5f,1.5f,30.0f,0,0,0);
    box6=new Sprite(test,-4.0f,0.5f,60.0f,0,0,0);
}

void mainOpenGL::paintGL()
{

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    f->glClearColor(0.5f, 0.5f, 0.5f, 0.0f);

    QMatrix4x4 mm;
    //mm.scale(1,1,dz);
    mm.translate(dx,0,dz);

    background->Draw();
    ground ->Draw_Ground(m*mm);
    test_3d->Draw_Box(m*mm);

    box1->Draw_Box(m*mm);
    box2->Draw_Box(m*mm);
    box3->Draw_Box(m*mm);
    box4->Draw_Box(m*mm);
    box5->Draw_Box(m*mm);
    box6->Draw_Box(m*mm);
}

void mainOpenGL::resizeGL(int w,int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.1, zFar = 100.0, fov = 45.0;
    m.setToIdentity();
    m.perspective(fov, aspect, zNear, zFar);
    //m.lookAt(QVector3D(0,0,0.0f),QVector3D(0,0,-100.0f),QVector3D(0.0f,1.0f,0.0f));
}

void mainOpenGL::mousePressEvent(QMouseEvent *e)
{
    //TODO
    qDebug()<<e->pos();
}

void mainOpenGL::mouseMoveEvent(QMouseEvent *e)
{
    test_3d->setSpeed(0.0f);
    if((e->x()<500)&&(e->x()>330)&&(e->y()<600)&&(e->y()>450))
        test_3d->setSpeed(2.0f);
}

void mainOpenGL::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_W) dz+=0.5f;
    if(e->key()==Qt::Key_S) dz-=0.5f;
    if(e->key()==Qt::Key_A) dx+=0.5f;
    if(e->key()==Qt::Key_D) dx-=0.5f;
}

