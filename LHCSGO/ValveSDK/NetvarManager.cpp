#include "pch.h"
#include "NetvarManager.h"

#include <d3d11sdklayers.h>

#include "ValveSDK.h"
#include "Classes/ClientClass.h"
#include "Framework/Memory/FNV1a.h"

void NetvarManager::Initialize()
{
    const ClientClass* client_data = g_baseclient->GetAllClasses();
    if (!client_data)
        return;

    const std::function<void(const char*, RecvTable*, size_t)> store = [&](const char* name, RecvTable * table, size_t offset = 0)
    {
        uint32_t var = 0, base = FNV1A_HASH(name);

        RecvProp* prop;
        RecvTable* child;
        
        for (int i = 0; i < table->m_nProps; ++i)
        {
            prop = &table->m_pProps[i];
            child = prop->m_pDataTable;
            
            if (child && child->m_nProps > 0)
                store(name, child, prop->m_Offset + offset);
            
            var = FNV1A_HASH(prop->m_pVarName);
            if (!netvar_map[base][var].offset)
            {
                netvar_map[base][var].p_netvar = prop;
                netvar_map[base][var].offset = (uint16_t)(prop->m_Offset + offset);
            }
        }
    };

    for (; client_data; client_data = client_data->m_pNext)
        store(client_data->m_pRecvTable->m_pNetTableName, client_data->m_pRecvTable, 0);
}

uint16_t NetvarManager::GetOffset(uint32_t table_hash, uint32_t prop_hash)
{
    return netvar_map[table_hash][prop_hash].offset;   
}

uint16_t NetvarManager::GetOffset(const std::string_view table_name, const std::string_view prop_name)
{
    return netvar_map[FNV1A_HASH(table_name.data())][FNV1A_HASH(prop_name.data())].offset;
}
