#include "hashing.hpp"
#include "Core/Types.hpp"

template<typename T>
T Hashing::const_hash(char const *input) {
    return *input ? static_cast<T>(*input) + 33 * const_hash<T>(input + 1) : 5381;
}

CompID Hashing::cid_const_hash(char const* input)
{
    return *input ? static_cast<CompID>(*input) + 33 * cid_const_hash(input + 1) : 5381;
}