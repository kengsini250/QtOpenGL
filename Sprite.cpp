 #include "Sprite.h"
#include <QDebug>

#define WIN_X 1600.0f
#define WIN_Y 900.0f

static QString vert = ":/pic/v.vert";
static QString frag = ":/pic/f.frag";


struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

static GLushort rule[]={
    0,1,2,
    2,3,0
};

static VertexData vertices[] = {
    {QVector3D(0.0f, 0.0f,0.0f),QVector2D(0.0f, 0.0f)},
    {QVector3D(0.0f, 1.0f,0.0f),QVector2D(0.0f, 1.0f)},
    {QVector3D(1.0f, 1.0f,0.0f),QVector2D(1.0f, 1.0f)},
    {QVector3D(1.0f, 0.0f,0.0f),QVector2D(1.0f, 0.0f)}
};

static GLfloat box_v[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

//-----------------------------------------background---------------------------------------------
Sprite::Sprite(QString pic, float _x, float _y,float _angle)
    :vbo(QOpenGLBuffer::VertexBuffer)
  ,ebo(QOpenGLBuffer::IndexBuffer)
  ,x1(_x),y1(_y)
  ,x2(QImage(pic).width())
  ,y2(QImage(pic).height())
  ,z1(0) ,z2(0)
  ,angle(_angle)
  ,angle_x(0),angle_y(0),angle_z(0)
  ,dx(0),dy(0),dz(0)
  ,flag(0)
{
    initializeOpenGLFunctions();
    texture = new QOpenGLTexture(QImage(pic));
    Init_Vbo_Ebo();
    Init_Shader();
    Init_Texture();
    Init_Matrix();
}
//-----------------------------------------background----------------------------------------------


//-----------------------------------------box----------------------------------------------
Sprite::Sprite(QString pic, float _x, float _y,float _z,float _angle_x,float _angle_y,float _angle_z)    :
    vbo(QOpenGLBuffer::VertexBuffer)
  ,ebo(QOpenGLBuffer::IndexBuffer)
  ,x1(_x),y1(_y)
  ,x2(QImage(pic).width())
  ,y2(QImage(pic).height())
  ,z1(_z),z2(0)
  ,angle(0)
  ,angle_x(_angle_x),angle_y(_angle_y),angle_z(_angle_z)
   ,dx(0),dy(0),dz(0)
  ,flag(1)
{
    initializeOpenGLFunctions();
    texture = new QOpenGLTexture(QImage(pic).mirrored());
    Init_Vbo_Ebo_3D();
    Init_Shader();
    Init_Texture();
    Init_Matrix_Box();
}
//-----------------------------------------box----------------------------------------------


//-----------------------------------------Ground----------------------------------------------
Sprite::Sprite(QString pic) :
    vbo(QOpenGLBuffer::VertexBuffer)
  ,ebo(QOpenGLBuffer::IndexBuffer)
  ,x1(0),y1(0)
  ,x2(QImage(pic).width())
  ,y2(QImage(pic).height())
  ,z1(0),z2(0)
  ,angle(0)
  ,angle_x(0),angle_y(0),angle_z(0)
   ,dx(0),dy(0),dz(0)
  ,flag(1)
{
    initializeOpenGLFunctions();
    texture = new QOpenGLTexture(QImage(pic).mirrored());
    Init_Vbo_Ebo();
    Init_Shader();
    Init_Texture();
    Init_Matrix_Ground();
}
//-----------------------------------------Ground----------------------------------------------


Sprite::~Sprite()
{
    vbo.destroy();
    if(flag==0)
        ebo.destroy();
}

void Sprite::Init_Vbo_Ebo()
{
    vbo.create();
    ebo.create();

    vbo.bind();
    vbo.allocate(vertices,4*sizeof(VertexData));

    ebo.bind();
    ebo.allocate(rule,sizeof(rule));
}

void Sprite::Init_Vbo_Ebo_3D()
{
    vbo.create();
    vbo.bind();
    vbo.allocate(box_v,sizeof(box_v));
}

void Sprite::Init_Shader()
{
    if(!shader.addShaderFromSourceFile(QOpenGLShader::Vertex,vert))
        qDebug()<<"Vertex Shader wrong !!!";
    if(!shader.addShaderFromSourceFile(QOpenGLShader::Fragment,frag))
        qDebug()<<"Fragment Shader wrong !!!";
    if(!shader.link())
        qDebug()<<"link wrong !!!";
    if(!shader.bind())
        qDebug()<<"bind wrong !!!";
}

void Sprite::Init_Texture()
{
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void Sprite::Init_Matrix()
{
    matrix.ortho(QRect(0,0,WIN_X,WIN_Y));
    matrix.translate(QVector3D(x1,y1,-1.0f));
    matrix.translate(QVector3D(x2/2,y2/2,0.0f));
    matrix.rotate(angle,0.0f,0.0f,1.0f);
    matrix.translate(QVector3D(-x2/2,-y2/2,0.0f));
    matrix.scale(QVector3D(x2 ,y2,0.0f));
}

void Sprite::Init_Matrix_Ground()
{
    matrix.scale(8.0f,4.0f,0.7f);
    matrix.translate(QVector3D(-0.5,-0.6f,-7.0f));
    matrix.rotate(-70.0f,1.0f,0.0f,0.0f);
}

void Sprite::Init_Matrix_Box()
{
    matrix.translate(QVector3D(x1,y1,-z1));
    matrix.rotate(angle_x,1.0f,0.0f,0.0f);//X
    matrix.rotate(angle_y,0.0f,1.0f,0.0f);//Y
    matrix.rotate(angle_z,0.0f,0.0f,1.0f);//Z
}

void Sprite::Draw()
{
    texture->bind();

    shader.setUniformValue("mvp_matrix",matrix);
    shader.setUniformValue("ourTexture", 0);

    vbo.bind();
    ebo.bind();

    int vertexLocation = shader.attributeLocation("aPos");
    shader.enableAttributeArray(vertexLocation);
    shader.setAttributeBuffer(vertexLocation,GL_FLOAT,0,3,sizeof(VertexData));

    int textureLocation = shader.attributeLocation("aTexCoord");
    shader.enableAttributeArray(textureLocation);
    shader.setAttributeBuffer(textureLocation,GL_FLOAT,0,2,sizeof(VertexData));

    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,nullptr);
}

void Sprite::Draw_Ground(QMatrix4x4 m)
{
    texture->bind();

    shader.setUniformValue("mvp_matrix",m*matrix);
    shader.setUniformValue("ourTexture", 0);

    vbo.bind();
    ebo.bind();

    int vertexLocation = shader.attributeLocation("aPos");
    shader.enableAttributeArray(vertexLocation);
    shader.setAttributeBuffer(vertexLocation,GL_FLOAT,0,3,sizeof(VertexData));

    int textureLocation = shader.attributeLocation("aTexCoord");
    shader.enableAttributeArray(textureLocation);
    shader.setAttributeBuffer(textureLocation,GL_FLOAT,0,2,sizeof(VertexData));

    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,nullptr);
}

void Sprite::Draw_Box(QMatrix4x4 m)
{
//    matrix.rotate(angle,1.0f,0.0f,0.0f);//X
//    matrix.rotate(angle-0.3f,0.0f,1.0f,0.0f);//Y
//    matrix.rotate(angle+0.2f,0.0f,0.0f,1.0f);//Z

    texture->bind();

    shader.setUniformValue("mvp_matrix",m*matrix);
    shader.setUniformValue("ourTexture", 0);

    vbo.bind();

    int vertexLocation = shader.attributeLocation("aPos");
    shader.enableAttributeArray(vertexLocation);
    shader.setAttributeBuffer(vertexLocation,GL_FLOAT,0,3,5*sizeof(GLfloat));

    int textureLocation = shader.attributeLocation("aTexCoord");
    shader.enableAttributeArray(textureLocation);
    shader.setAttributeBuffer(textureLocation,GL_FLOAT,3*sizeof(GLfloat),2,5*sizeof(GLfloat));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    dx=0;dy=0;dz=0;
}
