#include "pch.h"
#include "Hooks.h"

#include "../../ValveSDK/ValveSDK.h"
#include "Direct3DDevice/Direct3DDevice.h"

void Hooks::Initialize()
{
    direct3d_hook.setup(ValveSDK::game_device);
    direct3d_hook.HookIndex((int) HookIndex::Present, Direct3DDevice::hkPresent);
}

void Hooks::Remove()
{
    // direct3d_hook.Unhook();
}

