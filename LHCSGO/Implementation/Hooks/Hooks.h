#pragma once
#include "../../Framework/Hooks/ShadowVMT.h"

enum struct HookIndex : int
{
    Reset = 16,
    Present = 17,
    EndScene = 42,
};

namespace Hooks
{
    inline ShadowVMT direct3d_hook{ };
    
    inline ShadowVMT hlclient_hook{ };
    inline ShadowVMT vguipanel_hook{ };
    inline ShadowVMT vguisurf_hook{ };
    inline ShadowVMT mdlrender_hook{ };
    inline ShadowVMT viewrender_hook{ };
    inline ShadowVMT sound_hook{ };
    inline ShadowVMT clientmode_hook{ };
    inline ShadowVMT sv_cheats{ };
    inline ShadowVMT bsp_query_hook{ };
    inline ShadowVMT player_hook{ };
    inline ShadowVMT engine_hook{ };
    
    void Initialize();
    void Remove();
};
