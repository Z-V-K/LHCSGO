#include "pch.h"
#include "MenuManager.h"

#include "Implementation/Renderer/Renderer.h"
#include "ValveSDK/ValveSDK.h"
#include "ValveSDK/Classes/BasePlayer.h"
#include "ValveSDK/Interfaces/IEngineClient.h"

namespace MenuManager
{
    bool initialized = false;
    Vec2 screen_size;
    
    void DrawPermashow();
    
    Menu* CreateMenu(const std::string_view& name, const bool open)
    {
        Menu* new_menu = new Menu(name, open);
        menus.push_back(new_menu);

        return new_menu;
    }

    void Initialize()
    {
        int w, h;
        g_engine->GetScreenSize(w, h);

        screen_size = Vec2(w, h);
        menu_x_pos = (screen_size.x / 2) - 50;

        initialized = true;
    }

    void OnUpdate()
    {
    }
    
    void OnDraw()
    {
        if(!initialized || screen_size.x < 1)
            Initialize();
        
        if(g_engine->IsInGame())
            DrawPermashow();
        
        if(!menu_open)
            return;

        int initial_height = (screen_size.y / 2) - 100;
        int height = initial_height;
        
        for (const auto& menu : menus)
        {
            menu->Draw(height);
            height += menu->GetHeight();
        }
        
        Vec2 base_caret_pos{ menu_x_pos - 8, initial_height + (cursor_index * 14) + 1};
        
        Renderer::DrawFilledRect( base_caret_pos, base_caret_pos + Vec2(4, 11), { 255, 0, 0 });
    }

    int CalcMaxMenuIndex()
    {
        int idx = 0;
        for(const auto& menu : menus)
        {
            menu->IsOpen() ? idx += menu->GetEntries().size() + 1 : idx += 1;
        }
        
        return idx - 1;
    }

    void HandleAction(WPARAM wParam)
    {
        int idx = 0;
        for(const auto& menu : menus)
        {
            if(idx == cursor_index)
            {
                menu->SetOpen(!menu->IsOpen());
                return;
            }
            
            if(!menu->IsOpen())
            {
                idx++;
                continue;
            }

            for(auto& entry : menu->GetEntries())
            {
                idx++;
                if(idx == cursor_index)
                {
                    switch (entry->GetType())
                    {
                        case Checkbox: {
                                
                            if (wParam != VK_RETURN)
                                return;
                            
                            MenuBoolean* cb = (MenuBoolean*) entry;
                            *cb->value = !(*cb->value);
                            break;
                        }
                        case Slider: {
                            MenuSlider* slider = (MenuSlider*) entry;
                            if (wParam == VK_LEFT && *slider->value > slider->min_value)
                                *slider->value = *slider->value - 1;
                            if (wParam == VK_RIGHT && *slider->value < slider->max_value)
                                *slider->value = *slider->value + 1;
                            break;
                        }
                        case List: {
                            MenuList* list = (MenuList*) entry;
                            if(wParam == VK_LEFT && *list->value > 0)
                                *list->value = *list->value - 1;
                            if(wParam == VK_RIGHT && *list->value < list->values.size() - 1)
                                *list->value = *list->value + 1;
                            break;
                        }
                    }
                    return;
                }
            }

            idx++;
        }
    }

    void OnWndProc(UINT uMsg, WPARAM wParam)
    {        
        if(uMsg != WM_KEYUP)
            return;

        if(wParam == VK_INSERT)
            menu_open = !menu_open;
        
        if(!menu_open)
            return;
            
        switch(wParam)
        {
        case VK_UP:
            if(cursor_index > 0)
                cursor_index--;
            break;
        case VK_DOWN:
            if(cursor_index < CalcMaxMenuIndex())
                cursor_index++;
            break;
        case VK_RETURN:
        case VK_LEFT:
        case VK_RIGHT:
            HandleAction(wParam);
            break;
        }
    }
    
    void DrawPermashow()
    {
        static Vec2 base_pos { 300, 20 };

        Renderer::DrawText("LHCSGO Beta version", ISurfaceColor::PINK, base_pos - Vec2(0, 12));

        char buff[64];
        sprintf(buff, "localplayer 0x%p", g_localplayer);
        Renderer::DrawText(buff, ISurfaceColor::WHITE, base_pos - Vec2(- 130, 12));

        player_info_t player_info;
        g_engine->GetPlayerInfo(g_localplayer->EntIndex(), &player_info);
        Renderer::DrawText(player_info.name, ISurfaceColor::WHITE, base_pos + Vec2(130, 0));
    }
    
}
