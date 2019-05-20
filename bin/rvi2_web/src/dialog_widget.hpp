#pragma once

#include <rvi/client_instance.hpp>
#include <rvi/client_context.hpp>
#include <rvi/frame.hpp>
#include <rvi/assert.hpp>
#include <rvi/standard_library.hpp>

#include <string>
#include <unordered_map>

#include "cozy_widget.hpp"
#include "frame_utils.hpp"

struct dialog_page
{
    std::unordered_map<std::string, sol::function> custom_actions;
    std::unordered_map<std::string, std::string> redirections;
    std::string text;
    bool next = false, previous = false;
};

class dialog_widget : public cozy_widget
{
private:
    std::unordered_map<std::string, dialog_page> _dialog_pages;
    std::string _current_page = "";

public:
    dialog_widget();

    rvi::client_context* get_client_context();
    dialog_page& current_page();

    void refresh_dialog();

private:
    void init_lua();
    void init_bindings();

    void click_next();
    void click_prev();
};