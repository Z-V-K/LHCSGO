#pragma once
#include "ValveSDK/NetvarManager.h"

class CSPlayerResource
{
public:
    PNETVAR(int32_t, m_iCompetitiveRanking, "DT_CSPlayerResource", "m_iCompetitiveRanking")

    const char* GetCompetitiveRank(int index);
};
