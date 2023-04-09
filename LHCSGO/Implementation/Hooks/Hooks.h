#pragma once
#include "../../Framework/Hooks/ShadowVMT.h"

enum struct HookIndex : int
{
    /* GameEventManager */
    FireEvent = 9,

    /* BaseClient */
    FrameStageNotify = 37,

    /* VGUI */
    PaintTraverse = 41,

    /* D3DDEvice */
    Reset = 16,
    Present = 17,
    EndScene = 42,
};

namespace Hooks
{
    inline ShadowVMT direct3d_hook{ };
    inline ShadowVMT baseclient_hook{ };
    inline ShadowVMT gameeventmanager_hook{ };
    inline ShadowVMT vguipanel_hook{ };
    
    void Initialize();
    void Remove();
};
