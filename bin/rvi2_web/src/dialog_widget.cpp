#include "dialog_widget.hpp"

dialog_widget::dialog_widget()	
{
    init_lua();
    init_bindings();
    cozy_widget::init();
}

void dialog_widget::init_bindings()
{
    _runtime.create_binding("__dialog_click_next__", 
        [&](rvi::client_instance& cinst, rvi::frame* fptr)
        {
            click_next();
        }
    );

    _runtime.create_binding("__dialog_click_prev__", 
        [&](rvi::client_instance& cinst, rvi::frame* fptr)
        {
            click_prev();
        }
    );
}

void dialog_widget::init_lua()
{
    auto* lua = get_client_instance()->get_lua_context()->get_lua_state();

    sol::table dialog_table = lua->create_table("dialog");

    dialog_table.set_function("refresh", [&]{ refresh_dialog(); });

    dialog_table.set_function("declare_page", 
        [&](const std::string& dialog_name)
        {
            _dialog_pages.emplace(dialog_name, dialog_page());
        }
    );

    dialog_table.set_function("set_page_text", 
        [&](const std::string& dialog_name, const std::string& text)
        {
            rvi::debug_assert(
                _dialog_pages.count(dialog_name) > 0, 
                "dialog_page not found"
            );

            _dialog_pages.at(dialog_name).text = text;
        }
    );

    dialog_table.set_function("set_next_page",
        [&](const std::string& dialog_name, const std::string& next)
        {
            rvi::debug_assert(
                _dialog_pages.count(dialog_name) > 0, 
                "dialog_page not found"
            );

            auto& dpage = _dialog_pages.at(dialog_name);
            dpage.redirections.emplace("__NEXT__", next);
            dpage.next = true;
        }
    );

    dialog_table.set_function("set_prev_page",
        [&](const std::string& dialog_name, const std::string& prev)
        {
            rvi::debug_assert(
                _dialog_pages.count(dialog_name) > 0, 
                "dialog_page not found"
            );

            auto& dpage = _dialog_pages.at(dialog_name);
            dpage.redirections.emplace("__PREV__", prev);
            dpage.previous = true;
        }
    );

    dialog_table.set_function("goto_page", [&](const std::string& dialog_name)
    {
        rvi::debug_assert(
                _dialog_pages.count(dialog_name) > 0, 
                "dialog_page not found"
        );

        _current_page = dialog_name;
    });

    dialog_table.set_function("set_next_custom_function", 
        [&](const std::string& dialog_name, sol::function func)
        {
            rvi::debug_assert(
                _dialog_pages.count(dialog_name) > 0, 
                "dialog_page not found"
            );

            auto& dpage = _dialog_pages.at(dialog_name);
            dpage.custom_actions.emplace("__NEXT__", func);
        }
    );

    dialog_table.set_function("set_prev_custom_function",
    [&](const std::string& dialog_name, sol::function func)
        {
            rvi::debug_assert(
                _dialog_pages.count(dialog_name) > 0, 
                "dialog_page not found"
            );

            auto& dpage = _dialog_pages.at(dialog_name);
            dpage.custom_actions.emplace("__PREV__", func);
        }
    );
}

void dialog_widget::click_next()
{
    _current_page = current_page().redirections.at("__NEXT__");
    refresh_dialog();
}

void dialog_widget::click_prev()
{
    _current_page = current_page().redirections.at("__PREV__");
    refresh_dialog();
}

rvi::client_context* dialog_widget::get_client_context()
{
    return get_client_instance()->get_context();
}

dialog_page& dialog_widget::current_page()
{
    rvi::debug_assert(
            _dialog_pages.count(_current_page) > 0, 
            "dialog_page not found"
    );

    return _dialog_pages.at(_current_page);
}

void dialog_widget::refresh_dialog()
{
    auto* cctx = get_client_context();
    frame_checkpoint checkpoint(cctx);
    cctx->select_root();
    cctx->select_frame("__DIALOG_ROOT__");

    cctx->clear_frame();
    cctx->clear_children();

    rvi::standard::print_settings psettins;
    psettins.font_margin = rvi::vector2(0.1F, 0.1F);

    rvi::standard::printw(
        get_client_instance(), 
        cctx->selected_frame(), 
        current_page().text,
        psettins
    );

    if(current_page().next)
    {
        frame_autorelease ckpt(cctx);
        ckpt.select_frame("__BUTTON_NEXT__");
        cctx->set_scale(rvi::vector2(0.05F, 0.05F));
        cctx->set_position(rvi::vector2(0.90F, 0.05F));
        cctx->draw_line(rvi::vector2(0.0F, 1.0F), rvi::vector2(1.0F, 0.5F));
        cctx->draw_line(rvi::vector2(0.0F, 0.0F), rvi::vector2(1.0F, 0.5F));
        cctx->draw_line(rvi::vector2(0.0F, 0.0F), rvi::vector2(0.0F, 1.0F));
        cctx->draw_line(rvi::vector2(0.0F, 0.8F), rvi::vector2(1.0F, 0.5F));
        get_client_instance()->set_current_frame_clickable("__dialog_click_next__");
    }
    else
    {
        _runtime.delete_binding("__dialog_click_next__");
    }    

    if(current_page().previous)
    {
        frame_autorelease ckpt(cctx);
        ckpt.select_frame("__BUTTON_PREV__");
        cctx->set_scale(rvi::vector2(0.05F, 0.05F));
        cctx->set_position(rvi::vector2(0.90F, 0.05F));
        cctx->draw_line(rvi::vector2(1.0F, 1.0F), rvi::vector2(0.0F, 0.5F));
        cctx->draw_line(rvi::vector2(1.0F, 0.0F), rvi::vector2(0.0F, 0.5F));
        cctx->draw_line(rvi::vector2(1.0F, 0.0F), rvi::vector2(1.0F, 1.0F));
        cctx->draw_line(rvi::vector2(1.0F, 0.8F), rvi::vector2(0.0F, 0.5F));
        get_client_instance()->set_current_frame_clickable("__dialog_click_prev__");
    }
    else
    {
        _runtime.delete_binding("__dialog_click_prev__");
    }
}