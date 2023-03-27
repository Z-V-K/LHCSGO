#include "pch.h"
#include "Core.h"
#include "../Framework/Context.h"

std::shared_ptr<Core> g_core = std::make_shared<Core>();

void Core::Initialize(LPVOID base)
{
    g_ctx->game_module = base;
    hooks = Hooks{ };
}
