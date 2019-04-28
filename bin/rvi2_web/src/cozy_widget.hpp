#pragma once

#include <Wt/WGLWidget.h>
#include <Wt/WJavaScript.h>
#include <vector>
#include <string>

#include <rvi/runtime.hpp>
#include <rvi/standard_library.hpp>


class cozy_widget : public Wt::WGLWidget
{
private:
    rvi::runtime _runtime;
    rvi::rvi_cid_t _client_id = 0u;

    rvi::line_container _vx_data;

    Wt::WGLWidget::Buffer _vbo_pos;
    Wt::WGLWidget::Buffer _vbo_col;

    Wt::WGLWidget::Program _sh_program;

    bool _gl_initialized = false;

    const static std::string PX_SHADER_PATH;
    const static std::string VX_SHADER_PATH;

    void compile_shaders();
    
    Wt::JSignal<int, int> _resize_signal;

public:
    cozy_widget();
    void refresh_snapshot();

    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
    void updateGL() override {}

    void resize_signal(int w, int h);
};