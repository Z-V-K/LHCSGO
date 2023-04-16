#pragma once

#include "Classes/CSPlayerResource.h"
#include "Interfaces/IEngineClient.h"
#include "Interfaces/IClientEntityList.h"
#include "Interfaces/IBaseClient.h"
#include "Interfaces/IGameEventManager.h"
#include "Interfaces/IGameMovement.h"
#include "Interfaces/IMdlCache.h"
#include "Interfaces/IModelInfoClient.h"
#include "Interfaces/IMoveHelper.h"
#include "Interfaces/ISurface.h"
#include "Interfaces/IPanel.h"
#include "Interfaces/IPrediction.h"

class BasePlayer;

class LocalPlayer
{
    friend bool operator==(const LocalPlayer& lhs, void* rhs);
public:
    LocalPlayer() : m_local(nullptr) {}

    operator bool() const { return *m_local != nullptr; }
    operator BasePlayer*() const { return *m_local; }
    constexpr auto get() noexcept
    {
        return *m_local;
    }

    BasePlayer* operator->() { return *m_local; }

private:
    BasePlayer** m_local;
};

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
    inline CSPlayerResource** player_resource = nullptr;
    inline IPrediction* prediction = nullptr;
    inline IGameMovement* movement = nullptr;
    inline IMoveHelper* move_helper = nullptr;
    inline IMDLCache* model_cache = nullptr;
};

#define g_baseclient     ValveSDK::base_client
#define g_entitylist     ValveSDK::entity_list
#define g_engine         ValveSDK::engine_client
#define g_eventmanager   ValveSDK::game_event_manager
#define g_device         ValveSDK::game_device
#define g_vguipanel      ValveSDK::panel
#define g_surface        ValveSDK::surface
#define g_modelinfo      ValveSDK::model_info_client
#define g_globalvars     ValveSDK::global_vars
#define g_playerresource ValveSDK::player_resource
#define g_prediction     ValveSDK::prediction
#define g_movement       ValveSDK::movement
#define g_movehelper     ValveSDK::move_helper
#define g_mdlcache       ValveSDK::model_cache

__forceinline BasePlayer* GetLocalPlayer()
{
    return (BasePlayer*) g_entitylist->GetClientEntity(g_engine->GetLocalPlayer());
}

#define g_localplayer GetLocalPlayer()