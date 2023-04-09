#pragma once
#include "ValveSDK/Geometry/Vector/Vec3.h"

class ICollideable
{
public:
    virtual IHandleEntity*      GetEntityHandle() = 0;
    virtual Vec3&               OBBMins() const = 0;
    virtual Vec3&               OBBMaxs() const = 0;
};
