#ifndef OPENGL_H
#define OPENGL_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QTimer>


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

    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
	QTimer *fps;

    Sprite *background,*test_3d,*ground;
};

#endif // OPENGL_H
