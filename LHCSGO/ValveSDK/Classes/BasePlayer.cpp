#include "pch.h"
#include "BasePlayer.h"

const char* BasePlayer::GetRank()
{
    return (*g_playerresource)->GetCompetitiveRank(EntIndex());
}