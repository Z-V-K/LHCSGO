#pragma once
#include "ValveSDK/Interfaces/IHandleEntity.h"

#define NUM_ENT_ENTRY_BITS          (11 + 2)
#define NUM_ENT_ENTRIES             (1 << NUM_ENT_ENTRY_BITS)
#define INVALID_EHANDLE_INDEX       0xFFFFFFFF
#define NUM_SERIAL_NUM_BITS         16
#define NUM_SERIAL_NUM_SHIFT_BITS   (32 - NUM_SERIAL_NUM_BITS)
#define ENT_ENTRY_MASK              (( 1 << NUM_SERIAL_NUM_BITS) - 1)

class BaseHandle
{
    __forceinline BaseHandle() { m_Index = INVALID_EHANDLE_INDEX; }
    __forceinline BaseHandle(const BaseHandle &other) { m_Index = other.m_Index; }
    __forceinline BaseHandle(unsigned long value) { m_Index = value; }
    __forceinline BaseHandle(int iEntry, int iSerialNumber) { Init(iEntry, iSerialNumber); }

    __forceinline void Init(int iEntry, int iSerialNumber) { m_Index = iEntry | (iSerialNumber << NUM_ENT_ENTRY_BITS); }
    __forceinline void Term() { m_Index = INVALID_EHANDLE_INDEX; }
    
    __forceinline bool IsValid() const { return m_Index != INVALID_EHANDLE_INDEX; }

    __forceinline int GetEntryIndex() const { return m_Index & ENT_ENTRY_MASK; }
    __forceinline int GetSerialNumber() const { return m_Index >> NUM_ENT_ENTRY_BITS; }
    
    __forceinline const BaseHandle& operator=(const IHandleEntity *pEntity) { return Set(pEntity); }

    __forceinline const BaseHandle& Set(const IHandleEntity *pEntity) {
        if(pEntity) {
            *this = pEntity->GetRefEHandle();
        } else {
            m_Index = INVALID_EHANDLE_INDEX;
        }
        return *this;
    }
    
    IHandleEntity* Get() const;

protected:
    unsigned long	m_Index;
};
