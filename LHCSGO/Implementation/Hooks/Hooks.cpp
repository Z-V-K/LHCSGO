#include "pch.h"
#include "Hooks.h"

#include "../../ValveSDK/ValveSDK.h"
#include "Direct3DDevice/Direct3DDevice.h"
#include "BaseClient//BaseClient.h"
#include "GameEventManager/GameEventManager.h"

void Hooks::Initialize()
{
    direct3d_hook.Setup(g_device);
    direct3d_hook.HookIndex((int) HookIndex::Present, Direct3DDevice::hkPresent);

    baseclient_hook.Setup(g_baseclient);
    baseclient_hook.HookIndex((int) HookIndex::FrameStageNotify, BaseClient::hk_FrameStageNotify);

    gameeventmanager_hook.Setup(g_eventmanager);
    gameeventmanager_hook.HookIndex((int) HookIndex::FireEvent, GameEventManager::hk_FireEvent);
}

void Hooks::Remove()
{
    direct3d_hook.UnhookAll();
}

