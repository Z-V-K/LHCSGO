#include "pch.h"
#include "ValveSDK.h"

#include "Classes/BaseEntity.h"
#include "Classes/BasePlayer.h"
#include "ValveSDK/Interfaces/IEngineClient.h"
#include "Framework/Memory/Memory.h"

typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
typedef void* (*InstantiateInterfaceFn)();

CreateInterfaceFn GetModuleFactory(const HMODULE module)
{
    return reinterpret_cast<CreateInterfaceFn>(GetProcAddress(module, "CreateInterface"));
}

template<typename T>
T* GetInterface(const CreateInterfaceFn f, const char* szInterfaceVersion)
{
    auto result = static_cast<T*>(f(szInterfaceVersion, nullptr));

    if(!result) {
        printf("Failed to GetOffset in interface: %s", szInterfaceVersion);
        return nullptr;
    }

    return result;
}

void ValveSDK::Initialize()
{
    const auto engine = GetModuleHandleA("engine.dll");
    const auto client = GetModuleHandleA("client.dll");
    const auto vgui = GetModuleHandleA("vgui2.dll");
    const auto vgui_mat_surface = GetModuleHandleA("vguimatsurface.dll");

    const auto engine_factory = GetModuleFactory(engine);
    const auto client_factory = GetModuleFactory(client);
    const auto vgui_factory = GetModuleFactory(vgui);
    const auto vgui_mat_surface_factory = GetModuleFactory(vgui_mat_surface);

    base_client = GetInterface<IBaseClient>(client_factory, "VClient018");
    entity_list = GetInterface<IClientEntityList> (client_factory, "VClientEntityList003");
    engine_client = GetInterface<IEngineClient> (engine_factory, "VEngineClient014");
    game_event_manager = GetInterface<IGameEventManager> (engine_factory, "GAMEEVENTSMANAGER002");
    panel = GetInterface<IPanel> (vgui_factory, "VGUI_Panel009");
    surface = GetInterface<ISurface> (vgui_mat_surface_factory, "VGUI_Surface031");
    model_info_client = GetInterface<IModelInfoClient> (engine_factory, "VModelInfoClient004");
    
    const auto shaderapidx9 = GetModuleHandleA("shaderapidx9.dll");
    game_device = **reinterpret_cast<IDirect3DDevice9***>(Memory::PatternScan(shaderapidx9, "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);

    global_vars = **reinterpret_cast<GlobalVars***>(Memory::PatternScan(client, "A1 ? ? ? ? 5E 8B 40 10") + 1);
    player_resource = *reinterpret_cast<CSPlayerResource***>(Memory::PatternScan(client, "A1 ? ? ? ? 89 44 24 60 85") + 1);
}
