// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Framework/Context.h"
#include "Implementation/Core.h"


DWORD WINAPI DLLAttach(LPVOID base)
{
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
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, DLLAttach, hModule, 0, nullptr);
        break;
    case DLL_PROCESS_DETACH:
        DLLDetach(hModule);
        break;
    default:
        break;
    }
    
    return TRUE;
}

