#pragma once

#include <Wt/WGLWidget.h>
#include <vector>
#include <string>

#include <rvi/runtime.hpp>

class GL : public Wt::WGLWidget
{
private:
    rvi::runtime _runtime;
    int _client_id = -1;
    std::vector<float> _vx_buff;    
    Wt::WGLWidget::Program _sh_program;
    Wt::WGLWidget::Buffer _vbo;
public:
    GL()
    {
        setHeight(500);
        setWidth(500);
        _client_id = _runtime.create_client();
        _runtime.start_client(_client_id);
    }

    void refresh_snap()
    {
        std::cout << "refresh_snap()" << std::endl;
        auto snapsh = _runtime.snapshot_full_relative(_client_id);
        for(auto& entry : snapsh)
        {
            for(auto& ln : entry.lines)
            {
                _vx_buff.push_back(ln.start.position.x);
                _vx_buff.push_back(ln.start.position.y);
                uint32_t sc = ln.start.color.rgba();
                float scolor = *reinterpret_cast<float*>(&sc);
                _vx_buff.push_back(scolor);

                _vx_buff.push_back(ln.end.position.x);
                _vx_buff.push_back(ln.end.position.y);
                uint32_t ec = ln.end.color.rgba();
                float ecolor = *reinterpret_cast<float*>(&ec);
                _vx_buff.push_back(scolor);
            }
        }
    }

    void initializeGL() override
    {
        std::cout << "initializeGL()" << std::endl;
        refresh_snap();
        std::stringstream vx_shader, px_shader;
        px_shader
            << "precision mediump float;"<< std::endl
            << "varying vec4 vxColor;" << std::endl
            << "void main()"<< std::endl
            << "{"<< std::endl
            << "    vec4 fcol = vec4(vxColor.x, vxColor.y, vxColor.z, vxColor.w);"<< std::endl
            << "    gl_FragColor = fcol;"<< std::endl
            << "}"<< std::endl;
        
        vx_shader
            << "precision mediump float;" << std::endl
            << "attribute vec3 vertex;"<< std::endl
            << "varying vec4 vxColor;"<< std::endl
            << "void main()"<< std::endl
            << "{"<< std::endl
            << "    float x = ((vertex.x) * 2.0) - 1.0;"<< std::endl
            << "    float y = ((vertex.y) * 2.0) - 1.0;"<< std::endl
            << "    gl_Position = vec4(x, y, 1.0, 1.0);"<< std::endl
            << "    vxColor = vec4(0.5, 1.0, 0.5, 1.0);"<< std::endl
            << "}"<< std::endl;

        _sh_program = createProgram();
        auto vxsh = createShader(VERTEX_SHADER);
        auto pxsh = createShader(FRAGMENT_SHADER);
        shaderSource(vxsh, vx_shader.str());
        shaderSource(pxsh, px_shader.str());
        attachShader(_sh_program, vxsh);
        attachShader(_sh_program, pxsh);
        compileShader(vxsh);
        compileShader(pxsh);
        linkProgram(_sh_program);
        deleteShader(vxsh);
        deleteShader(pxsh);        
        _vbo = createBuffer();
        bindBuffer(ARRAY_BUFFER, _vbo);
		vertexAttribPointer(AttribLocation(0), 3, FLOAT, false, 0, 0);
        enableVertexAttribArray(AttribLocation(0));
        bindAttribLocation(_sh_program, 0, "vertex");
        bufferDatafv(ARRAY_BUFFER, _vx_buff.begin(), _vx_buff.end(), DYNAMIC_DRAW);
    }

    void resizeGL(int width, int height) override
    {
        std::cout << "resizeGL()" << std::endl;
        this->viewport(0, 0, width, height);
    }

    void paintGL() override
    {
        std::cout << "paintGL()" << std::endl;
		clearColor(0.2, 0.2, 0.2, 0.5);
        useProgram(_sh_program);
        bindBuffer(ARRAY_BUFFER, _vbo);
        enableVertexAttribArray(AttribLocation(0));
        drawArrays(LINES, 0, _vx_buff.size() / 3);
    }

    void updateGL() override
    {
        std::cout << "updateGL()" << std::endl;
    }
};