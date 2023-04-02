#include "pch.h"
#include "ValveSDK.h"

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
        throw std::runtime_error(std::string("[get_interface] Failed to GetOffset interface: ") + szInterfaceVersion);
    }

    return result;
}

void ValveSDK::Initialize()
{
    const auto engine_factory = GetModuleFactory(GetModuleHandleA("engine.dll"));
    const auto client_factory = GetModuleFactory(GetModuleHandleA("client.dll"));
    
    entity_list = GetInterface<IClientEntityList> (client_factory, "VClientEntityList003");
    engine_client = GetInterface<IEngineClient> (engine_factory, "VEngineClient014");
    
    const auto shaderapidx9 = GetModuleHandleA("shaderapidx9.dll");
    game_device = **(IDirect3DDevice9***)(Memory::PatternScan(shaderapidx9, "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);
}
