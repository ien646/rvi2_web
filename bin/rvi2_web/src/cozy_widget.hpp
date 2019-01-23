#pragma once

#include <Wt/WGLWidget.h>
#include <vector>
#include <string>

#include <rvi/runtime.hpp>
#include <rvi/std_bindings.hpp>

class cozy_widget : public Wt::WGLWidget
{
private:
    rvi::runtime _runtime;
    int _client_id = -1;
    std::vector<float> _vx_buff;
    Wt::WGLWidget::Program _sh_program;
    Wt::WGLWidget::Buffer _vbo;
    bool _gl_initialized = false;

    const static std::string PX_SHADER_PATH;
    const static std::string VX_SHADER_PATH;

    void compile_shaders();

public:
    cozy_widget();
    void refresh_snapshot();

    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
    void updateGL() override {}
};