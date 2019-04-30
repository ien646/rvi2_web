#include "dialog.hpp"

#include <rvi/runtime.hpp>

dialog::dialog(rvi::client_instance* ci)
    : _client_instance(ci)
    , _root_page(ci)
{ }

void dialog::add_next_button()
{
    _next_button = true;
}

void dialog::add_prev_button()
{
    _prev_button = true;
}

void dialog::add_misc_button(misc_button_info info)
{
    _misc_buttons.push_back(info);
}

void dialog::draw()
{
    auto ctx = _client_instance->get_context();
    ctx->select_frame("__DIALOG");
    {
        ctx->clear_frame();
        ctx->clear_children();

        if(_next_button) 
            { draw_next_button(); }
        if(_prev_button) 
            { draw_prev_button(); }
        if(!_misc_buttons.empty()) 
            { draw_misc_buttons(); }

        _current_page->draw();
    }
    ctx->release_frame();
}

void dialog::draw_next_button()
{
    auto ctx = _client_instance->get_context();
    ctx->select_frame("__NEXT_BUTTON");
    {
        const rvi::vector2 position(0.90F, 0.05F);
        const rvi::vector2 scale(0.05F, 0.05F);
        const std::string text = "N";

        ctx->set_position(position);
        ctx->set_scale(scale);

        rvi::standard::print_settings p_settings;
        p_settings.font_size = vector2(0.95F, 0.95F);
        p_settings.font_margin = vector2(0.025F, 0.025F);

        rvi::standard::print(*_client_instance, ctx->selected_frame(), text, p_settings);        
        rvi::standard::box_border(*(_client_instance->get_context()));

        _client_instance->set_current_frame_clickable("__NEXT_BUTTON_CLICK__");

        _client_instance->get_runtime()->delete_binding("__NEXT_BUTTON_CLICK__");
        _client_instance->get_runtime()->create_binding("__NEXT_BUTTON_CLICK__", 
            [&](client_instance* c_inst, frame* calling_fptr)
            {
                dialog_page* dest = _current_page->get_destination(0);
                _current_page = dest;
                draw();
            }
        );
    }
    ctx->release_frame();
}

void dialog::draw_prev_button()
{
    auto ctx = _client_instance->get_context();
    ctx->select_frame("__PREV_BUTTON");
    {
        const rvi::vector2 position(0.05F, 0.05F);
        const rvi::vector2 scale(0.05F, 0.05F);
        const std::string text = "P";

        ctx->set_position(position);
        ctx->set_scale(scale);

        rvi::standard::print_settings p_settings;
        p_settings.font_size = vector2(0.95F, 0.95F);
        p_settings.font_margin = vector2(0.025F, 0.025F);

        rvi::standard::print(*_client_instance, ctx->selected_frame(), text, p_settings);
        rvi::standard::box_border(*(_client_instance->get_context()));

        _client_instance->set_current_frame_clickable("__PREV_BUTTON_CLICK__");

        _client_instance->get_runtime()->delete_binding("__PREV_BUTTON_CLICK__");
        _client_instance->get_runtime()->create_binding("__PREV_BUTTON_CLICK__", 
            [&](client_instance* c_inst, frame* calling_fptr)
            {
                dialog_page* dest = _current_page->get_destination(-1);
                _current_page = dest;
                draw();
            }
        );
    }
    ctx->release_frame();
}

void dialog::draw_misc_buttons()
{
    //...
}