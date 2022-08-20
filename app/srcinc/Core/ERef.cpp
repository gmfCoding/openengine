
#ifndef OE_EREF_HPP
#define OE_EREF_HPP
#include "Core/Types.hpp"
namespace OE
{
    template<typename T>
    class Ref
    {
        CommonID instance;
        T* Get();
    };
}
#endif