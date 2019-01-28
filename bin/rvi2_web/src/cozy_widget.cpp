#include "cozy_widget.hpp"

#include <fstream>
#include <sstream>
#include <Wt/WCssDecorationStyle.h>

const std::string cozy_widget::PX_SHADER_PATH = "shaders/pxshader.glsl";
const std::string cozy_widget::VX_SHADER_PATH = "shaders/vxshader.glsl";

cozy_widget::cozy_widget()
{
    resize(800, 600);
    decorationStyle().setBackgroundColor(Wt::WColor(100, 100, 100));

    _client_id = _runtime.create_client();
    _runtime.start_client(_client_id);
    _runtime.get_instance(_client_id).create_binding("hello_click", 
    [](rvi::client_instance& inst, const rvi::arglist_t& args) {
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
    });

    this->clicked().connect([&](const Wt::WMouseEvent& e)
    { 
        auto& inst = _runtime.get_instance(_client_id);
        Wt::Coordinates coords = e.widget();
        float x = static_cast<float>(coords.x) / this->width().value();
        float y = static_cast<float>(coords.y) / this->height().value();
        inst.user_click(rvi::vector2(x, y));
        refresh_snapshot();
        repaintGL(Wt::GLClientSideRenderer::RESIZE_GL);
        repaintGL(Wt::GLClientSideRenderer::PAINT_GL);
    });
}

void cozy_widget::compile_shaders()
{
    // Read shaders
    std::string vx_sh_src, px_sh_src;

    std::ifstream vx_fstream(VX_SHADER_PATH);
    {
        vx_fstream >> std::noskipws;
        std::stringstream vx_ss;
        vx_ss << vx_fstream.rdbuf();
        vx_sh_src = vx_ss.str();
    } vx_fstream.close();

    std::ifstream px_fstream(PX_SHADER_PATH);
    {
        px_fstream >> std::noskipws;
        std::stringstream px_ss;
        px_ss << px_fstream.rdbuf();
        px_sh_src = px_ss.str();
    } px_fstream.close();

    // Compile and link shaders
    _sh_program = createProgram();
    auto vxsh = createShader(VERTEX_SHADER);
    auto pxsh = createShader(FRAGMENT_SHADER);

    shaderSource(vxsh, vx_sh_src);
    shaderSource(pxsh, px_sh_src);    

    compileShader(vxsh);
    compileShader(pxsh);

    attachShader(_sh_program, vxsh);
    attachShader(_sh_program, pxsh);

    linkProgram(_sh_program);

    validateProgram(_sh_program);

    deleteShader(vxsh);
    deleteShader(pxsh);

    useProgram(_sh_program);
}

void cozy_widget::refresh_snapshot()
{
    if(!_gl_initialized)
    {
        return;
    }
    auto snapsh = _runtime.snapshot_full_relative(_client_id);
    _vx_buff.clear();
    for(auto& entry : snapsh)
    {
        for(auto& ln : entry.lines)
        {
            _vx_buff.push_back(ln.start.position.x);
            _vx_buff.push_back(ln.start.position.y);
            uint32_t srgba = ln.start.color.rgba();
            float scolor = *reinterpret_cast<float*>(&srgba);
            _vx_buff.push_back(scolor);

            _vx_buff.push_back(ln.end.position.x);
            _vx_buff.push_back(ln.end.position.y);
            uint32_t ergba = ln.start.color.rgba();
            float ecolor = *reinterpret_cast<float*>(&ergba);
            _vx_buff.push_back(ecolor);
        }
    }
    bindBuffer(ARRAY_BUFFER, _vbo);
    bufferDatafv(ARRAY_BUFFER, _vx_buff.begin(), _vx_buff.end(), DYNAMIC_DRAW);

    // vertex position data attr
    AttribLocation loc_vx_pos = getAttribLocation(_sh_program, "vertex_position");
    vertexAttribPointer(loc_vx_pos, 2, FLOAT, false, 12, 0);
    enableVertexAttribArray(loc_vx_pos);
    
    AttribLocation loc_vx_col = getAttribLocation(_sh_program, "vertex_color");
    vertexAttribPointer(loc_vx_col, 4, BYTE, false, 12, 8);
    enableVertexAttribArray(loc_vx_col);
}

void cozy_widget::initializeGL()
{
    compile_shaders();
    _vbo = createBuffer();
    _gl_initialized = true;
    refresh_snapshot();
}

void cozy_widget::resizeGL(int width, int height)
{
    this->viewport(0, 0, width, height);
}

void cozy_widget::paintGL()
{
    refresh_snapshot();
    clearColor(0.2, 0.2, 0.2, 0.5);
    useProgram(_sh_program);
    bindBuffer(ARRAY_BUFFER, _vbo);
    drawArrays(LINES, 0, _vx_buff.size() / 3);
}