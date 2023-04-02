#pragma once

#include "../Classes/BaseHandle.h"

class IClientNetworkable;
class IClientEntity;
class BaseEntity;

class IClientEntityList
{
public:
    virtual IClientNetworkable*   GetClientNetworkable(int entNum) = 0;
    virtual void*                 GetClientNetworkableFromHandle(uint32_t hEnt) = 0;
    virtual void*                 GetClientUnknownFromHandle(uint32_t hEnt) = 0;
    virtual BaseEntity*           GetClientEntity(int entNum) = 0;
    virtual BaseEntity*           GetClientEntityFromHandle(BaseHandle hEnt) = 0;
    virtual int                   NumberOfEntities(bool bIncludeNonNetworkable) = 0;
    virtual int                   GetHighestEntityIndex() = 0;
    virtual void                  SetMaxEntities(int maxEnts) = 0;
    virtual int                   GetMaxEntities() = 0;
};