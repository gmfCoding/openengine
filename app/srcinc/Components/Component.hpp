#ifndef GMFC_COMPONENT_H
#define GMFC_COMPONENT_H
#include "Components/ComponentSystem.hpp"
#include "Components/ComponentGenHpp.hpp"

#include <string>
#include <memory>
#include <unordered_map>

#include <vector>
#include "SObject.hpp"
#include "hashing.hpp"
#include <iostream>
#include "Core/Types.hpp"

class Component;
struct ComponentInfo
{
    typedef Component* (*create_f)();
    create_f creator;
    std::string name;
    CompID hash;
};


template<typename T, typename U> constexpr size_t offsetOf(U T::*member)
{
    return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

class Component
{
    COMPONENT_BASE_REGISTER(Component)

    public:
    CompID m_instanceID;
    int m_ComponentType;

    Component(CompID comp_id);

    static void GetProperties(std::vector<SObject*>& array);
    virtual int getExecutionOrder();
    virtual bool IsActiveComponent();
    virtual void GetPropertiesLocal(std::vector<SObject*>& prop_list) = 0;

    virtual ~Component() = default;

    virtual int GetID() { return Component::CID; }
    
    static void registrate(std::string const & name, ComponentInfo* ci);

    static Component* instantiate(CompID name);

    template <typename D>
    struct Registrar
    {
        explicit Registrar(std::string const & name, CompID* cid)
        {
            ComponentInfo* ci = new ComponentInfo();
            ci->creator = &D::create;
            ci->name = name;
            ci->hash = Hashing::cid_const_hash(name.c_str());
            Component::registrate(name, ci);
            *cid = ComponentSystem::Get()->Register(name, "");
            std::cout << "Registrar:" << name << *cid;
        }
    };

    public:
    static std::unordered_map<CompID, ComponentInfo*> & registry();
};


#endif


#ifndef GMFC_COMPONENT_ACTIVE_H
#define GMFC_COMPONENT_ACTIVE_H

//ComponentDefinition(ActiveComponent, Component)

class ActiveComponent : public Component { 
    

public:
    void GetPropertiesLocal(std::vector < SObject * > & prop_list) override;
    int GetID() override;
    static Component * create();

    COMPONENT_BASE_REGISTER(ActiveComponent) 
    
    
    ActiveComponent(CompID comp_id);
    ActiveComponent();

 static SObject properties;
 static void GetProperties(std::vector < SObject * > & prop_list);
 private:
 public:
    virtual void Awake() = 0;
    virtual void Start() = 0;
    virtual void Update() = 0;

    bool IsActiveComponent() override;
};
#endif