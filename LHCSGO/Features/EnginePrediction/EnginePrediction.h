#pragma once
#include "ValveSDK/Classes/BasePlayer.h"
#include "ValveSDK/Classes/CUserCmd.h"

namespace EnginePrediction
{
	void Start(CUserCmd* cmd, BasePlayer* local_player);
	void End(BasePlayer* local_player);
}
