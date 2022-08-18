#ifndef OE_INSPECTOR_VIEW
#define OE_INSPECTOR_VIEW
#include <string>
#include "View.hpp"
#include "Entity.hpp"

ViewHeader(InspectorView, View)
public:
    std::string selectedEntityName;
    std::string searchComponent = "";
    Entity selected = {0, 0};
    void OnDrawGUI() override;

    void SelectEntity(Entity entity);
};

#endif