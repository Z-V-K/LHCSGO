#include "pch.h"
#include "DirectXUI.h"

#include "../Hooks/Direct3DDevice/Direct3DDevice.h"
#include "../../Framework/imgui/imgui.h"
#include "../../Framework/imgui/implementation/imgui_impl_win32.h"
#include "../../Framework/imgui/implementation/imgui_impl_dx9.h"
#include "ValveSDK/ValveSDK.h"

void DirectXUI::Initialize()
{
    ImGui::CreateContext();

    ImGui_ImplWin32_Init(Direct3DDevice::game_hwnd);
    ImGui_ImplDX9_Init(g_device);
    
    ImGui::StyleColorsDark();

    initialized = true;
}

void DirectXUI::StartFrame()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();

    const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground;

    ImGui::Begin("##overlay", nullptr, flags);

    ImGui::SetWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
}

void DirectXUI::EndFrame()
{
    ImGui::GetForegroundDrawList()->PushClipRectFullScreen();
    ImGui::End();
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}