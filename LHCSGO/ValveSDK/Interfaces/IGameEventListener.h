#pragma once

#include "IGameEvent.h"

class IGameEventListener
{
public:
    virtual      ~IGameEventListener(void) {}

    virtual void FireGameEvent(IGameEvent *event) = 0;
    virtual int  GetEventDebugID(void) = 0;

public:
    int m_iDebugId;
};