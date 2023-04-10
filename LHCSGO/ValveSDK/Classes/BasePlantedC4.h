#pragma once
#include "BaseEntity.h"

class BasePlantedC4 : public BaseEntity
{
public:
    NETVAR(EHandle<BasePlayer>, m_hBombDefuser, "DT_PlantedC4", "m_hBombDefuser")
    NETVAR(float, m_flC4Blow, "DT_PlantedC4", "m_flC4Blow")
    NETVAR(float, m_flDefuseCountDown, "DT_PlantedC4", "m_flDefuseCountDown")
    NETVAR(float, m_flTimerLength, "DT_PlantedC4", "m_flTimerLength")
    NETVAR(bool, m_bBombDefused, "DT_PlantedC4", "m_bBombDefused")
};
