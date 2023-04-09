#pragma once
#include "Framework/Memory/Memory.h"
#include "ValveSDK/Misc/VFunctionIndexes.h"

class IPanel
{
public:
    const char *GetName(unsigned int vguiPanel)
    {
        typedef const char *(__thiscall* tGetName)(void*, unsigned int);
        return Memory::CallVirtual<tGetName>(this, (int) VGuiPanelVFunc::GetName)(this, vguiPanel);
    }
};
