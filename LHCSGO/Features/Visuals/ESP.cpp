#include "pch.h"
#include "ESP.h"

#include "Implementation/CallbackManager/CallbackManager.h"
#include "Implementation/Menu/MenuManager.h"
#include "Implementation/Renderer/Renderer.h"
#include "ValveSDK/ValveSDK.h"
#include "ValveSDK/Classes/BaseCombatWeapon.h"
#include "ValveSDK/Classes/BasePlayer.h"
#include "ValveSDK/Misc/Math.h"
#include "ValveSDK/Interfaces/ICollideable.h"

namespace ESP
{
    namespace Menu
    {
        bool enable_ally = false;
        bool enable_enemy = true;
        
        bool bounding_box_ally = true;
        bool bounding_box_enemy = true;

        bool name_ally = false;
        bool name_enemy = true;

        bool bones_ally = false;
        bool bones_enemy = true;
        
        bool weapon_ally = true;
        bool weapon_enemy = true;
    }

    void PlayerESP(BasePlayer* player);
    void BoundingBox(BasePlayer* player, const ISurfaceColor& color, const float right, const float left, const float top, const float bottom);
    void Name(BasePlayer* player, const ISurfaceColor& color, const float left, const float top);
    void Bones(BasePlayer* player, const ISurfaceColor& color);
    void Weapon(BasePlayer* player, const ISurfaceColor& color, const float right, const float top);

    void GrenadeESP(BaseCombatWeapon* grenade);
    
    void Initialize()
    {
        CallbackManager::AddCallback(CallbackType::OnPaintTraverse, OnDraw);
        CallbackManager::AddCallback(CallbackType::OnPreFrameNetUpdateStart, OnUpdate);
        
        const auto menu = MenuManager::CreateMenu("ESP");
        menu->AddBoolean("Enable ally", &Menu::enable_ally);
        menu->AddBoolean("Enable enemy", &Menu::enable_enemy);
        menu->AddBoolean("Bounding box ally", &Menu::bounding_box_ally);
        menu->AddBoolean("Bounding box enemy", &Menu::bounding_box_enemy);
        menu->AddBoolean("Name ally", &Menu::name_ally);
        menu->AddBoolean("Name enemy", &Menu::name_enemy);
        menu->AddBoolean("Bones ally", &Menu::bones_ally);
        menu->AddBoolean("Bones enemy", &Menu::bones_enemy);
        menu->AddBoolean("Weapon ally", &Menu::weapon_ally);
        menu->AddBoolean("Weapon enemy", &Menu::weapon_enemy);
    }

    void Delete()
    {

    }

    void OnDraw()
    {
        if (!g_engine->IsInGame())
            return;
        
        for(int i = 0; i < g_entitylist->GetMaxEntities(); i++)
        {
            const auto entity = g_entitylist->GetClientEntity(i);

            if(!entity)
                continue;

            ClassId class_id = entity->GetClientClass()->m_ClassID;
            
            if (class_id == ClassId_CCSPlayer)
            {
                BasePlayer* player = (BasePlayer*) entity;
                
                if (player->IsAlly() && !Menu::enable_ally)
                    continue;

                if (!player->IsAlly() && !Menu::enable_enemy)
                    continue;
                
                PlayerESP((BasePlayer*) entity);
            }

            if (class_id == ClassId_CDecoyProjectile || class_id == ClassId_CMolotovProjectile || class_id == ClassId_CSmokeGrenadeProjectile || class_id == ClassId_CBaseCSGrenadeProjectile || class_id == ClassId_CSensorGrenadeProjectile)
                GrenadeESP((BaseCombatWeapon*) entity);
        }
    }

    void OnUpdate()
    {

    }

    void PlayerESP(BasePlayer* player)
    {
        if (!player || !player->IsAlive())
            return;

        ICollideable* collideable = player->GetCollideable();
        const Matrix3x4& trans = player->m_rgflCoordinateFrame();

        if (!collideable)
            return;
        
        auto bb_min = collideable->OBBMins();
        auto bb_max = collideable->OBBMaxs();

        Vec3 points[] = {
            Vec3(bb_min.x, bb_min.y, bb_min.z),
            Vec3(bb_min.x, bb_max.y, bb_min.z),
            Vec3(bb_max.x, bb_max.y, bb_min.z),
            Vec3(bb_max.x, bb_min.y, bb_min.z),
            Vec3(bb_max.x, bb_max.y, bb_max.z),
            Vec3(bb_min.x, bb_max.y, bb_max.z),
            Vec3(bb_min.x, bb_min.y, bb_max.z),
            Vec3(bb_max.x, bb_min.y, bb_max.z)
        };

        Vec3 pointsTransformed[8];
        for (int i = 0; i < 8; i++)
        {
            Math::VectorTransform(points[i], trans, pointsTransformed[i]);
        }
        
        Vec3 flb, brt, blb, frt, frb, brb, blt, flt;
        
        if (!Math::WorldToScreen(pointsTransformed[3], flb) || !Math::WorldToScreen(pointsTransformed[5], brt)
        		|| !Math::WorldToScreen(pointsTransformed[0], blb) || !Math::WorldToScreen(pointsTransformed[4], frt)
        		|| !Math::WorldToScreen(pointsTransformed[2], frb) || !Math::WorldToScreen(pointsTransformed[1], brb)
        		|| !Math::WorldToScreen(pointsTransformed[6], blt) || !Math::WorldToScreen(pointsTransformed[7], flt))
        		return;

        Vec3 arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };
 
        float left = flb.x;		// left
        float top = flb.y;		// top
        float right = flb.x;	// right
        float bottom = flb.y;	// bottom
 
        for (int i = 1; i < 8; i++)
        {
            if (left > arr[i].x) 
                left = arr[i].x;
            if (top < arr[i].y) 
                top = arr[i].y;
            if (right < arr[i].x) 
                right = arr[i].x;
            if (bottom > arr[i].y) 
                bottom = arr[i].y;
        }

        const ISurfaceColor bbox_color = player->IsAlly() ? ISurfaceColor::GREEN : ISurfaceColor::RED;
        BoundingBox(player, bbox_color, right, left, top, bottom);

        const ISurfaceColor name_color = bbox_color;
        Name(player, name_color, left, bottom - 16);

        const ISurfaceColor bones_color = ISurfaceColor::WHITE;
        Bones(player, bones_color);

        const ISurfaceColor weapon_color = ISurfaceColor::WHITE;
        Weapon(player, weapon_color, right + 4, bottom - 4);
    }

    void BoundingBox(BasePlayer* player, const ISurfaceColor& color, const float right, const float left, const float top, const float bottom)
    {
        if(player->IsAlly() && !Menu::bounding_box_ally)
            return;

        if(!player->IsAlly() && !Menu::bounding_box_enemy)
            return;

        Renderer::DrawOutlinedRect(Vec2(left + 1, bottom + 1), Vec2(right - 1, top - 1), ISurfaceColor::BLACK);
        Renderer::DrawOutlinedRect(Vec2(left, bottom), Vec2(right, top), color);
        Renderer::DrawOutlinedRect(Vec2(left - 1, bottom - 1), Vec2(right + 1, top + 1), ISurfaceColor::BLACK);
    }

    void Name(BasePlayer* player, const ISurfaceColor& color, const float left, const float top)
    {
        if (player->IsAlly() && !Menu::name_ally)
            return;

        if (!player->IsAlly() && !Menu::name_enemy)
            return;
    
        player_info_t player_info;
        g_engine->GetPlayerInfo(player->EntIndex(), &player_info);

        Renderer::DrawText(player_info.name, color, Vec2(left, top));        
    }

    void Bones(BasePlayer* player, const ISurfaceColor& color)
    {
        if(player->IsAlly() && !Menu::bones_ally)
            return;

        if(!player->IsAlly() && !Menu::bones_enemy)
            return;
        
        studiohdr_t* model = g_modelinfo->GetStudiomodel(player->GetModel());

        if (!model)
            return;

        static Matrix3x4 bones_to_world[128];
        if (!player->SetupBones(bones_to_world, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, g_globalvars->curtime))
            return;

        for (int i = 0; i < model->numbones; i++)
        {
            mstudiobone_t* bone = model->GetBone(i);
            if(!bone || !(bone->flags & BONE_USED_BY_HITBOX) || bone->parent == -1)
                continue;

            Vec3 bonePos1, bonePos2;
            if(!Math::WorldToScreen({ bones_to_world[i][0][3], bones_to_world[i][1][3], bones_to_world[i][2][3] }, bonePos1))
                continue;

            if(!Math::WorldToScreen({ bones_to_world[bone->parent][0][3], bones_to_world[bone->parent][1][3], bones_to_world[bone->parent][2][3] }, bonePos2))
                continue;

            Renderer::DrawLine({ bonePos1.x, bonePos1.y }, { bonePos2.x, bonePos2.y }, color);
        }
    }

    void Weapon(BasePlayer* player, const ISurfaceColor& color, const float right, const float top)
    {
        static std::unordered_map<std::string_view, std::string> sanitized_weapon_names = {
            { "AK47", "AK" },
            { "Aug", "AUG" },
            { "Famas", "Famas" },
            { "GalilAR" , "Galil" },
            { "M4A1", "M4A1" },
            { "SG556", "AUG" },
            { "HKP2000", "USP" },
            { "DEagle", "DEagle" },
            { "P250", "P250" },
            { "Elite", "Dual" },
            { "FiveSeven", "Five seven" },
            { "Glock", "Glock" },
            { "Tec9", "Tec9" },
            { "MAC10", "MAC10" },
            { "MP9", "MP9" },
            { "MP7", "MP7" },
            { "Bizon", "PIPI" },
            { "P90", "P90" },
            { "UMP45", "UMP45" },
            { "Mag7", "Mag7" },
            { "NOVA", "Nova" },
            { "Sawedoff", "Sawed off" },
            { "XM1014", "XM" },
            { "M249", "M249" },
            { "Negev", "Negev" },
            { "AWP", "AWP" },
            { "G3SG1", "G3SG1" },
            { "SCAR20", "SCAR20" },
            { "SSG08", "SCOUT" },
            { "Knife", "KNIFE" }
        };
        
        static auto sanitize_weapon_name = [] (const char* name) -> std::string
        {
            std::string str = name;

            if (str.at(0) == 'C')
                str.erase(0, 1);

            if (str.find("Weapon") != std::string::npos)
                str.erase(0, 6);

            return sanitized_weapon_names[str];
        };

        if(player->IsAlly() && !Menu::weapon_ally)
            return;

        if(!player->IsAlly() && !Menu::weapon_enemy)
            return;
        
        BaseCombatWeapon* weapon = player->m_hActiveWeapon().Get();
        
        if(!weapon)
            return;
        
        if(!weapon->m_hOwnerEntity().IsValid())
            return;

        Renderer::DrawText(sanitize_weapon_name(weapon->GetClientClass()->m_pNetworkName), color, Vec2(right, top));
    }

    void GrenadeESP(BaseCombatWeapon* grenade)
    {
        
    }
}

