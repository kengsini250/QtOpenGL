#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(1600,900);
    opengl=new mainOpenGL(this);
}

Widget::~Widget()
{

}
