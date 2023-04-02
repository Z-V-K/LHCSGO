#pragma once

#include "Interfaces/IEngineClient.h"
#include "Interfaces/IClientEntityList.h"
#include "Interfaces/IBaseClient.h"
#include "Interfaces/IGameEventManager.h"

class LocalPlayer
{
    friend bool operator==(const LocalPlayer& lhs, void* rhs);
public:
    LocalPlayer() : m_local(nullptr) {}

    operator bool() const { return *m_local != nullptr; }
    operator BaseEntity*() const { return *m_local; }
    constexpr auto get() const noexcept
    {
        return *m_local;
    }

    BaseEntity* operator->() const { return *m_local; }

private:
    BaseEntity** m_local;
};

namespace ValveSDK
{
    void Initialize();

    inline IBaseClient* base_client = nullptr;
    inline IClientEntityList* entity_list = nullptr;
    inline IEngineClient* engine_client = nullptr;
    inline IGameEventManager* game_event_manager = nullptr;
    inline IDirect3DDevice9* game_device = nullptr;

    inline LocalPlayer local_player;
};

#define g_baseclient    ValveSDK::base_client
#define g_entitylist    ValveSDK::entity_list
#define g_engine        ValveSDK::engine_client
#define g_eventmanager  ValveSDK::game_event_manager
#define g_device        ValveSDK::game_device
#define g_localplayer   ValveSDK::local_player

