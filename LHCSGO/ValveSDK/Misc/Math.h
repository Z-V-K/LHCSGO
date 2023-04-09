#pragma once
#include "ValveSDK/Interfaces/IEngineClient.h"

namespace Math
{
    void VectorTransform(const Vec3& v_in, const Matrix3x4& m_in, Vec3& out);
    bool WorldToScreen(const Vec3& v_in, Vec3& v_out);
}
