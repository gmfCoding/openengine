#ifndef OE_HIERARCHY
#define OE_HIERARCHY
#include "View.hpp"
#include "Entity.hpp"

class EntityHierarchyNode;

ViewHeader(HierarchyView, View)
public:
    Entity selected;
    void OnDrawGUI() override;

    void ImGui_RecurseStartDrawHeirarchy(Scene* scene);
    void ImGui_RecurseDrawHeirarchy(EntityHierarchyNode* node, Scene* scene);
};

#endif