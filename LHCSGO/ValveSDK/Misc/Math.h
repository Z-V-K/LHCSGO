#pragma once
#include "ValveSDK/Interfaces/IEngineClient.h"

namespace Math
{
    void VectorTransform(const Vec3& v_in, const Matrix3x4& m_in, Vec3& out);
    bool WorldToScreen(const Vec3& v_in, Vec3& v_out);

    __forceinline double Deg2Rad(double deg) {
        return deg * M_PI / 180.0;
    }
}
