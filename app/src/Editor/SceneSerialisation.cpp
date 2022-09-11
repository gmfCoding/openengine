#include "Editor/SceneSerialisation.hpp"
#include <nlohmann/json.hpp>

void SceneSerialisation::Save(Scene& scene)
{
    nlohmann::json json;
    json["type"] = "scene";
    json["id"] = scene.sceneID;
    // for (auto &&i : scene.)
    // {
        
    // }
    
}

void SceneSerialisation::Load(const std::string& name)
{


}
