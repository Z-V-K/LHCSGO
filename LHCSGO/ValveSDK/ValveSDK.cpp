#include "pch.h"
#include "ValveSDK.h"

#include "Classes/BaseEntity.h"
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

    const auto engine_factory = GetModuleFactory(engine);
    const auto client_factory = GetModuleFactory(client);

    base_client = GetInterface<IBaseClient>(client_factory, "VClient018");
    entity_list = GetInterface<IClientEntityList> (client_factory, "VClientEntityList003");
    engine_client = GetInterface<IEngineClient> (engine_factory, "VEngineClient014");
    game_event_manager = GetInterface<IGameEventManager> (engine_factory, "GAMEEVENTSMANAGER002");
    
    const auto shaderapidx9 = GetModuleHandleA("shaderapidx9.dll");
    game_device = **reinterpret_cast<IDirect3DDevice9***>(Memory::PatternScan(shaderapidx9, "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);    

    local_player = entity_list->GetClientEntity(engine_client->GetLocalPlayer());
}
