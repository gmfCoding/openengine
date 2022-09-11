#include "Types.hpp"

#ifndef OE_OBJECT_REFERENCE_HPP
#define OE_OBJECT_REFERENCE_HPP
enum ObjectLocation
{
    ASSET,
    SCENE
};

template<typename T>
class ObjectReference
{
private:
    CommonID m_id;
    ObjectLocation m_location;

public:
    ObjectReference(CommonID id);
    ObjectReference(CommonID id, ObjectLocation location);
    bool IsValid();
    
    T* operator*();
    T* operator->();
};
#endif