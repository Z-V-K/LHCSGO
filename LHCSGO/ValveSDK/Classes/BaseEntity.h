#pragma once
#include "../Interfaces/IClientEntity.h"
#include "../NetvarManager.h"
#include "Framework/Memory/Memory.h"
#include "ValveSDK/ValveSDK.h"
#include "ValveSDK/Misc/VFunctionIndexes.h"
#include "ValveSDK/Classes/EHandle.h"

class BaseEntity : public IClientEntity
{
public:
    __forceinline bool IsPlayer(){ return Memory::CallVirtual<bool>(this, (int) BaseEntityVFunc::IsPlayer); }

    NETVAR(int32_t, m_flSimulationTime, "DT_BaseEntity", "m_flSimulationTime")
    NETVAR(int32_t, m_ubInterpolationFrame, "DT_BaseEntity", "m_ubInterpolationFrame")
    NETVAR(Vec3, m_vecOrigin, "DT_BaseEntity", "m_vecOrigin")
    NETVAR(Vec3, m_angRotation, "DT_BaseEntity", "m_angRotation")
    NETVAR(int32_t, m_nModelIndex, "DT_BaseEntity", "m_nModelIndex")
    NETVAR(int32_t, m_fEffects, "DT_BaseEntity", "m_fEffects")
    NETVAR(int32_t, m_nRenderMode, "DT_BaseEntity", "m_nRenderMode")
    NETVAR(int32_t, m_nRenderFX, "DT_BaseEntity", "m_nRenderFX")
    NETVAR(int32_t, m_clrRender, "DT_BaseEntity", "m_clrRender")
    NETVAR(int32_t, m_iTeamNum, "DT_BaseEntity", "m_iTeamNum")
    NETVAR(int32_t, m_CollisionGroup, "DT_BaseEntity", "m_CollisionGroup")
    NETVAR(float, m_flElasticity, "DT_BaseEntity", "m_flElasticity")
    NETVAR(float, m_flShadowCastDistance, "DT_BaseEntity", "m_flShadowCastDistance")
    NETVAR(EHandle<BaseEntity*>, m_hOwnerEntity, "DT_BaseEntity", "m_hOwnerEntity")
    NETVAR(int32_t, m_hEffectEntity, "DT_BaseEntity", "m_hEffectEntity")
    NETVAR(Vec3, m_vecVelocity, "DT_BaseEntity", "m_vecVelocity[0]")
    
    /* CUSTOM IMPLEMENTATIONS */
    __forceinline Matrix3x4& m_rgflCoordinateFrame()
    {
        static uint32_t offset = NetvarManager::GetOffset("DT_BaseEntity", "m_CollisionGroup") - 0x30;
        return *reinterpret_cast<Matrix3x4*>((uintptr_t) this + offset);
    }

    bool IsAlly() const;
    bool IsWeapon();
    bool IsDefuseKit();
    bool IsDroppedBomb();
};