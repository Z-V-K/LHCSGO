#pragma once

#include "BaseAttributableItem.h"

class BaseCombatWeapon : public BaseAttributableItem
{
public:
    NETVAR(int32_t, m_nExplodeEffectTickBegin, "DT_BaseCSGrenadeProjectile", "m_nExplodeEffectTickBegin")
};
