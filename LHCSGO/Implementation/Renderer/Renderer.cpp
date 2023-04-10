#include "pch.h"
#include "Renderer.h"

#include "ValveSDK/ValveSDK.h"

namespace Renderer
{
    void SetupFonts()
    {
        tahoma = g_surface->CreateFont_();
        g_surface->SetFontGlyphSet(tahoma, "Tahoma", 12, FW_BOLD, NULL, NULL, FONTFLAG_OUTLINE);

        initialized = true;
    }

    void DrawText(const std::string_view& text, const ISurfaceColor& color, const Vec2& screen_pos)
    {
        g_surface->DrawSetTextPos(screen_pos.x, screen_pos.y);
        g_surface->DrawSetTextFont(tahoma);
        g_surface->DrawSetTextColor(color);
    
        wchar_t szString[1024] = { '\0' };
        wsprintfW(szString, L"%S", text.data());
        
        g_surface->DrawPrintText(szString, wcslen(szString));
    }

    void DrawFilledRect(const Vec2& pos_start, const Vec2& pos_end, const ISurfaceColor& color)
    {
        g_surface->DrawSetColor(color);
        g_surface->DrawFilledRect((int) pos_start.x, (int) pos_start.y, (int) pos_end.x, (int) pos_end.y);
    }

    void DrawOutlinedRect(const Vec2& pos_start, const Vec2& pos_end, const ISurfaceColor& color)
    {
        g_surface->DrawSetColor(color);
        g_surface->DrawOutlinedRect((int) pos_start.x, (int) pos_start.y, (int) pos_end.x, (int) pos_end.y);
    }

    void DrawLine(const Vec2& pos_start, const Vec2& pos_end, const ISurfaceColor& color)
    {
        g_surface->DrawSetColor(color);
        g_surface->DrawLine((int) pos_start.x, (int) pos_start.y, (int) pos_end.x, (int) pos_end.y);
    }

    void DrawCircle(const Vec2& pos, const int radius, const ISurfaceColor& color)
    {
        g_surface->DrawSetColor(color);
        g_surface->DrawOutlinedCircle(pos.x, pos.y, (int)radius, 50);
    }
    
    Vec2 GetTextSize(const std::string_view& text)
    {
        wchar_t szString[1024] = { '\0' };
        wsprintfW(szString, L"%S", text.data());

        int x, y;
        g_surface->GetTextSize(tahoma, szString, x, y);
        
        return Vec2(x, y);
    }
}
