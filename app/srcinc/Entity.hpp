#ifndef GMFC_ENTITY_H
#define GMFC_ENTITY_H
#include <string>
#include <vector>

#include "Core/Types.hpp"

#define ENTITY_FLAG_ACTIVE 0x1
#define ENTITY_FLAG_INACTIVE 0x0

class Component;
class Scene;

struct Entity
{
public:
    EntityID id;
    SceneID scene;

public:
    std::string GetName();
    void SetName(std::string name);

    template <typename T>
    Component *GetComponent();

    template <typename T>
    std::vector<Component*> GetComponents();
    std::vector<Component*> GetAllComponents();

    template <typename T>
    T* AddComponent();

    Component* AddComponent(CompID id);

    template <typename T>
    void RemoveComponent();

    bool Exists();

    Scene *GetScene();

    size_t operator()() const noexcept
    {
        return static_cast<size_t>(id);
    }
};

constexpr bool operator==(const Entity &lhs, const Entity &rhs) { return lhs.id == rhs.id; }
constexpr bool operator!=(const Entity &lhs, const Entity &rhs) { return !(lhs == rhs); }
#endif