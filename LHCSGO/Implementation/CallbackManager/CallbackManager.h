#pragma once

enum CallbackType : unsigned
{
    OnDraw,
    OnPreFrameRenderStart,
    OnPreFrameRenderEnd,
    OnPreFrameNetUpdateStart,
    OnPreFrameNetUpdateEnd,
    OnPostFrameRenderStart,
    OnPostFrameRenderEnd,
    OnPostFrameNetUpdateStart,
    OnPostFrameNetUpdateEnd,
    OnFireEvent,
    
    Size
};

namespace CallbackManager
{
    inline std::vector<void*> callbacks[(unsigned int)CallbackType::Size] { };
    
    void AddCallback(CallbackType cbType, void* fct);
    bool RemoveCallback(CallbackType cbType, void* fct);
    void ClearCallbacks();

    template <typename... Args>
    void Trigger(CallbackType cbType, Args... args)
    {
    	for (const auto& cb : callbacks[cbType])
    		static_cast<void(*)(Args...)>(cb)(args...);
    }
};
