#pragma once

#include <Wt/WGLWidget.h>
#include <vector>
#include <string>

#include <rvi/runtime.hpp>
#include <rvi/std_bindings.hpp>

static void hello_click(rvi::client_instance& inst, const rvi::arglist_t&)
{
    // Save current selected frame
    auto& ctx = inst.context;
    rvi::frame* save_ptr = ctx.selected_frame();

    // Return to root frame
    ctx.select_frame("hello_friend");
    ctx.clear_frame();
    ctx.clear_children();
    ctx.set_position(rvi::vector2(0.10f, 0.15f));
    rvi::std_bindings::printx(inst, ctx.selected_frame()->name() , "+-+-+ HELLO FRIEND +-+-+");
    ctx.select_frame(save_ptr);
}

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

    void initializeGL() override
    {
        compile_shaders();
        _vbo = createBuffer();
        _gl_initialized = true;
        refresh_snapshot();
    }

    void resizeGL(int width, int height) override
    {
        std::cout << "resizeGL()" << std::endl;
        this->viewport(0, 0, width, height);
    }

    void paintGL() override
    {
        refresh_snapshot();
        std::cout << "paintGL()" << std::endl;
		clearColor(0.2, 0.2, 0.2, 0.5);
        useProgram(_sh_program);
        bindBuffer(ARRAY_BUFFER, _vbo);
        drawArrays(LINES, 0, _vx_buff.size() / 3);
    }

    void updateGL() override
    {
        std::cout << "updateGL()" << std::endl;
    }
};