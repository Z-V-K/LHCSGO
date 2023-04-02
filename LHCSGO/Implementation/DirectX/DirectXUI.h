#pragma once

namespace DirectXUI
{
    void Initialize();
    
    void StartFrame();
    void EndFrame();

    inline LPDIRECT3DDEVICE9 dx9Device;
    inline bool initialized = false;
};
