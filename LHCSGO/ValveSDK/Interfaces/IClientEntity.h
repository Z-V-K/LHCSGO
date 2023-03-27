#pragma once
#include "IClientNetworkable.h"
#include "IClientRenderable.h"
#include "IClientThinkable.h"
#include "IClientUnknown.h"

#include "../Geometry/Vector/Vec3.h"

class MouthInfo;
struct SpatializationInfo_t;

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
    virtual void Release() = 0;
    
    virtual const Vec3&	GetAbsOrigin() const = 0;
    virtual const Vec3&	GetAbsAngles() const = 0;

    virtual MouthInfo *GetMouth() = 0;
    
    virtual bool GetSoundSpatialization(SpatializationInfo_t& info) = 0;

    virtual bool IsBlurred() = 0;
};
