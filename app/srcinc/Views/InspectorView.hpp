#ifndef OE_INSPECTOR_VIEW
#define OE_INSPECTOR_VIEW
#include <string>
#include <unordered_map>

#include "View.hpp"
#include "Entity.hpp"

class PropertyField;


ViewHeader(InspectorView, View)
public:

    std::string navigate_to; 
    static std::unordered_map<EntityID, std::unordered_set<InspectorView*>> inspectorEntities;
    static std::unordered_map<EntityID, std::string>  selectedEntityNames;
    std::string searchComponent = "";
    bool locked = false;
    Entity selected = {0, 0};

    void static RegisterCustomPropertyDrawer(std::string type, PropertyField* propertyDrawer);
    void OnDrawGUI() override;

    void SelectEntity(Entity entity);

    void AddToViewSystem() override;

    void OnObjectReferenceFind(ObjectReference<void> object, const std::string& find);

    static std::vector<InspectorView*> inspectors;
    static std::vector<InspectorView*> GetInspectors(bool includeLocked = true);

    static void SetAllSelectedEntity(Entity entity);

    static std::unordered_map<std::string, PropertyField*>& customPropertiesMap();

    virtual ImGuiWindowFlags GetFlags();
};

#endif