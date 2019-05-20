#pragma once

#include <rvi/client_context.hpp>
#include <rvi/assert.hpp>

#include <stack>

class frame_autorelease
{
private:
    int _release_counter = 0;
    rvi::client_context* _cctx = nullptr;

public:
    frame_autorelease(rvi::client_context* cctx);
    frame_autorelease(rvi::client_context* cctx, rvi::frame* save_context);
    virtual ~frame_autorelease();

    void select_frame(const std::string& name);
    void select_frame(std::string&& name);
};

class frame_save_context
{
private:
    rvi::frame* _saved_frame;
    rvi::client_context* _cctx = nullptr;

public:
    frame_save_context(rvi::client_context* cctx);
    frame_save_context(rvi::client_context* cctx, rvi::frame* fptr);
    virtual ~frame_save_context();
};