#include "Core/Types.hpp"

class Hashing
{
    public:
    template<typename T>
    static T const_hash(char const *input);

    static unsigned short us_const_hash(char const* input);
    static CompID cid_const_hash(char const* input);
};
