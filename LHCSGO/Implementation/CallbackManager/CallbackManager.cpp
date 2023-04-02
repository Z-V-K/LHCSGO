#include "pch.h"
#include "CallbackManager.h"

void CallbackManager::AddCallback(CallbackType cbType, void* fct)
{
    callbacks[cbType].push_back(fct);
}

bool CallbackManager::RemoveCallback(CallbackType cbType, void* fct)
{
    auto f = callbacks[cbType];

    const auto it = std::find(f.begin(), f.end(), fct);

    if(it != f.end())
    {
    	f.erase(it);
    	return true;
    }

    return false;
}

void CallbackManager::ClearCallbacks()
{
    for (int i = 0; i < CallbackType::Size; i++)
    	callbacks[i].clear();
}