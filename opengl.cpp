#include "opengl.h"
#include <QOpenGLFunctions>
#include <QDebug>

static QString test_pic =":/pic/box.png";
static QString background_pic =":/pic/sky.jpg";
static QString ground_pic =":/pic/ground.jpg";

mainOpenGL::mainOpenGL(QWidget *p):QOpenGLWidget(p)
{
    setGeometry(0,0,1600,900);
    show();
    setFocus();
    fps = new QTimer(this);
    connect(fps, SIGNAL(timeout()), this, SLOT(update()));
    fps->start(16);//FPS 60
    //fps->start(500);//FPS 60
}

void mainOpenGL::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->initializeOpenGLFunctions();
    f->glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    f->glEnable(GL_DEPTH_TEST);
    f->glDepthFunc(GL_LEQUAL);
    f->glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    test_3d = new Sprite(test_pic ,-2.5f,-0.5f,7.5f,0.0f,0.0f,0.0f);
    background = new Sprite(background_pic,0,0,0);
    ground = new Sprite(ground_pic);
}

void mainOpenGL::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    f->glClearColor(0.5f, 0.5f, 0.5f, 0.0f);

    background->Draw();
    ground ->Draw_Ground();
    test_3d->Draw_3D();
}

void mainOpenGL::resizeGL(int w,int h)
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glViewport(0,0,w,h);

}

void mainOpenGL::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"mouse : "<<event->globalPos() ;
    qDebug()<<"mouse : "<<event->pos();
}

void mainOpenGL::keyPressEvent(QKeyEvent *event)
{
   if(event->key()==Qt::Key_W){
       test_3d->GoFront(0.5f);
   }
   if(event->key()==Qt::Key_A){
       test_3d->GoLeft(0.5f);
   }
   if(event->key()==Qt::Key_S){
       test_3d->GoBack(0.5f);
   }
   if(event->key()==Qt::Key_D){
       test_3d->GoRight(0.5f);
   }
}

