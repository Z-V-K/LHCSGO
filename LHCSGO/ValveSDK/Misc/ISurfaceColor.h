#pragma once

class ISurfaceColor
{
    unsigned char color[4];
    
public:
    ISurfaceColor() { *(int*) color = 0; }
    ISurfaceColor(int r, int g, int b, int a = 255) { SetColor(r, g, b, a); }
    ISurfaceColor(float r, float g, float b, float a = 1.f) { SetColor(255 * r, 255 * g, 255 * b, 255 * a); }
    ISurfaceColor(unsigned long argb)
    {
        color[2] = (unsigned char)((argb & 0x000000FF) >> (0 * 8));
        color[1] = (unsigned char)((argb & 0x0000FF00) >> (1 * 8));
        color[0] = (unsigned char)((argb & 0x00FF0000) >> (2 * 8));
        color[3] = (unsigned char)((argb & 0xFF000000) >> (3 * 8));
    }
    
    void SetColor(int r, int g, int b, int a) { color[0] = r; color[1] = g; color[2] = b; color[3] = a; }
    
    static ISurfaceColor GREEN;
    static ISurfaceColor RED;
    static ISurfaceColor WHITE;
    static ISurfaceColor BLACK;
    static ISurfaceColor BLUE;
    static ISurfaceColor PINK;
};