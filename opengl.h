#ifndef OPENGL_H
#define OPENGL_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QTimer>
#include <QMatrix4x4>
#include <QVector3D>

#include <QMouseEvent>
#include <QKeyEvent>
#include "Sprite.h"

class mainOpenGL : public QOpenGLWidget
{
public:
    mainOpenGL(QWidget *p);
protected:
    void	initializeGL();
    void	paintGL();
    void    resizeGL(int w,int h);

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);
private:
	QTimer *fps;
    QOpenGLContext *c1,*c2,*c3;
    Sprite *background,*test_3d,*ground;
    Sprite *box1,*box2,*box3,*box4,*box5,*box6;

    GLfloat dx,dy,dz,mx,my;

};

#endif // OPENGL_H
