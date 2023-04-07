// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Implementation/Core.h"
#include <iostream>

void CreateConsole()
{
    if (!AllocConsole()) {
        return;
    }
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
}

DWORD WINAPI DLLAttach(LPVOID base)
{
    CreateConsole();
    
    g_core->Initialize(base);

    return 0;
}

void WINAPI DLLDetach(HMODULE hModule)
{
    FreeLibraryAndExitThread(hModule, 0);
    /* TODO */
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
)
{
    UNREFERENCED_PARAMETER(lpReserved);
    
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, DLLAttach, hModule, 0, nullptr);
        DisableThreadLibraryCalls(hModule);
        break;
    case DLL_PROCESS_DETACH:
        DLLDetach(hModule);
        break;
    default:
        break;
    }
    
    return TRUE;
}