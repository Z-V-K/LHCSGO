#pragma once

class Context
{
public:
    LPVOID game_module;
};

extern std::shared_ptr<Context> g_ctx;