#pragma once

class Context
{
public:
    LPVOID game_module;
    bool unload = false;
};

extern std::shared_ptr<Context> g_ctx;
