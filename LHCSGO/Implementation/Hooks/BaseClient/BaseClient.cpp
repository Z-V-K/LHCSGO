#include "pch.h"
#include "BaseClient.h"
#include "../Hooks.h"
#include "Implementation/CallbackManager/CallbackManager.h"
#include "ValveSDK/ValveSDK.h"

void __fastcall BaseClient::hk_FrameStageNotify(void* thisPtr, void* edx, ClientFrameStage stage)
{
    if(!g_localplayer)
        g_localplayer = g_entitylist->GetClientEntity(g_engine->GetLocalPlayer());
    
    switch(stage)
    {
    case ClientFrameStage::FRAME_START:
        CallbackManager::Trigger(OnPreFrameRenderStart);
        break;
    case ClientFrameStage::FRAME_RENDER_END:
        CallbackManager::Trigger(OnPreFrameRenderEnd);
        break;
    case ClientFrameStage::FRAME_NET_UPDATE_START:
        CallbackManager::Trigger(OnPreFrameNetUpdateStart);
        break;
    case ClientFrameStage::FRAME_NET_UPDATE_END:
        CallbackManager::Trigger(OnPreFrameNetUpdateEnd);
        break;
    default:
        break;
    }

    Hooks::baseclient_hook.GetOg<decltype(&hk_FrameStageNotify)>((int) HookIndex::FrameStageNotify)(thisPtr, edx, stage);

    switch(stage)
    {
    case ClientFrameStage::FRAME_START:
        CallbackManager::Trigger(OnPostFrameRenderStart);
        break;
    case ClientFrameStage::FRAME_RENDER_END:
        CallbackManager::Trigger(OnPostFrameRenderEnd);
        break;
    case ClientFrameStage::FRAME_NET_UPDATE_START:
        CallbackManager::Trigger(OnPostFrameNetUpdateStart);
        break;
    case ClientFrameStage::FRAME_NET_UPDATE_END:
        CallbackManager::Trigger(OnPostFrameNetUpdateEnd);
        break;
    default:
        break;
    }
}
