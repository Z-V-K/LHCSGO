#pragma once
#include "Misc/Recv.h"

namespace NetvarManager {
    
    inline std::unordered_map<std::string, RecvTable*> tables { };
    
    void Initialize();
    int GetOffset(const char* table_name, const char* prop_name);
    int GetProperty(const char* table_name, const char* prop_name, RecvProp** prop = nullptr);
    int GetProperty(RecvTable* recv_table, const char* prop_name, RecvProp** prop = nullptr);
    RecvTable* GetTable(const char* table_name);
}

#define NETVAR(type, name, table, netvar)                           \
type& name () const {                                          \
static int _##name = NetvarManager::GetOffset(table, netvar);     \
return *(type*)((uintptr_t)this + _##name);                 \
}

#define NETVARADDOFFS(type, name, table, netvar, offs)                           \
type& name () const {                                          \
static int _##name = NetvarManager::GetOffset(table, netvar) + offs;     \
return *(type*)((uintptr_t)this + _##name);                 \
}

#define PNETVAR(type, name, table, netvar)                           \
type* name () const {                                          \
static int _##name = NetvarManager::GetOffset(table, netvar);     \
return (type*)((uintptr_t)this + _##name);                 \
}
