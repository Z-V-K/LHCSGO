#pragma once
#include "BaseHandle.h"

template< class T >
class EHandle : public BaseHandle
{
public:

    EHandle();
    EHandle(int iEntry, int iSerialNumber);
    EHandle(const BaseHandle &handle);
    EHandle(T *pVal);

    // The index should have come from a call to ToInt(). If it hasn't, you're in trouble.
    static EHandle<T> FromIndex(int index);

    T*		Get() const;
    void	Set(const T* pVal);

    operator T*();
    operator T*() const;

    bool	operator !() const;
    bool	operator==(T *val) const;
    bool	operator!=(T *val) const;
    const   BaseHandle& operator=(const T *val);

    T*		operator->() const;
};
template<class T>
EHandle<T>::EHandle()
{
}

template<class T>
EHandle<T>::EHandle(int iEntry, int iSerialNumber)
{
    Init(iEntry, iSerialNumber);
}

template<class T>
EHandle<T>::EHandle(const BaseHandle &handle)
    : BaseHandle(handle)
{
}

template<class T>
EHandle<T>::EHandle(T *pObj)
{
    Term();
    Set(pObj);
}

template<class T>
inline EHandle<T> EHandle<T>::FromIndex(int index)
{
    EHandle<T> ret;
    ret.m_Index = index;
    return ret;
}

template<class T>
inline T* EHandle<T>::Get() const
{
    return (T*)BaseHandle::Get();
}

template<class T>
inline EHandle<T>::operator T *()
{
    return Get();
}

template<class T>
inline EHandle<T>::operator T *() const
{
    return Get();
}


template<class T>
inline bool EHandle<T>::operator !() const
{
    return !Get();
}

template<class T>
inline bool EHandle<T>::operator==(T *val) const
{
    return Get() == val;
}

template<class T>
inline bool EHandle<T>::operator!=(T *val) const
{
    return Get() != val;
}

template<class T>
void EHandle<T>::Set(const T* pVal)
{
    BaseHandle::Set(reinterpret_cast<const IHandleEntity*>(pVal));
}

template<class T>
inline const BaseHandle& EHandle<T>::operator=(const T *val)
{
    Set(val);
    return *this;
}

template<class T>
T* EHandle<T>::operator -> () const
{
    return Get();
}
