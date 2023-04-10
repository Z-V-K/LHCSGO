#include "pch.h"
#include "GameEventManager.h"

#include "Implementation/CallbackManager/CallbackManager.h"
#include "Implementation/Hooks/Hooks.h"
#include "ValveSDK/Classes/BasePlayer.h"

bool __fastcall GameEventManager::hk_FireEvent(void* thisPtr, void* edx, IGameEvent* event, bool bDontBroadcast)
{
    CallbackManager::Trigger(OnFireEvent, event);

    return Hooks::gameeventmanager_hook.GetOg<decltype(&hk_FireEvent)>((int) HookIndex::FireEvent)(thisPtr, edx, event, bDontBroadcast);
}

