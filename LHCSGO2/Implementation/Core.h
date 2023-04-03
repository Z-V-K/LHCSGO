#pragma once

class Core
{
public:    
    void Initialize(LPVOID base);
};

extern std::shared_ptr<Core> g_core;
