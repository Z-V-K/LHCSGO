#pragma once

#include "ValveSDK/Geometry/Vector/Vec2.h"
#include "ValveSDK/Misc/ISurfaceColor.h"

namespace Renderer
{
    inline unsigned long tahoma = 0;

    inline bool initialized = false;
    
    void SetupFonts();
    void DrawText(const std::string_view& text, const ISurfaceColor& color, const Vec2& screen_pos);
    void DrawFilledRect(const Vec2& pos_start, const Vec2& pos_end, const ISurfaceColor& color);
    void DrawOutlinedRect(const Vec2& pos_start, const Vec2& pos_end, const ISurfaceColor& color);
    void DrawLine(const Vec2& pos_start, const Vec2& pos_end, const ISurfaceColor& color);
    Vec2 GetTextSize(const std::string_view& text);
};