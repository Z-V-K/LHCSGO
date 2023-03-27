#pragma once

class Vec2
{
public:
    float x = 0, y = 0;
    
    __forceinline Vec2() = default;
    __forceinline Vec2(const float x, const float y) { this->x = x; this->y = y; }
    
    __forceinline bool operator==(const Vec2& src) const { return (src.x == x) && (src.y == y); }
    __forceinline bool operator!=(const Vec2& src) const { return (src.x != x) || (src.y != y); }
};