#include "pch.h"
#include "BasePlayer.h"

CUserCmd** BasePlayer::GetCurrentCommand()
{
    return *reinterpret_cast<CUserCmd***>((uintptr_t) this + (NetvarManager::GetOffset("DT_BasePlayer", "m_hViewEntity") - 0x4));
}

CUserCmd& BasePlayer::GetLastCommand()
{
    static const std::uintptr_t uLastCommandOffset = *reinterpret_cast<std::uintptr_t*>(Memory::PatternScan(GetModuleHandleA("client.dll"), "8D 8E ? ? ? ? 89 5C 24 3C") + 0x2);
    return *reinterpret_cast<CUserCmd*>((uintptr_t) this + uLastCommandOffset);
}

int BasePlayer::GetButtonDisabled()
{
    return *reinterpret_cast<CUserCmd***>((uintptr_t) this + (NetvarManager::GetOffset("DT_BasePlayer", "m_hViewEntity") - 0xC));
}

int BasePlayer::GetButtonForced()
{
    return *reinterpret_cast<CUserCmd***>((uintptr_t) this + (NetvarManager::GetOffset("DT_BasePlayer", "m_hViewEntity") - 0x8));
}

bool BasePlayer::PhysicsRunThink(int think_method)
{
    using PhysicsRunThinkFn = bool(__thiscall*)(void*, int);
    static auto oPhysicsRunThink = reinterpret_cast<PhysicsRunThinkFn>(Memory::PatternScan(GetModuleHandleA("client.dll"), "55 8B EC 83 EC 10 53 56 57 8B F9 8B 87"));
    return oPhysicsRunThink(this, think_method);
}

void BasePlayer::PostThink()
{
    using PostThinkVPhysicsFn = bool(__thiscall*)(BaseEntity*);
    static auto oPostThinkVPhysics = reinterpret_cast<PostThinkVPhysicsFn>(Memory::PatternScan(GetModuleHandleA("client.dll"), "55 8B EC 83 E4 F8 81 EC ? ? ? ? 53 8B D9 56 57 83 BB"));

    using SimulatePlayerSimulatedEntitiesFn = void(__thiscall*)(BaseEntity*);
    static auto oSimulatePlayerSimulatedEntities = reinterpret_cast<SimulatePlayerSimulatedEntitiesFn>(Memory::PatternScan(GetModuleHandleA("client.dll"), "56 8B F1 57 8B BE ? ? ? ? 83 EF 01 78 74"));

    g_mdlcache->BeginLock();

    if (this->IsAlive())
    {
        UpdateCollisionBounds();

        if (m_fFlags() & FL_ONGROUND)
            m_flFallVelocity() = 0.f;

        if (m_nSequence() == -1)
            SetSequence(0);

        StudioFrameAdvance();
        oPostThinkVPhysics(this);
    }

    oSimulatePlayerSimulatedEntities(this);

    g_mdlcache->EndLock();
}

const char* BasePlayer::GetRank()
{
    return (*g_playerresource)->GetCompetitiveRank(EntIndex());
}