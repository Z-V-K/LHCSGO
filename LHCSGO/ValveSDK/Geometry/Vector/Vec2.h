#pragma once

class Vec2
{
public:
    float x = 0, y = 0;
    
    __forceinline Vec2() = default;
    __forceinline Vec2(const float x, const float y) { this->x = x; this->y = y; }
    __forceinline Vec2(const int x, const int y) { this->x = (float) x, this->y = (float) y; }
    
    __forceinline bool operator==(const Vec2& src) const { return (src.x == x) && (src.y == y); }
    __forceinline bool operator!=(const Vec2& src) const { return (src.x != x) || (src.y != y); }
    
    __forceinline void operator+=(const Vec2& src) { x += src.x; y += src.y; }
    __forceinline Vec2 operator+(const Vec2& src) { return Vec2(x + src.x, y + src.y); }
    __forceinline Vec2 operator-(const Vec2& src) { return Vec2(x - src.x, y - src.y); }
};