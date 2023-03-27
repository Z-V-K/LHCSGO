#pragma once
#include "../Interfaces/IClientEntity.h"

class BaseEntity : public IClientEntity
{
public:
    bool is_player();
    bool is_weapon();
};
