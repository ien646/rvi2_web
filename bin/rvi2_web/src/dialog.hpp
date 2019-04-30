#include "dialog_page.hpp"

struct misc_button_info
{
    rvi::transform2 transform;
    std::string text;
    int destination_index;
};

class dialog
{
private:
    dialog_page _root_page;
    dialog_page* _current_page;

    rvi::client_instance* _client_instance;

    bool _prev_button = false, _next_button = false;
    std::vector<misc_button_info> _misc_buttons;

    void draw_next_button();
    void draw_prev_button();
    void draw_misc_buttons();

public:
    dialog(rvi::client_instance* ci);

    void add_next_button();
    void add_prev_button();
    void add_misc_button(misc_button_info info);

    void draw();
};