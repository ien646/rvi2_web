#include "dialog_page.hpp"

dialog_page::dialog_page(rvi::client_instance* ci, dialog_page* origin_page = nullptr)
    : _client_instance(ci)
    , _origin(origin_page)
{ }

void dialog_page::set_text(const std::string& text)
{
    _text = text;
}

void dialog_page::draw()
{
    auto ctx = _client_instance->get_context();

    ctx->select_frame("__DIALOG_PAGE");
    {
        ctx->clear_frame();
        ctx->clear_children();        
        rvi::standard::printw(*_client_instance, nullptr, _text);
    }
    ctx->release_frame();
}

void dialog_page::set_destination(int dest_idx, dialog_page&& dest)
{
    _destinations.emplace(dest_idx, std::move(dest));
}