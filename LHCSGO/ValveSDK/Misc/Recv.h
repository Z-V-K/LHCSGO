#pragma once

typedef enum
{
    DPT_Int = 0,
    DPT_Float,
    DPT_Vector,
    DPT_VectorXY,
    DPT_String,
    DPT_Array,
    DPT_DataTable,
    DPT_Int64,
    DPT_NUMSendPropTypes
} Type;

class RecvTable;
class RecvProp;
class CRecvProxyData;

typedef void(*ArrayLengthRecvProxyFn)(void *pStruct, int objectID, int currentArrayLength);
typedef void(*DataTableRecvVarProxyFn)(const RecvProp *pProp, void **pOut, void *pData, int objectID);
typedef void(*RecvVarProxyFn)(const CRecvProxyData *pData, void *pStruct, void *pOut);

class DVariant
{
public:
    union
    {
        float	 m_Float;
        long	 m_Int;
        char*    m_pString;
        void*    m_pData;
        float	 m_Vector[3];
        __int64  m_Int64;
    };
    Type  m_Type;
};

class CRecvProxyData
{
public:
    const RecvProp*     m_pRecvProp;
    DVariant		    m_Value;   
    int				    m_iElement;
    int				    m_ObjectID;
};

class RecvProp
{
public:
    char*                   m_pVarName;
    Type					m_RecvType;
    int                     m_Flags;
    int                     m_StringBufferSize;
    int                     m_bInsideArray;
    const void*             m_pExtraData;
    RecvProp*               m_pArrayProp;
    ArrayLengthRecvProxyFn  m_ArrayLengthProxy;
    RecvVarProxyFn          m_ProxyFn;
    DataTableRecvVarProxyFn m_DataTableProxyFn;
    RecvTable*              m_pDataTable;
    int                     m_Offset;
    int                     m_ElementStride;
    int                     m_nElements;
    const char*             m_pParentArrayPropName;

    RecvVarProxyFn			GetProxyFn() const;
    void					SetProxyFn(RecvVarProxyFn fn);
    DataTableRecvVarProxyFn	GetDataTableProxyFn() const;
    void					SetDataTableProxyFn(DataTableRecvVarProxyFn fn);

};

class RecvTable
{
public:
    RecvProp*               m_pProps;
    int                     m_nProps;
    void*                   m_pDecoder;
    char*                   m_pNetTableName;
    bool                    m_bInitialized;
    bool                    m_bInMainList;
};

inline RecvVarProxyFn RecvProp::GetProxyFn() const
{
    return m_ProxyFn;
}

inline void RecvProp::SetProxyFn(RecvVarProxyFn fn)
{
    m_ProxyFn = fn;
}

inline DataTableRecvVarProxyFn RecvProp::GetDataTableProxyFn() const
{
    return m_DataTableProxyFn;
}

inline void RecvProp::SetDataTableProxyFn(DataTableRecvVarProxyFn fn)
{
    m_DataTableProxyFn = fn;
}