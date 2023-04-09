#pragma once
#include "IClientNetworkable.h"
#include "IClientRenderable.h"
#include "IClientThinkable.h"
#include "IClientUnknown.h"

#include "../Geometry/Vector/Vec3.h"

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
    virtual void Release() = 0;
    
    virtual const Vec3&	GetAbsOrigin() const = 0;
    virtual const Vec3&	GetAbsAngles() const = 0;
};
