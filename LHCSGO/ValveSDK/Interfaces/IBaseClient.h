#pragma once
#include "ValveSDK/Classes/ClientClass.h"
#include "ValveSDK/Classes/GlobalVars.h"

typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

class IBaseClient
{
public:
    virtual int              Connect(CreateInterfaceFn appSystemFactory, GlobalVars *pGlobals) = 0;
    virtual int              Disconnect() = 0;
    virtual int              Init(CreateInterfaceFn appSystemFactory, GlobalVars *pGlobals) = 0;
    virtual void             PostInit() = 0;
    virtual void             Shutdown() = 0;
    virtual void             LevelInitPreEntity(char const* pMapName) = 0;
    virtual void             LevelInitPostEntity() = 0;
    virtual void             LevelShutdown() = 0;
    virtual ClientClass*     GetAllClasses() = 0;
};
