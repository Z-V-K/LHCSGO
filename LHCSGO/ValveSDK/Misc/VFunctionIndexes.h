#pragma once

enum class BaseEntityVFunc
{
    Collideable = 3,
    IsPlayer = 157,
    IsWeapon = 166,
};

enum class BasePlayerVFunc
{
    Think = 139,
    SetSequence = 219,
    StudioFrameAdvance = 220,
    PreThink = 318,
    UpdateCollisionBounds = 340,
};

enum class VGuiPanelVFunc
{
    GetName = 36,
    GetClassName = 37
};