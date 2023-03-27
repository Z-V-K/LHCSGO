#pragma once

#include "Interfaces/IClientEntityList.h"
#include "Interfaces/IEngineClient.h"

class ValveSDK
{
public:
    ValveSDK();

    IClientEntityList* entity_list;
    IEngineClient* engine_client;
    IDirect3DDevice9* game_device;
};

extern std::shared_ptr<ValveSDK> g_sdk;
