#include "Types.hpp"
#include "Core/ObjectLocation.hpp"

#ifndef OE_OBJECT_REFERENCE_HPP
#define OE_OBJECT_REFERENCE_HPP

template<typename T>
class ObjectReference
{
public:
    CommonID m_id;
    ObjectLocation m_location;


    ObjectReference(CommonID id);
    ObjectReference(CommonID id, ObjectLocation location);

    T* Get();
    bool IsValid();
    
    T* operator->();
};
#endif  

#ifndef OE_OBJECT_REFERENCE_IMPL
#define OE_OBJECT_REFERENCE_IMPL

#include "Systems/ObjectSystem.hpp"

template<typename T>
ObjectReference<T>::ObjectReference(CommonID id) : m_id(id), m_location(ObjectLocation::SCENE)
{}

template<typename T>
ObjectReference<T>::ObjectReference(CommonID id, ObjectLocation location) : m_id(id), m_location(location)
{}

template<typename T>
T* ObjectReference<T>::Get()
{
    return ObjectSystem::instance.GetObject(*this);
}

template<typename T>
T* ObjectReference<T>::operator->()
{
    if(this->m_id == 0)
        return nullptr;
    return Get();
}

template<typename T>
bool ObjectReference<T>::IsValid()
{
    return m_id != 0 && Get() != nullptr;
}

#endif
