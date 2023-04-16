#include "pch.h"
#include "PlayerList.h"

#include "Framework/imgui/imgui.h"
#include "Implementation/CallbackManager/CallbackManager.h"
#include "Implementation/Menu/MenuManager.h"
#include "Implementation/Renderer/Renderer.h"
#include "ValveSDK/ValveSDK.h"
#include "ValveSDK/Classes/BaseEntity.h"
#include "ValveSDK/Classes/BasePlayer.h"

namespace PlayerList
{
    struct PlayerRecord {
        BasePlayer* player;
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

    void PlayerList();
    void SpectatorList();

    namespace Menu
    {
        bool enable = false;
        bool spectator_list = true;
    }
    
    void Initialize()
    {
        CallbackManager::AddCallback(CallbackType::OnPreFrameRenderStart, OnUpdate);
        CallbackManager::AddCallback(CallbackType::OnDraw, OnDraw);
        CallbackManager::AddCallback(CallbackType::OnFireEvent, OnFireEvent);
        CallbackManager::AddCallback(CallbackType::OnPaintTraverse, OnDrawSurface);

        const auto menu = MenuManager::CreateMenu("Player list", false);
        // menu->AddBoolean("Enable", &Menu::enable);
        menu->AddBoolean("Spectator list", &Menu::spectator_list);
    }

    void Delete()
    {
        CallbackManager::RemoveCallback(CallbackType::OnPreFrameRenderStart, OnUpdate);
        CallbackManager::RemoveCallback(CallbackType::OnDraw, OnDraw);
        CallbackManager::RemoveCallback(CallbackType::OnPaintTraverse, OnDrawSurface);
        CallbackManager::RemoveCallback(CallbackType::OnFireEvent, OnFireEvent);
    }

    void OnUpdate()
    {
        if(!g_engine->IsInGame() || !g_engine->IsConnected() || (!Menu::enable && !Menu::spectator_list))
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
            
            player_records.push_back({ (BasePlayer*) entity, player_name, entity->IsAlly() });
        }
    }

    void OnFireEvent(IGameEvent* event)
    {
        if (!g_engine->IsConnected() || !g_engine->IsInGame())
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
        if (!g_engine->IsInGame() || !g_engine->IsConnected())
            return;
        
        PlayerList();
    }

    void OnDrawSurface()
    {
        if (!g_engine->IsInGame() || !g_engine->IsConnected())
            return;

        SpectatorList();
    }

    void PlayerList()
    {
        if(!Menu::enable)
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

    void SpectatorList()
    {
        if (!Menu::spectator_list || !g_localplayer->IsAlive())
            return;
            
        Vec2 base_pos = { 20 , 500 };
        Renderer::DrawText("---- Spectators ----", ISurfaceColor::PINK, base_pos);
        base_pos += Vec2{ 0, 14 };
        
        for (const auto& [player, name, dmg_to_ally] : player_records)
        {
            if (!player || player->EntIndex() == g_localplayer->EntIndex() || !player->IsAlly())
                continue;

            const auto obs_target = player->m_hObserverTarget();

            if (!obs_target || obs_target->EntIndex() != g_localplayer->EntIndex())
                continue;
            
            Renderer::DrawText(name, ISurfaceColor::WHITE, base_pos);
            base_pos += Vec2{ 0, 14 };
        }
    }
}
