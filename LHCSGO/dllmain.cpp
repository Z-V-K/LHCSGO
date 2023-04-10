// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Implementation/Core.h"
#include <iostream>

#include "Framework/Context.h"
#include "Implementation/CallbackManager/CallbackManager.h"
#include "Implementation/Hooks/Hooks.h"

HANDLE thread_handle;

void DLLDetach();

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

    while(!g_ctx->unload)
        Sleep(1000);

    DLLDetach();

    return 0;
}

void DLLDetach()
{
    printf("Deleting DLL!\n");
    CallbackManager::ClearCallbacks();
    Hooks::Remove();
    FreeConsole();
    TerminateThread(thread_handle, 1);
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
        thread_handle = CreateThread(nullptr, 0, DLLAttach, hModule, 0, nullptr);
        DisableThreadLibraryCalls(hModule);
        break;
    default:
        break;
    }
    
    return TRUE;
}