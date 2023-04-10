#include "pch.h"
#include "Vec3.h"

#include "ValveSDK/Misc/Math.h"

Vec3 Vec3::AngleVectors()
{
    float	sp, sy, cp, cy;
    Vec3    ret;

    sy = sin(Math::Deg2Rad(y));
    cy = cos(Math::Deg2Rad(y));

    sp = sin(Math::Deg2Rad(x));
    cp = cos(Math::Deg2Rad(x));

    ret.x = cp * cy;
    ret.y = cp * sy;
    ret.z = -sp;

    return ret;
}
