#pragma once

#include "Interfaces/IEngineClient.h"
#include "Interfaces/IClientEntityList.h"
#include "Interfaces/IBaseClient.h"
#include "Interfaces/IGameEventManager.h"
#include "Interfaces/IModelInfoClient.h"
#include "Interfaces/ISurface.h"
#include "Interfaces/IPanel.h"

namespace ValveSDK
{
    void Initialize();

    inline IBaseClient* base_client = nullptr;
    inline IClientEntityList* entity_list = nullptr;
    inline IEngineClient* engine_client = nullptr;
    inline IGameEventManager* game_event_manager = nullptr;
    inline IDirect3DDevice9* game_device = nullptr;
    inline IPanel* panel = nullptr;
    inline ISurface* surface = nullptr;
    inline IModelInfoClient* model_info_client = nullptr;
    inline GlobalVars* global_vars = nullptr;

    inline BaseEntity* local_player = nullptr;
};

#define g_baseclient    ValveSDK::base_client
#define g_entitylist    ValveSDK::entity_list
#define g_engine        ValveSDK::engine_client
#define g_eventmanager  ValveSDK::game_event_manager
#define g_device        ValveSDK::game_device
#define g_vguipanel     ValveSDK::panel
#define g_surface       ValveSDK::surface
#define g_localplayer   ValveSDK::local_player
#define g_modelinfo     ValveSDK::model_info_client
#define g_globalvars    ValveSDK::global_vars

