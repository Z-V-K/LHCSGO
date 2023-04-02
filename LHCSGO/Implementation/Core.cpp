#include "pch.h"
#include "Core.h"
#include "../Framework/Context.h"
#include "../ValveSDK/ValveSDK.h"
#include "Bypass/RetAddrCheckBypass.h"
#include "Hooks/Hooks.h"
#include "Features/Features.h"
#include "ValveSDK/NetvarManager.h"
#include "ValveSDK/Classes/BaseEntity.h"

std::shared_ptr<Core> g_core = std::make_shared<Core>();

void Core::Initialize(LPVOID base)
{
    g_ctx->game_module = base;

    ValveSDK::Initialize();
    NetvarManager::Initialize();
   
    RetAddrCheckBypass::Initialize();
    Hooks::Initialize();

    Features::Initialize();
}
