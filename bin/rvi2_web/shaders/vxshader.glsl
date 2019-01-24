precision mediump float;

attribute vec3 vertex_position;

varying vec4 vxColor;

vec4 DecodeRGBA (float v) 
{
    float r = v / 100.0 / 100.0 / 100.0;
    float g = mod(v / 100.0 / 100.0, 100.0);
    float b = mod(v / 100.0, 100.0);
    float a = mod(v, 100.0);
    return vec4(r, g, b, a);
}

void main()
{
    float vertex_color = vertex_position.z;
    float x = ((vertex_position.x) * 2.0) - 1.0;
    float y = ((vertex_position.y) * 2.0) - 1.0;
    gl_Position = vec4(x, y, 1.0, 1.0);
    vxColor = DecodeRGBA(vertex_color);
}