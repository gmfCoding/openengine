#ifndef OE_INSTNACESYSTEM
#define OE_INSTNACESYSTEM
#include <unordered_set>
#include <random>
#include "Core/Types.hpp"

template<typename T>
class InstanceSet
{
    std::unordered_set<T> activeInstances;
    public:
    T GetNew();
};

class InstanceSystem
{
    public:
    static InstanceSet<CommonID> identities;
};
#endif