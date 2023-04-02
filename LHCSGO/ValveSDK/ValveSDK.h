#pragma once

#include "Interfaces/IClientEntityList.h"
#include "Interfaces/IEngineClient.h"

namespace ValveSDK
{
    void Initialize();

    inline IClientEntityList* entity_list = nullptr;
    inline IEngineClient* engine_client = nullptr;
    inline IDirect3DDevice9* game_device = nullptr;
};
