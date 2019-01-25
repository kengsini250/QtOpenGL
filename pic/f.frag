#ifdef GL_ES
precision highp int;
precision highp float;
#endif


varying vec2 TexCoord;

uniform sampler2D ourTexture;

void main(void)
{
    gl_FragColor =texture2D(ourTexture,TexCoord);
}
