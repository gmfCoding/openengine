#include <string>
#include <iostream>

#ifndef OE_PROPERTYFIELD_HPP
#define OE_PROPERTYFIELD_HPP
class PropertyField
{
    std::string type;

    public:
    PropertyField(const std::string& name);

    virtual void DrawField(void* data)
    {

    };

    static PropertyField* Generate();
    static void Register(PropertyField* property);

    virtual ~PropertyField()
    {
        
    }
};

template<typename T>
struct PropertyFieldRegistrar
{
    explicit PropertyFieldRegistrar(std::string name)
    {
        PropertyField::Register(T::Generate());
    }
};
#endif
