#pragma once
#include "Menu.h"

namespace MenuManager
{
    inline std::vector<Menu*> menus { };
    inline int menu_x_pos = 850;
    inline bool menu_open = true;

    inline int cursor_index = 0;

    Menu* CreateMenu(const std::string_view& name, const bool open = true);

    void OnUpdate();
    void OnDraw();
    void OnWndProc(UINT uMsg, WPARAM wParam);
};
