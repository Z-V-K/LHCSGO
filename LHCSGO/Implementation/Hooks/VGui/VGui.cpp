#include "pch.h"
#include "VGui.h"

#include "Implementation/CallbackManager/CallbackManager.h"
#include "Implementation/Hooks/Hooks.h"
#include "Implementation/Menu/MenuManager.h"
#include "Implementation/Renderer/Renderer.h"
#include "ValveSDK/ValveSDK.h"

void __fastcall VGui::hk_PaintTraverse(void* thisPtr, void* edx, VPANEL panel, bool force_repaint, bool allow_force)
{
    Hooks::vguipanel_hook.GetOg<decltype(&hk_PaintTraverse)>((int) HookIndex::PaintTraverse)(thisPtr, edx, panel, force_repaint, allow_force);

    static VPANEL focus_overlay_panel = 0;
    if(!focus_overlay_panel)
    {
        if(!strcmp(g_vguipanel->GetName(panel), "FocusOverlayPanel"))
        {
            Renderer::SetupFonts();
            focus_overlay_panel = panel;
            return;
        }
    }

    if(panel == focus_overlay_panel)
    {
        MenuManager::OnDraw();
        CallbackManager::Trigger(OnPaintTraverse);
    }
}