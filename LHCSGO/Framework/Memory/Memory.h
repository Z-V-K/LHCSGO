#pragma once

class Memory
{
public:
    static std::uint8_t* PatternScan(void* module, const char* signature);
};
