#pragma once
#include "ValveSDK/Interfaces/IGameEvent.h"

namespace PlayerList
{
    void Initialize();
    void Delete();

    void OnUpdate();
    void OnFireEvent(IGameEvent* event);
    void OnDraw();
}
