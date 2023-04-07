#include "pch.h"
#include "BaseHandle.h"

#include "ValveSDK/ValveSDK.h"

IHandleEntity* BaseHandle::Get() const
{
    return (IHandleEntity*) g_entitylist->GetClientEntityFromHandle(*this);
}
