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

    float _aspect_ratio_x = 1.0F;
    float _aspect_ratio_y = 1.0F;

    rvi::line_container _vx_data;

    Wt::WGLWidget::Buffer _vbo_pos;
    Wt::WGLWidget::Buffer _vbo_col;

    Wt::WGLWidget::Program _sh_program;

    bool _gl_initialized = false;

    const static std::string PX_SHADER_PATH;
    const static std::string VX_SHADER_PATH;

    void compile_shaders();
    
    Wt::JSignal<int, int> _resize_signal;

    void init_resize_timer(int pollrate_ms);

public:
    cozy_widget();
    void refresh_snapshot();

    void init_lua_methods();

    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
    void updateGL() override {}

    void resize_signal(int w, int h);
    void recenter_widget(int fw, int fh);

    rvi::client_instance* get_client_instance() { return &(_runtime.get_instance(_client_id)); }
};