#pragma once
#include "Misc/Recv.h"
#include "Framework/Memory/FNV1a.h"

namespace NetvarManager {

    struct netvar_t
    {
        RecvProp* p_netvar;
        uint16_t offset;
    };

    inline std::unordered_map<uint32_t, std::unordered_map<uint32_t, netvar_t>> netvar_map;
    
    void Initialize();

    uint16_t GetOffset(uint32_t table_hash, uint32_t prop_hash);
    uint16_t GetOffset(const std::string_view table_name, const std::string_view prop_name);
}

#define NETVAR( type, func, table, var ) type& func() const \
{ \
static auto offset = NetvarManager::GetOffset( CT_FNV1A_HASH( table ), CT_FNV1A_HASH( var ) );\
return *reinterpret_cast< type* >( reinterpret_cast< uintptr_t >( this ) + offset );\
}

#define PNETVAR( type, func, table, var ) type* func() const \
{ \
static auto offset = NetvarManager::GetOffset( CT_FNV1A_HASH( table ), CT_FNV1A_HASH( var ) ); \
return reinterpret_cast< type* >( reinterpret_cast< uintptr_t >( this ) + offset ); \
}
