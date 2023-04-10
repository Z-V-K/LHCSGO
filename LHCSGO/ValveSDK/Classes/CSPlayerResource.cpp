#include "pch.h"
#include "CSPlayerResource.h"

const char* CSPlayerResource::GetCompetitiveRank(const int index)
{
    static const char* ranks_str[] =
    {   
        "Unranked",
        "Silver 1",
        "Silver 2",
        "Silver 3",
        "Silver 4",
        "Silver Elite",
        "Silver Elite Master",

        "Nova 1",
        "Nova 2",
        "Nova 3",
        "Nova Master",
        "MG 1",
        "MG 2",
        "MGE",
            
        "DMG",
        "LE",
        "LEM",
        "Supreme",
        "Global"
    };

    int idx = *reinterpret_cast<int*>((uintptr_t) m_iCompetitiveRanking() + index * 4);
    return ranks_str[idx];
}
