#pragma once
#include "Hooks/Hooks.h"

class Core
{
public:
    Hooks hooks;
    
    void Initialize(LPVOID base);
};

extern std::shared_ptr<Core> g_core;
