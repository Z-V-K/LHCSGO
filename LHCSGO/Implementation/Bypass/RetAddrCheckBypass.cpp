#include "pch.h"
#include "RetAddrCheckBypass.h"
#include "Framework/Hooks/InlineHook.h"
#include "Framework/Memory/Memory.h"

InlineHook func_hook{ };

bool __fastcall hk_ReturnAddressCheck(void*, void*, const char*)
{
    return true;
}

void RetAddrCheckBypass::Initialize()
{
    const HMODULE client = GetModuleHandleA("client.dll");
    const HMODULE engine = GetModuleHandleA("engine.dll");
    const HMODULE studio_render = GetModuleHandleA("studiorender.dll");
    const HMODULE material_system = GetModuleHandleA("materialsystem.dll");

    const auto func_sig = "55 8B EC 56 8B F1 33 C0 57 8B 7D 08 8B 8E ? ? ? ? 85 C9 7E";

    void* client_func = Memory::PatternScan(client, func_sig);
    void* engine_func = Memory::PatternScan(engine, func_sig);
    void* studio_render_func = Memory::PatternScan(studio_render, func_sig);
    void* material_system_func = Memory::PatternScan(material_system, func_sig);

    if(client_func)
        func_hook.Hook(client_func, hk_ReturnAddressCheck, 6);
    if(engine_func)
        func_hook.Hook(engine_func, hk_ReturnAddressCheck, 6);
    if(studio_render_func)
        func_hook.Hook(studio_render_func, hk_ReturnAddressCheck, 6);
    if(material_system_func)
        func_hook.Hook(material_system_func, hk_ReturnAddressCheck, 6);
}