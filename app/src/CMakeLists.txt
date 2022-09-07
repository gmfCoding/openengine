cmake_minimum_required(VERSION 3.12)

set(LSOURCE 
main.cpp
ViewCamera.cpp
Input.cpp
Material.cpp
MaterialSystem.cpp
ViewCameraController.cpp
Rendering.cpp
GizmoLine.cpp
TextureManager.cpp
CommonData.cpp
hashing.cpp
Views/SceneView.cpp
Views/HierarchyView.cpp
Views/View.cpp
Views/InspectorView.cpp
Systems/InstanceSystem.cpp
Systems/ViewSystem.cpp
Systems/Scenes.cpp
Components/ActiveComponent.cpp
Components/Component.cpp
Components/ComponentSystem.cpp
Components/TransformComponent.cpp
Components/MeshComponent.cpp
Components/TestComponent.cpp
Legacy/LegacyObject.cpp
Core/Entity.cpp
Core/Scene.cpp
Editor/Editor.cpp
Editor/EditorViewSetup.cpp
SObject.cpp
)

list(TRANSFORM LSOURCE PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")

message(STATUS "[LSOURCE/extra] files: ${LSOURCE}")
set(SOURCES ${SOURCES} ${LSOURCE} PARENT_SCOPE)