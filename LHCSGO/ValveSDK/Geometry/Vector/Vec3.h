#pragma once

class Vec3
{
public:
    float x = 0, y = 0, z = 0;
    
    __forceinline Vec3() = default;
    __forceinline Vec3(const float x, const float y, const float z) { this->x = x; this->y = y; this->z = z; }
    __forceinline Vec3(const float* val) { x = val[0]; y = val[1]; z = val[2]; }
    
    __forceinline bool operator==(const Vec3& src) const { return (src.x == x) && (src.y == y) && (src.z == z); }
    __forceinline bool operator!=(const Vec3& src) const { return (src.x != x) || (src.y != y) || (src.z != z); }

    __forceinline float Dot(const Vec3& other) const { return x * other.x + y * other.y + z * other.z; }
};
