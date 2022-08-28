#ifndef GMFC_ENTITY_H
#define GMFC_ENTITY_H

#ifdef OE_SRC_USE_PCH
#include "pch/pch.hpp"
#else
#include <string>
#include <vector>
#endif

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

    static Entity none;

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

    Entity GetParent();

    void SetParent(Entity entity, int index = -1);
    void SetIndex(int i);

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