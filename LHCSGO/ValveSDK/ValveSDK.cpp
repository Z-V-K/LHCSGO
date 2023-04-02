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

bool getD3D9Device(void** pTable, size_t Size)
{
    // no ptable.
    if (!pTable)
        return false;

    IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

    // Direct3DCreate9 failed.
    if (!pD3D)
        return false;

    D3DPRESENT_PARAMETERS d3dpp = { 0 };
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = GetForegroundWindow();
    d3dpp.Windowed = ((GetWindowLong(d3dpp.hDeviceWindow, GWL_STYLE) & WS_POPUP) != 0) ? FALSE : TRUE;;


    IDirect3DDevice9* pDummyDevice = nullptr;
    HRESULT create_device_ret = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);
    if (!pDummyDevice || FAILED(create_device_ret))
    {
        // CreateDevice failed
        pD3D->Release();
        return false;
    }

    memcpy(pTable, *reinterpret_cast<void***>(pDummyDevice), Size);

    pDummyDevice->Release();
    pD3D->Release();

    return true;
}

void ValveSDK::Initialize()
{
    const auto engine_factory = GetModuleFactory(GetModuleHandleA("engine.dll"));
    const auto client_factory = GetModuleFactory(GetModuleHandleA("client.dll"));
    
    entity_list = GetInterface<IClientEntityList> (client_factory, "VClientEntityList003");
    engine_client = GetInterface<IEngineClient> (engine_factory, "VEngineClient014");
    
    const auto shaderapidx9 = GetModuleHandleA("shaderapidx9.dll");
    game_device = **(IDirect3DDevice9***)(Memory::PatternScan(shaderapidx9, "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);
    // game_device = (IDirect3DDevice9*) d3d9Device;
}
