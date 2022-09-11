#include "Core/ObjectReference.hpp"
#include "Systems/ObjectSystem.hpp"


template<typename T>
ObjectReference<T>::ObjectReference(CommonID id) : m_id(id), m_location(ObjectLocation::SCENE)
{}

template<typename T>
ObjectReference<T>::ObjectReference(CommonID id, ObjectLocation location) : m_id(id), m_location(location)
{}

template<typename T>
T* ObjectReference<T>::operator->()
{
    if(this->m_id == 0)
        return nullptr;
    return ObjectSystem::instance.GetObject(this);
}

template<typename T>
T* ObjectReference<T>::operator*()
{
    return ObjectSystem::instance.GetObject(this);
}

template<typename T>
bool ObjectReference<T>::IsValid()
{
    return m_id != 0;
}