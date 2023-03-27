#include "pch.h"
#include "Hooks.h"

#include "../../ValveSDK/ValveSDK.h"
#include "Direct3DDevice/Direct3DDevice.h"

Hooks::Hooks()
{
    direct3d_hook.Setup(g_sdk->game_device);

    direct3d_hook.HookIndex((int) HookIndex::EndScene, Direct3DDevice::hkEndScene);
    direct3d_hook.HookIndex((int) HookIndex::Reset, Direct3DDevice::hkReset);
}

Hooks::~Hooks()
{
    direct3d_hook.UnhookAll();
}

