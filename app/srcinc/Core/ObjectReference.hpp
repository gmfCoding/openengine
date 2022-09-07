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
    CommonID id;
    ObjectLocation location;

    T* operator->();
};
#endif