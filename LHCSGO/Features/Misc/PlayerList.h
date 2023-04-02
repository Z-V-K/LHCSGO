#pragma once
#include "ValveSDK/Interfaces/IGameEvent.h"

namespace PlayerList
{
    void Initialize();

    void OnUpdate();
    void OnFireEvent(IGameEvent* event);
    void OnDraw();
}
