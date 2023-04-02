#include "pch.h"
#include "Direct3DDevice.h"

#include "../Hooks.h"
#include "Framework/imgui/imgui.h"
#include "Implementation/DirectX/DirectXUI.h"
#include "Framework/imgui/implementation/imgui_impl_dx9.h"
#include "ValveSDK/ValveSDK.h"
#include "Implementation/CallbackManager/CallbackManager.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool hwndInitialized = false;
WNDPROC m_wndProc;

long __stdcall Direct3DDevice::hkPresent(
            LPDIRECT3DDEVICE9 pDevice, 
            RECT* pSourceRect, 
            RECT* pDestRect,
            HWND hDestWindowOverride, 
            RGNDATA* pDirtyRegion
) {
    if (!hwndInitialized)
    {
        dx9_device = ValveSDK::game_device;
    
        D3DDEVICE_CREATION_PARAMETERS parameters;
        ZeroMemory(&parameters, sizeof(parameters));
        pDevice->GetCreationParameters(&parameters);
        game_hwnd = parameters.hFocusWindow;
    
        m_wndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(game_hwnd, GWL_WNDPROC, reinterpret_cast<LONG>(hkWndProc)));
    
        hwndInitialized = true;
    }
    
    if (!DirectXUI::initialized) {
        DirectXUI::Initialize();
    }
    
    DirectXUI::StartFrame();

    CallbackManager::Trigger(OnPresent);
    
    DirectXUI::EndFrame();
    
    return Hooks::direct3d_hook.GetOg<decltype(&hkPresent)>((int) HookIndex::Present)(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

long __stdcall Direct3DDevice::hkReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    ImGui_ImplDX9_InvalidateDeviceObjects();

    HRESULT hResult = Hooks::direct3d_hook.GetOg<decltype(&hkReset)>((int)HookIndex::Reset)(device, pPresentationParameters);
    if (hResult != D3DERR_INVALIDCALL)
        ImGui_ImplDX9_CreateDeviceObjects();

    return hResult;
}

LRESULT __stdcall Direct3DDevice::hkWndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    bool execute = true;
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
        execute = false;
    }
    
    if (execute)
        return CallWindowProc(m_wndProc, hWnd, uMsg, wParam, lParam);

    return 1;
}