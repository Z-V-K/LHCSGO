#pragma once
#include "MenuEntry.h"

class Menu
{
private:
    int ENTRY_HEIGHT = 14;
    std::vector<MenuEntry*> entries;
    std::string name;
    int longest_entry_name = 0;
    bool open;
public:

    Menu(const std::string_view& name, const bool open) : name(name), open(open) { }

    ~Menu()
    {
        for(const auto& e : entries)
            delete e;

        entries.clear();
    }

    void AddBoolean(const std::string_view& name, bool* value);
    void AddSlider(const std::string_view& name, int* value, const int min_value, const int max_value);
    void AddList(const std::string_view& name, int* value, const std::vector<std::string_view>& values);

    void UpdateLongestName(const std::string_view& name);
    
    int GetHeight();
    void Draw(const int base_height);

    __forceinline bool IsOpen() { return open; }
    __forceinline void SetOpen(bool b) { open = b; }
    
    __forceinline std::vector<MenuEntry*> GetEntries() { return entries; }
};
