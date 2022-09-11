#ifndef OE_SCENES_HPP
#define OE_SCENES_HPP

#ifdef OE_SRC_USE_PCH
#include "pch/pch.hpp"
#else
#include <unordered_set>
#include <unordered_map>
#endif

#include "Core/Scene.hpp"
#include "InstanceSystem.hpp"
#include "Core/Types.hpp"
#include "Core/ObjectReference.hpp"

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

    static Entity GetEntityFromComponentInstance(CommonID comp);
};

#endif