#include <QApplication>
#include <QSurfaceFormat>
#include <QDebug>

#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);
    format.setVersion(3,0);
    //qDebug()<<"OpenGL major: "<<format.version().first;
    //qDebug()<<"OpenGL minor: "<<format.version().second ;

    Widget w;
    w.show();

    return a.exec();
}
