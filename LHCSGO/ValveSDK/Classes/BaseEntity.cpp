#include "pch.h"
#include "BaseEntity.h"

#include "BasePlayer.h"

bool BaseEntity::IsAlly() const
{
    return m_iTeamNum() == g_localplayer->m_iTeamNum();
}

bool BaseEntity::IsWeapon()
{
    const ClassId class_id = GetClientClass()->m_ClassID;
    
    return class_id == (int)ClassId_CAK47 ||
    class_id == (int)ClassId_CDEagle ||
    class_id == (int)ClassId_CKnife ||
    class_id == (int)ClassId_CKnifeGG ||
    class_id == (int)ClassId_CWeaponAug ||
    class_id == (int)ClassId_CWeaponAWP ||
    class_id == (int)ClassId_CWeaponBizon ||
    class_id == (int)ClassId_CWeaponElite ||
    class_id == (int)ClassId_CWeaponFiveSeven ||
    class_id == (int)ClassId_CWeaponG3SG1 ||
    class_id == (int)ClassId_CWeaponG3SG1 ||
    class_id == (int)ClassId_CWeaponGalilAR ||
    class_id == (int)ClassId_CWeaponGlock ||
    class_id == (int)ClassId_CWeaponHKP2000 ||
    class_id == (int)ClassId_CWeaponM249 ||
    class_id == (int)ClassId_CWeaponM4A1 ||
    class_id == (int)ClassId_CWeaponMag7 ||
    class_id == (int)ClassId_CWeaponMP7 ||
    class_id == (int)ClassId_CWeaponMP9 ||
    class_id == (int)ClassId_CWeaponNegev ||
    class_id == (int)ClassId_CWeaponNOVA ||
    class_id == (int)ClassId_CWeaponP250 ||
    class_id == (int)ClassId_CWeaponP90 ||
    class_id == (int)ClassId_CWeaponBizon ||
    class_id == (int)ClassId_CWeaponSCAR20 ||
    class_id == (int)ClassId_CWeaponSG556 ||
    class_id == (int)ClassId_CWeaponSSG08 ||
    class_id == (int)ClassId_CWeaponTaser ||
    class_id == (int)ClassId_CWeaponTec9 ||
    class_id == (int)ClassId_CWeaponUMP45 ||
    class_id == (int)ClassId_CWeaponXM1014 ||
    class_id == (int)ClassId_CDecoyGrenade ||
    class_id == (int)ClassId_CHEGrenade ||
    class_id == (int)ClassId_CIncendiaryGrenade ||
    class_id == (int)ClassId_CMolotovGrenade ||
    class_id == (int)ClassId_CSmokeGrenade ||
    class_id == (int)ClassId_CFlashbang;
}

bool BaseEntity::IsDefuseKit()
{
    const auto model = GetModel();
    if (!model)
        return false;

    return !strcmp(model->szName, "models/weapons/w_defuser.mdl");
}

bool BaseEntity::IsDroppedBomb()
{
    const auto model = GetModel();
    if (!model)
        return false;

    return !strcmp(model->szName, "models/weapons/w_ied_dropped.mdl");
}