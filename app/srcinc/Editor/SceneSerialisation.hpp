#ifndef OE_SCENE_SERIALISATION_HPP
#define OE_SCENE_SERIALISATION_HPP

#include "Core/Scene.hpp"

/// @brief Scene Serialisation Class for editor
class SceneSerialisation
{
    public:
    void Save(Scene& scene);

    void Load(const std::string& name);
};
#endif