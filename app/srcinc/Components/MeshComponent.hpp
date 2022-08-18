
#ifndef OE_MESH_COMPONENT
#define OE_MESH_COMPONENT
#include "Components/Component.hpp"
#include "Components/ComponentGenHpp.hpp"
#include "Mesh.hpp"

ComponentDefinition(MeshComponent, Component)

    Mesh* m_mesh;
};

// class MeshComponent : public Component
// {
// public:
//     static SObject properties;
//     MeshComponent(int comp_id);
//     MeshComponent();
//     void GetPropertiesLocal(std::vector<SObject *> &prop_list) override;
//     int GetID() override;
//     static void GetProperties(std::vector<SObject *> &prop_list);
//     static Component *create();
//     static const std::string GET_COMPONENT_NAME() { return "MeshComponent"; }
//     static int CID;

// private:
//     Mesh *m_mesh;
// };

#endif