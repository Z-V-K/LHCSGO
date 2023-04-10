#pragma once
#include "Vec2.h"

class Vec3
{
public:
    float x = 0, y = 0, z = 0;
    
    __forceinline Vec3() = default;
    __forceinline Vec3(const float x, const float y, const float z) { this->x = x; this->y = y; this->z = z; }
    __forceinline Vec3(const float* val) { x = val[0]; y = val[1]; z = val[2]; }
    
    __forceinline bool operator==(const Vec3& src) const { return (src.x == x) && (src.y == y) && (src.z == z); }
    __forceinline bool operator!=(const Vec3& src) const { return (src.x != x) || (src.y != y) || (src.z != z); }
    __forceinline Vec3 operator+(const Vec3& o) const { return { x + o.x, y + o.y, z + o.z }; }
    __forceinline Vec3 operator*(const float o) const { return { x * o, y * o, z * o }; }
    __forceinline operator Vec2() const { return { x, y }; }

    __forceinline float Dot(const Vec3& other) const { return x * other.x + y * other.y + z * other.z; }

    Vec3 AngleVectors();
};
