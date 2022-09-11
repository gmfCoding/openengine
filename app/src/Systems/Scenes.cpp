#include "Systems/Scenes.hpp"
#include "Core/Types.hpp"

InstanceSet<SceneID> Scenes::scenesIds;
std::unordered_map<SceneID, Scene*> Scenes::idToScene;
std::unordered_set<Scene*> Scenes::scenes;
Scene* Scenes::current;


Scene* Scenes::GetCurrent()
{
    return current;
}

void Scenes::LoadScene(SceneID scene)
{
    if(idToScene.count(scene))
        current = idToScene[scene];
}

SceneID Scenes::CreateScene()
{
    Scene* scene = new Scene();
    scene->sceneID = scenesIds.GetNew();
    idToScene.emplace(scene->sceneID, scene);
    scenes.emplace(scene);
    return scene->sceneID;
}

Scene* Scenes::Get(SceneID id)
{
    if(idToScene.count(id))
        return idToScene[id];

    return nullptr;
}

Entity Scenes::GetEntityFromComponentInstance(CommonID comp)
{
    Entity id = {0,0};
    for (auto &&i : scenes)
    {
        id = {i->GetEntityFromComponentInstance(comp), i->sceneID};
        if(id.id != 0)
            break;
    }
    return id;
}