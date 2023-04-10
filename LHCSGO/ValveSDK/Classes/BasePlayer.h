#pragma once
#include "EHandle.h"
#include "BaseCombatWeapon.h"

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
     NETVAR(Vec3,        m_angEyeAngles,     "DT_CSPlayer",   "m_angEyeAngles")
     PNETVAR(Vec3,        m_angEyeAnglesP,   "DT_CSPlayer",   "m_angEyeAngles")
     
     NETVAR(EHandle<BaseCombatWeapon>, m_hActiveWeapon, "DT_BaseCombatCharacter", "m_hActiveWeapon");

     /* CUSTOM IMPLEMENTATIONS */
     __forceinline bool IsAlive() { return m_lifeState() == 0; }

     const char* GetRank();
};
