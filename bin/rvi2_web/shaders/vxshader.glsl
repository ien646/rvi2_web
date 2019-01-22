precision mediump float;
attribute vec3 vertex;
varying vec4 vxColor;

void main()
{
    float x = ((vertex.x) * 2.0) - 1.0;
    float y = ((vertex.y) * 2.0) - 1.0;
    gl_Position = vec4(x, y, 1.0, 1.0);
    vxColor = vec4(0.5, 1.0, 0.5, 1.0);
}