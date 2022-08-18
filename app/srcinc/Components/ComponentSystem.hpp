#ifndef GMFC_COMPONENTSYSTEM_H
#define GMFC_COMPONENTSYSTEM_H
#include <map>
#include <string>
#include <vector>
#include "Core/Types.hpp"

class ComponentSystem
{
    public:
    std::map<std::string, CompID> componentNameMap;
    std::map<CompID, std::string> componentIdMap;
    std::map<CompID, std::string> component_relations;

    static ComponentSystem* instance;

    CompID Register(const std::string& name, const std::string& parent);
    static ComponentSystem* const Get();
    const std::string GetName(CompID id);
    bool Exists(std::string name);
};
#endif