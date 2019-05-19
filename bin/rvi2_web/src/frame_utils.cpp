#include "frame_utils.hpp"

// +-+-+-+-+-+-+-+-+-+-+
// frame_autorelease   +
// +-+-+-+-+-+-+-+-+-+-+

frame_autorelease::frame_autorelease(rvi::client_context* cctx) 
    : _cctx(cctx)
{ }

frame_autorelease::~frame_autorelease()
{
    for(int i = 0; i < _release_counter; ++i)
    {
        rvi::r_assert(_cctx->selected_frame()->has_parent(), "Attempt to release root frame!");
        _cctx->release_frame();
    }
    _release_counter = 0;
}

void frame_autorelease::select_frame(const std::string& name)
{
    _cctx->select_frame(name);
    ++_release_counter;
}

void frame_autorelease::select_frame(std::string&& name)
{
    _cctx->select_frame(std::move(name));
    ++_release_counter;
}

// +-+-+-+-+-+-+-+-+-+-+
// frame_save_context  +
// +-+-+-+-+-+-+-+-+-+-+

frame_save_context::frame_save_context(rvi::client_context* cctx)
    : _cctx(cctx)
{ 
    _saved_frame = _cctx->selected_frame();
}

frame_save_context::frame_save_context(rvi::client_context* cctx, rvi::frame* fptr)
    : _cctx(cctx)
    , _saved_frame(_cctx->selected_frame())
{ }

frame_save_context::~frame_save_context()
{
    _cctx->select_frame(_saved_frame);
}