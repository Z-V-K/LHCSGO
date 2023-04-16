#pragma once
#include "EHandle.h"
#include "BaseCombatWeapon.h"
#include "CUserCmd.h"

enum EntityFlags
{
     FL_ONGROUND = (1 << 0), 	     // At rest / on the ground
     FL_DUCKING = (1 << 1),		// Player flag -- Player is fully crouched
     FL_WATERJUMP = (1 << 2),	     // player jumping out of water
     FL_ONTRAIN = (1 << 3),		// Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
     FL_INRAIN = (1 << 4),		// Indicates the entity is standing in rain
     FL_FROZEN = (1 << 5),		// Player is frozen for 3rd person camera
     FL_ATCONTROLS = (1 << 6),	// Player can't move, but keeps key inputs for controlling another entity
     FL_CLIENT = (1 << 7),		// Is a player
     FL_FAKECLIENT = (1 << 8),	// Fake client, simulated server side; don't send network messages to them
     FL_INWATER = (1 << 10),		// In water
};

class BasePlayer : public BaseEntity
{
public:
     NETVAR(EHandle<BasePlayer>, m_hObserverTarget, "DT_BasePlayer", "m_hObserverTarget")
     NETVAR(int32_t,     m_iFOV,             "DT_BasePlayer", "m_iFOV")  
     NETVAR(int32_t,     m_iFOVStart,        "DT_BasePlayer", "m_iFOVStart")  
     NETVAR(float,       m_flFOVTime,        "DT_BasePlayer", "m_flFOVTime")  
     NETVAR(int32_t,     m_iDefaultFOV,      "DT_BasePlayer", "m_iDefaultFOV")  
     NETVAR(int32_t,     m_hZoomOwner,       "DT_BasePlayer", "m_hZoomOwner")  
     NETVAR(int32_t,     m_hVehicle,         "DT_BasePlayer", "m_hVehicle")  
     NETVAR(int32_t,     m_hUseEntity,       "DT_BasePlayer", "m_hUseEntity")  
     NETVAR(int32_t,     m_iHealth,          "DT_BasePlayer", "m_iHealth")  
     NETVAR(int32_t,     m_lifeState,        "DT_BasePlayer", "m_lifeState")  
     NETVAR(int32_t,     m_iBonusProgress,   "DT_BasePlayer", "m_iBonusProgress")  
     NETVAR(int32_t,     m_iBonusChallenge,  "DT_BasePlayer", "m_iBonusChallenge")  
     NETVAR(float,       m_flMaxspeed,       "DT_BasePlayer", "m_flMaxspeed")  
     NETVAR(int32_t,     m_fFlags,           "DT_BasePlayer", "m_fFlags")  
     NETVAR(int32_t,     m_iObserverMode,    "DT_BasePlayer", "m_iObserverMode")  
     NETVAR(int32_t*,    m_hViewModel,       "DT_BasePlayer", "m_hViewModel[0]")
     NETVAR(bool,        m_bIsDefusing,      "DT_BasePlayer", "m_bIsDefusing")
     NETVAR(int32_t,     m_nTickBase,        "DT_BasePlayer", "m_nTickBase")
     NETVAR(float,       m_flFallVelocity,   "DT_BasePlayer", "m_flFallVelocity")
     PNETVAR(int32_t,    m_nNextThinkTick,   "DT_BasePlayer", "m_nNextThinkTick")
     NETVAR(Vec3,        m_angEyeAngles,     "DT_CSPlayer",   "m_angEyeAngles")
     PNETVAR(Vec3,       m_angEyeAnglesP,    "DT_CSPlayer",   "m_angEyeAngles")
     NETVAR(EHandle<BaseCombatWeapon>, m_hActiveWeapon, "DT_BaseCombatCharacter", "m_hActiveWeapon");


     /* VTABLE FUNCTIONS */
     __forceinline void PreThink() { Memory::CallVirtual<void>(this, (int) BasePlayerVFunc::PreThink); }
     __forceinline void Think() { Memory::CallVirtual<void>(this, (int) BasePlayerVFunc::Think); }
     __forceinline void UpdateCollisionBounds() { Memory::CallVirtual<void>(this, (int) BasePlayerVFunc::UpdateCollisionBounds); }
     __forceinline void StudioFrameAdvance() { Memory::CallVirtual<void>(this, (int) BasePlayerVFunc::StudioFrameAdvance); }
     __forceinline void SetSequence(int32_t seq)
     {
          typedef void *(__thiscall* tSetSequence)(void*, int32_t);
          Memory::CallVirtual<tSetSequence>(this, (int) BasePlayerVFunc::SetSequence)(this, seq);
     }

     /* FUNCTIONS */
     CUserCmd** GetCurrentCommand();
     CUserCmd& GetLastCommand();

     int GetButtonDisabled();
     int GetButtonForced();

     void PostThink();
     bool PhysicsRunThink(int think_method);
     
     /* CUSTOM IMPLEMENTATIONS */
     __forceinline bool IsAlive() { return m_lifeState() == 0; }

     const char* GetRank();
};
