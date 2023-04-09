#include "pch.h"
#include "Math.h"

#include "ValveSDK/ValveSDK.h"

namespace Math
{
    void VectorTransform(const Vec3& v_in, const Matrix3x4& m_in, Vec3& out)
    {
        out.x = v_in.Dot(m_in[0]) + m_in[0][3];
        out.y = v_in.Dot(m_in[1]) + m_in[1][3];
        out.z = v_in.Dot(m_in[2]) + m_in[2][3];
    }
    
    bool ScreenTransform(const Vec3& v_in, Vec3& v_out)
    {
        static auto& w2sMatrix = g_engine->WorldToScreenMatrix();

        v_out.x = w2sMatrix.m[0][0] * v_in.x + w2sMatrix.m[0][1] * v_in.y + w2sMatrix.m[0][2] * v_in.z + w2sMatrix.m[0][3];
        v_out.y = w2sMatrix.m[1][0] * v_in.x + w2sMatrix.m[1][1] * v_in.y + w2sMatrix.m[1][2] * v_in.z + w2sMatrix.m[1][3];
        v_out.z = 0.0f;

        float w = w2sMatrix.m[3][0] * v_in.x + w2sMatrix.m[3][1] * v_in.y + w2sMatrix.m[3][2] * v_in.z + w2sMatrix.m[3][3];

        if(w < 0.001f) {
            v_out.x *= 100000;
            v_out.y *= 100000;
            return false;
        }

        v_out.x /= w;
        v_out.y /= w;

        return true;
    }

    bool WorldToScreen(const Vec3& v_in, Vec3& v_out)
    {
        if(ScreenTransform(v_in, v_out)) {
            int w, h;
            g_engine->GetScreenSize(w, h);

            v_out.x = (w / 2.0f) + (v_out.x * w) / 2.0f;
            v_out.y = (h / 2.0f) - (v_out.y * h) / 2.0f;

            return true;
        }
        return false;
    }

}
