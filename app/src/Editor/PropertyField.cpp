#include "Editor/PropertyField.hpp"
namespace std{
class string;

}

template<>
void PropertyField<int>::DrawField(int* data)
{

}

template<>
void PropertyField<float>::DrawField(float* data)
{

}

template<>
void PropertyField<std::string>::DrawField(std::string* data)
{

}

template<>
void PropertyField<long>::DrawField(long* data)
{

}