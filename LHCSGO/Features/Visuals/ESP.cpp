#include "pch.h"
#include "ESP.h"

#include "Implementation/CallbackManager/CallbackManager.h"
#include "ValveSDK/ValveSDK.h"
#include "ValveSDK/Classes/BasePlayer.h"

namespace ESP
{
    void Initialize()
    {
        CallbackManager::AddCallback(CallbackType::OnDraw, OnDraw);
        CallbackManager::AddCallback(CallbackType::OnPreFrameNetUpdateStart, OnUpdate);
    }

    void Delete()
    {

    }

    void OnDraw()
    {
        
    }

    void OnUpdate()
    {
        for(int i = 0; i < g_entitylist->GetMaxEntities(); i++)
        {
            const auto entity = (BasePlayer*) g_entitylist->GetClientEntity(i);
        
            if(!entity || !entity->IsAlive())
                continue;

            Vec3 bb_min, bb_max;
            entity->GetRenderBounds(bb_min, bb_max);
        }
    }
}

