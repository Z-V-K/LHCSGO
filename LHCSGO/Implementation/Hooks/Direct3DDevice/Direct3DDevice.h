#pragma once

class Direct3DDevice
{
public:
    static long __stdcall hkEndScene(IDirect3DDevice9* device);
    static long __stdcall hkReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters);
};
