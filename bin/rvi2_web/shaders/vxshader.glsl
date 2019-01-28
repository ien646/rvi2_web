precision highp float;

attribute vec2 vertex_position;
attribute vec4 vertex_color;

varying vec4 vxColor;

void main()
{
    float x = ((vertex_position.x) * 2.0) - 1.0;
    float y = ((vertex_position.y) * 2.0) - 1.0;
    gl_Position = vec4(x, y, 1.0, 1.0);
    vxColor = vec4(
        abs(vertex_color.a),
        abs(vertex_color.b), 
        abs(vertex_color.g), 
        abs(vertex_color.r)
    );
}