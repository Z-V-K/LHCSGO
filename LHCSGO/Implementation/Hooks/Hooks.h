#pragma once
#include "../../Framework/Hooks/VMTHook.h"

enum struct HookIndex : int
{
    Reset = 16,
    EndScene = 42,
};

class Hooks
{
public:
    VMTHook hlclient_hook;
    VMTHook direct3d_hook;
    VMTHook vguipanel_hook;
    VMTHook vguisurf_hook;
    VMTHook mdlrender_hook;
    VMTHook viewrender_hook;
    VMTHook sound_hook;
    VMTHook clientmode_hook;
    VMTHook sv_cheats;
    VMTHook bsp_query_hook;
    VMTHook player_hook;
    VMTHook engine_hook;
    
    Hooks();
    ~Hooks();
};
