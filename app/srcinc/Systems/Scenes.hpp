#ifndef OE_SCENES_HPP
#define OE_SCENES_HPP
#include <unordered_set>
#include <unordered_map>
#include "Core/Scene.hpp"
#include "InstanceSystem.hpp"
#include "Core/Types.hpp"

class Scenes
{
    public:
    static std::unordered_map<SceneID, Scene*> idToScene;
    static std::unordered_set<Scene*> scenes;

    static Scene* current;
    static InstanceSet<SceneID> scenesIds;

    static Scene* GetCurrent();

    static void LoadScene(SceneID scene);

    static SceneID CreateScene();

    static Scene* Get(SceneID id);
};

#endif