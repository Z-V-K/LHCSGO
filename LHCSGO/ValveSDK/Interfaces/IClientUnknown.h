#pragma once

#include "IHandleEntity.h"

class IClientUnknown : public IHandleEntity
{
public:
    virtual ICollideable* GetCollideable() = 0;
};