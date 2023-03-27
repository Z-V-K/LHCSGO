#pragma once

class Vec4
{
public:
    float x = 0, y = 0, z = 0, w = 0;
    
    __forceinline Vec4() = default;
    __forceinline Vec4(const float x, const float y, const float z, const float w = 0) { this->x = x; this->y = y; this->z = z; this->w = w; }
    
    __forceinline bool operator==(const Vec4& src) const { return (src.x == x) && (src.y == y) && (src.z == z) && (src.w == w); }
    __forceinline bool operator!=(const Vec4& src) const { return (src.x != x) || (src.y != y) || (src.z != z) || (src.w != w); }
};
