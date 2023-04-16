#include "pch.h"
#include "EnginePrediction.h"

#include "ValveSDK/Classes/MoveData.h"

namespace EnginePrediction
{
	unsigned int* pred_random_seed = nullptr;
	BaseEntity** pred_player = nullptr;
	MoveData move_data = { };

	// backup values
	float old_currtime = 0.f;
	float old_frametime = 0.f;	
	int old_tickcount = 0;

	float Tick2Time(float t)
	{
		return g_globalvars->interval_per_tick * t;
	}

	int GetTickBase(CUserCmd* cmd, const BasePlayer* local_player)
	{
		static int iTick = 0;

		if (cmd)
		{
			static CUserCmd* last_cmd = nullptr;

			// if command was not predicted - increment tickbase
			if (last_cmd == nullptr || last_cmd->hasbeenpredicted)
				iTick = local_player->m_nTickBase();
			else
				iTick++;

			last_cmd = cmd;
		}

		return iTick;
	}
	
	void Start(CUserCmd* cmd, BasePlayer* local_player)
	{
		if (!local_player->IsAlive())
			return;

		*local_player->GetCurrentCommand() = cmd;
		local_player->GetLastCommand() = *cmd;

		*pred_random_seed = cmd->random_seed;
		*pred_player = local_player;

		old_currtime = g_globalvars->curtime;
		old_frametime = g_globalvars->frametime;
		old_tickcount = g_globalvars->tickcount;

		const int old_tickbase = local_player->m_nTickBase();
		const bool old_is_first_pred = g_prediction->first_time_predicted;
		const bool old_in_pred = g_prediction->in_prediction;

		// set corrected values
		g_globalvars->curtime = Tick2Time(GetTickBase(cmd ,local_player));
		g_globalvars->frametime = g_prediction->engine_paused ? 0.f : g_globalvars->interval_per_tick;
		g_globalvars->tickcount = GetTickBase(cmd, local_player);

		g_prediction->first_time_predicted = false;
		g_prediction->in_prediction = true;

		cmd->buttons |= local_player->GetButtonForced();
		cmd->buttons &= ~(local_player->GetButtonDisabled());

		g_movement->StartTrackPredictionErrors(local_player);

		// const int buttons = cmd->buttons;
		// const int local_buttons = *local_player->GetButtons();
		// const int buttons_changed = buttons ^ local_buttons;
		//
		// local_player->GetButtonLast() = local_buttons;
		// *local_player->GetButtons() = buttons;
		//
		// local_player->GetButtonPressed() = buttons_changed & buttons;
		// local_player->GetButtonReleased() = buttons_changed & (~buttons);

		g_prediction->CheckMovingGround(local_player, g_globalvars->frametime);
		g_prediction->SetLocalViewAngles(cmd->viewangles);

		if (local_player->PhysicsRunThink(0)) // THINK_FIRE_ALL_FUNCTIONS
			local_player->PreThink();

		if (int32_t* next_think_tick = local_player->m_nNextThinkTick(); *next_think_tick > 0 && *next_think_tick <= GetTickBase(cmd, local_player))
		{
			*next_think_tick = -1; // TICK_NEVER_THINK
			local_player->Think();
		}

		g_movehelper->SetHost(local_player);

		// setup move
		g_prediction->SetupMove(local_player, cmd, g_movehelper, &move_data);
		g_movement->ProcessMovement(local_player, &move_data);

		// finish move
		g_prediction->FinishMove(local_player, cmd, &move_data);
		g_movehelper->ProcessImpacts();

		local_player->PostThink();

		// restore backups
		local_player->m_nTickBase() = old_tickbase;
		g_prediction->in_prediction = old_in_pred;
		g_prediction->first_time_predicted = old_is_first_pred;
	}
	
	void End(BasePlayer* local_player)
	{
		if (!local_player->IsAlive() )
			return;

		g_movement->FinishTrackPredictionErrors(local_player);
		
		g_movehelper->SetHost(nullptr);

		// restore globals
		g_globalvars->curtime = old_currtime;
		g_globalvars->frametime = old_frametime;
		g_globalvars->tickcount = old_tickcount;
		
		*local_player->GetCurrentCommand() = nullptr;
		
		*pred_random_seed = -1;
		*pred_player = nullptr;

		g_movement->Reset();
	}
}
