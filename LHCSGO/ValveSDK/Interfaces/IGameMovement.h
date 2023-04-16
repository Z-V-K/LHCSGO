#pragma once
#include "ValveSDK/Classes/BaseEntity.h"
#include "ValveSDK/Classes/MoveData.h"

class IGameMovement
{
public:
    virtual						~IGameMovement() { }
    virtual void				ProcessMovement(BaseEntity* pEntity, MoveData* pMove) = 0;
    virtual void				Reset() = 0;
    virtual void				StartTrackPredictionErrors(BaseEntity* pEntity) = 0;
    virtual void				FinishTrackPredictionErrors(BaseEntity* pEntity) = 0;
    virtual void				DiffPrint(char const* fmt, ...) = 0;
    virtual Vec3 const&		    GetPlayerMins(bool bDucked) const = 0;
    virtual Vec3 const&		    GetPlayerMaxs(bool bDucked) const = 0;
    virtual Vec3 const&		    GetPlayerViewOffset(bool bDucked) const = 0;
    virtual bool				IsMovingPlayerStuck() const = 0;
    virtual BaseEntity*		    GetMovingPlayer() const = 0;
    virtual void				UnblockPusher(BaseEntity* pEntity, BaseEntity* pPusher) = 0;
    virtual void				SetupMovementBounds(MoveData* pMove) = 0;
};
