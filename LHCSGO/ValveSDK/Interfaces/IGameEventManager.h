#pragma once

#include "IGameEvent.h"
#include "IGameEventListener.h"

class bf_write;
class bf_read;

class IGameEventManager
{
public:
    virtual             ~IGameEventManager() = 0;
    virtual int         LoadEventsFromFile(const char *filename) = 0;
    virtual void        Reset() = 0;
    virtual bool        AddListener(IGameEventListener *listener, const char *name, bool bServerSide) = 0;
    virtual bool        FindListener(IGameEventListener *listener, const char *name) = 0;
    virtual int         RemoveListener(IGameEventListener *listener) = 0;
    virtual IGameEvent* CreateEvent(const char *name, bool bForce, unsigned int dwUnknown) = 0;
    virtual bool        FireEvent(IGameEvent *event, bool bDontBroadcast = false) = 0;
    virtual bool        FireEventClientSide(IGameEvent *event) = 0;
    virtual IGameEvent* DuplicateEvent(IGameEvent *event) = 0;
    virtual void        FreeEvent(IGameEvent *event) = 0;
    virtual bool        SerializeEvent(IGameEvent *event, bf_write *buf) = 0;
    virtual IGameEvent* UnserializeEvent(bf_read *buf) = 0;
};