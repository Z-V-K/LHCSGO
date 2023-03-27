#include "pch.h"
#include "Direct3DDevice.h"

#include "../Hooks.h"
#include "../../Core.h"

long Direct3DDevice::hkEndScene(IDirect3DDevice9* device)
{
    return g_core->hooks.direct3d_hook.GetOG<decltype(&hkEndScene)>((int) HookIndex::EndScene)(device);
}

long Direct3DDevice::hkReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    return g_core->hooks.direct3d_hook.GetOG<decltype(&hkReset)>((int) HookIndex::Reset)(device, pPresentationParameters);
}