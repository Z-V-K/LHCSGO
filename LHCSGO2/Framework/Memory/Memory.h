#pragma once

class Memory
{
public:
    static std::uint8_t* PatternScan(void* module, const char* signature);

    template<typename FuncType>
    __forceinline static FuncType CallVirtual(void* ppClass, int index)
    {
        int* pVTable = *(int**)ppClass;
        int dwAddress = pVTable[index];
        return (FuncType)(dwAddress);
    }
};
