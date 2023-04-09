#include "pch.h"
#include "PlayerList.h"

#include "Framework/imgui/imgui.h"
#include "Implementation/CallbackManager/CallbackManager.h"
#include "Implementation/Menu/MenuManager.h"
#include "ValveSDK/ValveSDK.h"
#include "ValveSDK/Classes/BaseEntity.h"

namespace PlayerList
{
    struct PlayerRecord {
        BaseEntity* player;
        std::string name;
        int dmg_to_ally;
    };
    
    std::vector<PlayerRecord> player_records{ };

    PlayerRecord* GetRecord(BaseEntity* entity)
    {
        for(auto& record : player_records)
        {
            if(record.player == entity)
                return &record;
        }

        return nullptr;
    }

    namespace Menu
    {
        bool enable = false;
    }
    
    void Initialize()
    {
        CallbackManager::AddCallback(CallbackType::OnPreFrameRenderStart, OnUpdate);
        CallbackManager::AddCallback(CallbackType::OnDraw, OnDraw);
        CallbackManager::AddCallback(CallbackType::OnFireEvent, OnFireEvent);

        const auto menu = MenuManager::CreateMenu("Player list", false);
        menu->AddBoolean("Enable", &Menu::enable);
    }

    void Delete()
    {
        CallbackManager::RemoveCallback(CallbackType::OnPreFrameRenderStart, OnUpdate);
        CallbackManager::RemoveCallback(CallbackType::OnDraw, OnDraw);
        CallbackManager::RemoveCallback(CallbackType::OnFireEvent, OnFireEvent);
    }

    void OnUpdate()
    {
        if(!g_engine->IsInGame() || !g_engine->IsConnected() || !Menu::enable)
            return;
        
        for(int i = 0; i < g_engine->GetMaxClients(); i++)
        {
            if(i > 64)
                continue;

            BaseEntity* entity = g_entitylist->GetClientEntity(i);
            if(!entity)
                continue;

            bool record_exists = false;
            for(const auto& record : player_records)
            {
                if(record.player == entity)
                {
                    record_exists = true;
                    break;
                }
            }

            if(record_exists)
                continue;

            player_info_t player_info;
            if(!g_engine->GetPlayerInfo(i, &player_info))
                continue;

            std::string player_name = player_info.name;
            if(player_info.is_fake_player)
                player_name = "[BOT] " + player_name;
            
            player_records.push_back({ entity, player_name, entity->IsAlly() });
        }
    }

    void OnFireEvent(IGameEvent* event)
    {
        if(!g_engine->IsConnected() || !Menu::enable)
            return;
        
        if(!strcmp(event->GetName(), "round_start"))
        {
            player_records.clear();
        }
        
        if(!strcmp(event->GetName(), "player_hurt"))
        {
            BaseEntity* target = g_entitylist->GetClientEntity(g_engine->GetPlayerForUserID(event->GetInt("userid")));
            BaseEntity* attacker = g_entitylist->GetClientEntity(g_engine->GetPlayerForUserID(event->GetInt("attacker")));

            if(!target || !attacker)
                return;
            
            if(attacker->IsAlly() && target->IsAlly())
            {
                const auto record = GetRecord(attacker);
                if(record)
                    record->dmg_to_ally += event->GetInt("dmg_health");
            }
        }
    }

    void OnDraw()
    {
        if(!g_engine->IsInGame() || !g_engine->IsConnected() || !Menu::enable)
            return;

        ImGui::SetNextWindowSize({ 600, 0.f });
        if(ImGui::Begin("Players", nullptr, ImGuiWindowFlags_NoResize))
        {
            if(ImGui::BeginTable("##playerlist", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
            {
                ImGui::TableSetupColumn("Name");
                ImGui::TableSetupColumn("Damage to allies");
                
                for(const auto& [player, name, dmg_to_ally] : player_records)
                {
                    if(!player->IsAlly())
                        continue;
                    
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::TextColored(ImColor(255, 255 ,255), name.c_str());
                    ImGui::TableNextColumn();
                    
                    // prevent editing from UI
                    int tmp_value = dmg_to_ally;
                    ImGui::SliderInt("##DamageToAlly", &tmp_value, 0, 300);
                }

                for(const auto& [player, name, dmg_to_ally] : player_records)
                {
                    if(player->IsAlly())
                        continue;
                    
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::TextColored(ImColor(255, 0, 0), name.c_str());
                    ImGui::TableNextColumn();
                }
                
                ImGui::EndTable();
            }

            ImGui::End();
        }
    }
}
