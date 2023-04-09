#pragma once

enum EntryType
{
    Checkbox,
    Slider,
    List
};

class MenuEntry
{
protected:
    std::string name;
    EntryType type;
public:
    MenuEntry(const std::string_view& name, const EntryType type) : name(name), type(type) { }
    
    virtual void Draw(const int base_height, const int value_x) = 0;

    __forceinline std::string GetName() { return name; }
    __forceinline EntryType GetType() { return type; }
};

class MenuBoolean : public MenuEntry
{
public:
    bool* value;

    MenuBoolean(const std::string_view& name, bool* value) :
        MenuEntry(name, Checkbox),
        value(value)
    { }
        

    void Draw(const int base_height, const int value_x) override;
};

class MenuSlider : public MenuEntry
{
public:
    int min_value;
    int max_value;
    int* value;

    MenuSlider(const std::string_view& name, int* value, const int min_value, const int max_value) :
        MenuEntry(name, Slider),
        value(value),
        min_value(min_value),
        max_value(max_value)
    { }
    
    void Draw(const int base_height, const int value_x) override;
};

class MenuList : public MenuEntry
{
public:
    std::vector<std::string_view> values;
    int* value;
    
    MenuList(const std::string_view& name, int* value, const std::vector<std::string_view>& values) :
        MenuEntry(name, List),
        value(value),
        values(values)
    { }
    
    void Draw(const int base_height, const int value_x) override;
};