#pragma once

class ProtectGuard
{
public:
    ProtectGuard(void* base, size_t len, std::uint32_t flags)
    {
        _base = base;
        _length = len;
        if (!VirtualProtect(base, len, flags, (PDWORD)&_old))
            throw std::runtime_error("Failed to protect region");
    }
    ~ProtectGuard()
    {
        VirtualProtect(_base, _length, _old, (PDWORD)&_old);
    }

private:
    void*         _base;
    size_t        _length;
    std::uint32_t _old;
};

class VMTHook
{
public:
    VMTHook();
    VMTHook(void* base);
    ~VMTHook();

    bool Setup(void* class_base = nullptr);

    template<typename T>
    void HookIndex(int index, T fun)
    {
        assert(index >= 0 && index <= (int)vftbl_len);
        new_vftbl[index + 1] = reinterpret_cast<std::uintptr_t>(fun);
    }
    void UnhookIndex(int index)
    {
        new_vftbl[index] = old_vftbl[index];
    }
    void UnhookAll()
    {
        try {
            if (old_vftbl != nullptr) {
                auto guard = ProtectGuard{ class_base, sizeof(std::uintptr_t), PAGE_READWRITE };
                *(std::uintptr_t**)class_base = old_vftbl;
                old_vftbl = nullptr;
            }
        }
        catch (...) {
        }
    }

    template<typename T>
    T GetOG(int index)
    {
        return (T)old_vftbl[index];
    }

private:
    static inline std::size_t EstimateVirtualTableLength(std::uintptr_t* vftbl_start);

    void*           class_base;
    std::size_t     vftbl_len;
    std::uintptr_t* new_vftbl;
    std::uintptr_t* old_vftbl;
};
