#pragma once

#include <rvi/client_instance.hpp>
#include <rvi/standard_library.hpp>

#include <map>
#include <string>

using namespace rvi;

class dialog_page
{
private:
    dialog_page* _origin = nullptr;
    std::map<int, dialog_page> _destinations;

    rvi::client_instance* _client_instance;

    std::string _text;

public:
    dialog_page(rvi::client_instance* ci, dialog_page* origin_page = nullptr);

    void set_text(const std::string& text);

    dialog_page* get_destination(int dest_idx) { return &(_destinations[dest_idx]); }
    void set_destination(int dest_idx, dialog_page&& dest);

    void draw();
};