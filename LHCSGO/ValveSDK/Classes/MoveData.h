#pragma once
#include "ValveSDK/Geometry/Vector/Vec3.h"

class MoveData
{
public:
    bool			bFirstRunOfFunctions : 1;
    bool			bGameCodeMovedPlayer : 1;
    bool			bNoAirControl : 1;
    std::uintptr_t	hPlayerHandle;		// edict index on server, client entity handle on client=
    int				nImpulseCommand;	// impulse command issued.
    Vec3			angViewAngles;		// command view angles (local space)
    Vec3			angAbsViewAngles;	// command view angles (world space)
    int				nButtons;			// attack buttons.
    int				nOldButtons;		// from host_client->oldbuttons;
    float			flForwardMove;
    float			flSideMove;
    float			flUpMove;
    float			flMaxSpeed;
    float			flClientMaxSpeed;
    Vec3			vecVelocity;		// edict::velocity	// current movement direction.
    Vec3			vecTrailingVelocity;
    float			flTrailingVelocityTime;
    Vec3			vecAngles;			// edict::angles
    Vec3			vecOldAngles;
    float			flOutStepHeight;	// how much you climbed this move
    Vec3			vecOutWishVel;		// this is where you tried 
    Vec3			vecOutJumpVel;		// this is your jump velocity
    Vec3			vecConstraintCenter;
    float			flConstraintRadius;
    float			flConstraintWidth;
    float			flConstraintSpeedFactor;
    bool			bConstraintPastRadius;
    Vec3			vecAbsOrigin;
};
