#ifndef SPRITE_H
#define SPRITE_H

#include<QOpenGLBuffer>
#include<QOpenGLShaderProgram>
#include<QOpenGLTexture>
#include <QOpenGLFunctions>

#include <QMatrix4x4>
#include <QVector2D>
#include <QVector3D>

class Sprite : protected QOpenGLFunctions
{	
public:
    Sprite(QString pic,float _x,float _y,float _angle);//background
    Sprite(QString pic,float _x,float _y,float _z,float _angle_x,float _angle_y,float _angle_z);//box
    Sprite(QString pic);//ground
    ~Sprite();
    void Draw();
    void Draw_Ground(QMatrix4x4 m);
    void Draw_Box(QMatrix4x4 m);

    void setSpeed(float s){angle=s;}
private:

    void Init_Vbo_Ebo();
    void Init_Vbo_Ebo_3D();
    void Init_Shader();
    void Init_Texture();

    void Init_Matrix();
    void Init_Matrix_Ground();
    void Init_Matrix_Box();

    QOpenGLBuffer vbo, ebo;
    QOpenGLShaderProgram shader;
    QOpenGLTexture *texture;

    QMatrix4x4 matrix;

    float x1, y1, x2, y2,z1,z2;
    float angle;
    float angle_x,angle_y,angle_z;
    float dx,dy,dz;
    int flag;
};

#endif
