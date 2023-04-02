#include "pch.h"
#include "PlayerList.h"

#include "Implementation/CallbackManager/CallbackManager.h"

namespace PlayerList
{
    void Initialize()
    {
        CallbackManager::AddCallback(CallbackType::OnUpdate, OnUpdate);
        CallbackManager::AddCallback(CallbackType::OnDraw, OnDraw);
    }

    void OnUpdate()
    {
        
    }

    void OnDraw()
    {
        
    }
}
