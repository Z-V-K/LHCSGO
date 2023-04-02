#pragma once

class InlineHook
{
    std::vector<BYTE> og_bytes;
    DWORD original = 0;
    DWORD source = 0;
    bool bEnabled = false;
public:
    InlineHook(){}

    void Hook(void* src, void* dest, const size_t len);
    void Unhook();

    template<typename T>
    T GetOg()
    {
        return (T)original;
    }
};
