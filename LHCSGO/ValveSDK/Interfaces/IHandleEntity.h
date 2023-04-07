#pragma once

class BaseHandle;

class IHandleEntity
{
public:
public:
    virtual ~IHandleEntity() {}
    virtual void SetRefEHandle(const BaseHandle &handle) = 0;
    virtual const unsigned long& GetRefEHandle() const = 0;
};
