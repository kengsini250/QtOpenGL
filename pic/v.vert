#ifdef GL_ES
precision highp int;
precision highp float;
#endif

uniform mat4 mvp_matrix;

attribute vec3 aPos;
attribute vec2 aTexCoord;

varying vec2 TexCoord;

void main(void)
{
    vec4 pos = vec4(aPos,1.0);
    gl_Position = mvp_matrix * pos;
    TexCoord = aTexCoord;
}
