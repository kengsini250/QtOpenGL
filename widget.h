#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "opengl.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    mainOpenGL *opengl;
};

#endif // WIDGET_H
