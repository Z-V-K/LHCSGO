#pragma once
#include "IClientEntity.h"

class IPhysicsSurfaceProps;
class CGameTrace;

class IMoveHelper
{
public:
    virtual	const char*			GetName(void* hEntity) const = 0;
    virtual void                SetHost(IClientEntity* host) = 0;
    virtual void				ResetTouchList() = 0;
    virtual bool				AddToTouched(const CGameTrace& trace, const Vec3& vecImpactVelocity) = 0;
    virtual void				ProcessImpacts() = 0;
    virtual void				Con_NPrintf(int nIndex, char const* fmt, ...) = 0;
    virtual void				StartSound(const Vec3& vecOrigin, int iChannel, char const* szSample, float flVolume, int soundlevel, int fFlags, int iPitch) = 0;
    virtual void				StartSound(const Vec3& vecOrigin, const char* soundname) = 0;
    virtual void				PlaybackEventFull(int fFlags, int nClientIndex, unsigned short uEventIndex, float flDelay, Vec3& vecOrigin, Vec3& vecAngles, float flParam1, float flParam2, int iParam1, int iParam2, int bParam1, int bParam2) = 0;
    virtual bool				PlayerFallingDamage() = 0;
    virtual void				PlayerSetAnimation(int playerAnimation) = 0;
    virtual IPhysicsSurfaceProps* GetSurfaceProps() = 0;
    virtual bool				IsWorldEntity(const unsigned long& hEntity) = 0;
};
