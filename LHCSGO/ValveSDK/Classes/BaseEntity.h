#pragma once
#include "../Interfaces/IClientEntity.h"
#include "../NetvarManager.h"
#include "Framework/Memory/Memory.h"
#include "ValveSDK/ValveSDK.h"
#include "ValveSDK/Misc/VFunctionIndexes.h"

class BaseEntity : public IClientEntity
{
public:
    __forceinline bool IsPlayer(){ return Memory::CallVirtual<bool>(this, BaseEntityVFunc::IsPlayer); }
    __forceinline bool IsWeapon(){ return Memory::CallVirtual<bool>(this, BaseEntityVFunc::IsWeapon); }

    NETVAR(int32_t, model_index, "CBasePlayer", "m_nModelIndex")
    NETVAR(int32_t, team_num, "CBasePlayer", "m_iTeamNum")
    NETVAR(Vec3, vec_origin, "CBasePlayer", "m_vecOrigin")

    /* CUSTOM IMPLMENTATIONS */
    __forceinline bool IsAlly() const { return g_localplayer->team_num() == team_num(); }
};