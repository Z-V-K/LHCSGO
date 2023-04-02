#pragma once
#include "ValveSDK/Interfaces/IGameEvent.h"

namespace GameEventManager
{
    bool __fastcall hk_FireEvent(void* thisPtr, void* edx, IGameEvent* event, bool bDontBroadcast = false);
};
