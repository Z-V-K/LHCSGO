#include "pch.h"
#include "Menu.h"

#include "MenuManager.h"
#include "Implementation/Renderer/Renderer.h"

void Menu::AddBoolean(const std::string_view& name, bool* value)
{
    entries.push_back(new MenuBoolean(name, value));
    UpdateLongestName(name);
}

void Menu::AddSlider(const std::string_view& name, int* value, const int min_value, const int max_value)
{
    entries.push_back(new MenuSlider(name, value, min_value, max_value));
    UpdateLongestName(name);
}

void Menu::AddList(const std::string_view& name, int* value, const std::vector<std::string_view>& values)
{
    entries.push_back(new MenuList(name, value, values));
    UpdateLongestName(name);
}

int Menu::GetHeight()
{
   return open ? ENTRY_HEIGHT * entries.size() + ENTRY_HEIGHT : ENTRY_HEIGHT;
}

void Menu::UpdateLongestName(const std::string_view& name)
{
    const Vec2 entry_name_size = Renderer::GetTextSize(name);

    if(entry_name_size.x > longest_entry_name)
        longest_entry_name = entry_name_size.x;
}

void Menu::Draw(const int base_height)
{
    const std::string menu_header = (open ? "[-]" : "[+]") + std::string(" ") + name;
    Renderer::DrawText(menu_header, { 255, 255, 255 }, { MenuManager::menu_x_pos, base_height });

    if(open)
    {
        int entry_base_height = base_height + ENTRY_HEIGHT;
        for (const auto& entry : entries)
        {
            entry->Draw(entry_base_height, longest_entry_name + 12);
            entry_base_height += ENTRY_HEIGHT;
        }     
    }
}