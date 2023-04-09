#include "pch.h"
#include "MenuEntry.h"

#include "MenuManager.h"
#include "Implementation/Renderer/Renderer.h"

constexpr int ENTRY_X_OFFSET = 8;

void MenuBoolean::Draw(const int base_height, const int value_x)
{
	Renderer::DrawText(name, { 255, 255, 255 }, { MenuManager::menu_x_pos + ENTRY_X_OFFSET, base_height });
	Renderer::DrawText(*value ? "true" : "false", *value ? ISurfaceColor::GREEN : ISurfaceColor::RED, {  MenuManager::menu_x_pos + value_x + ENTRY_X_OFFSET, base_height });
}

void MenuSlider::Draw(const int base_height, const int value_x)
{
	Renderer::DrawText(name, { 255, 255, 255 }, { MenuManager::menu_x_pos + ENTRY_X_OFFSET, base_height });
	Renderer::DrawText(std::to_string(*value), ISurfaceColor::WHITE, {  MenuManager::menu_x_pos + value_x + ENTRY_X_OFFSET, base_height });
}

void MenuList::Draw(const int base_height, const int value_x)
{
	Renderer::DrawText(name, { 255, 255, 255 }, { MenuManager::menu_x_pos + ENTRY_X_OFFSET, base_height });
	Renderer::DrawText(values[*value], ISurfaceColor::WHITE, { MenuManager::menu_x_pos + value_x + ENTRY_X_OFFSET, base_height });
}