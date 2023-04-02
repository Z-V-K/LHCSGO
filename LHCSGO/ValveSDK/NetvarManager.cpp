#include "pch.h"
#include "NetvarManager.h"

#include "ValveSDK.h"
#include "Classes/ClientClass.h"

void NetvarManager::Initialize()
{
    tables.clear();

    const ClientClass* client = g_baseclient->GetAllClasses();
    if (!client)
        return;

    while (client)
    {
        const auto recvTable = client->m_pRecvTable;

        if (recvTable)
            tables.emplace(std::string(client->m_pNetworkName), recvTable);

        client = client->m_pNext;
    }
}

int NetvarManager::GetOffset(const char* table_name, const char* prop_name)
{
    return GetProperty(table_name, prop_name);
}

int NetvarManager::GetProperty(const char* table_name, const char* prop_name, RecvProp** prop)
{
    RecvTable *recvTable = GetTable(table_name);
    
    if (!recvTable)
        return 0;

    return GetProperty(recvTable, prop_name, prop);
}

int NetvarManager::GetProperty(RecvTable* recv_table, const char* prop_name, RecvProp** prop)
{
    int extra_offset = 0;
    
    for (int i = 0; i < recv_table->m_nProps; i++)
    {
    	auto* recvProp = &recv_table->m_pProps[i];
    	const auto recvChild = recvProp->m_pDataTable;

    	if (recvChild && (recvChild->m_nProps > 0))
    	{
    		if (const int result = GetProperty(recvChild, prop_name, prop))
    			extra_offset += (recvProp->m_Offset + result);
    	}

    	if (strcmp(recvProp->m_pVarName, prop_name))
    		continue;

    	if (prop)
    		*prop = recvProp;
        
    	return (recvProp->m_Offset + extra_offset);
    }

    return extra_offset;
}

RecvTable* NetvarManager::GetTable(const char* table_name)
{
    if(tables.empty())
        return nullptr;

    for(const auto& t : tables)
    {
        if(strcmp(t.first.c_str(), table_name) == 0)
            return t.second;
    }

    return nullptr;
}