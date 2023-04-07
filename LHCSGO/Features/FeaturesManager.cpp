#include "pch.h"
#include "FeaturesManager.h"

#include "Misc/PlayerList.h"
#include "Visuals/ESP.h"

void FeaturesManager::Initialize()
{
    PlayerList::Initialize();
    ESP::Initialize();
}

void FeaturesManager::Delete()
{
    PlayerList::Delete();
    ESP::Delete();
}

