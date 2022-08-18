#include "Object.hpp"
#include <string>
#include <glm/gtc/type_ptr.hpp>

EngineObject::EngineObject() : transform(glm::mat4(1.0f)), position({0,0,0}), scale({1,1,1}), rotation(glm::quat()), renderer(nullptr)
{

}

void EngineObject::SetPosition(glm::vec3 pos) { OBJ_SETDIRTY; position = pos;}
void EngineObject::SetScale(glm::vec3 sca)  { OBJ_SETDIRTY; scale = sca;}
void EngineObject::SetRotation(glm::quat rot) { OBJ_SETDIRTY; rotation = rot;}
void EngineObject::SetMatrix(glm::mat4 mat) { OBJ_CLEAR_DIRTY; transform = mat;}

glm::vec3 EngineObject::GetPosition() const { return position; }
glm::vec3 EngineObject::GetScale() const { return scale; }
glm::quat EngineObject::GetRotation() const { return rotation; }
glm::mat4 EngineObject::GetTransform() const
{ 
    if(flags & EngineObject::Flags::DirtyMat)
        UpdateTransform();
    return transform;     
}

glm::vec3* EngineObject::PtrPosition() { OBJ_SETDIRTY; return &position; }
glm::vec3* EngineObject::PtrScale() { OBJ_SETDIRTY; return &scale; }
glm::quat* EngineObject::PtrRotation() { OBJ_SETDIRTY; return &rotation; }
glm::mat4* EngineObject::PtrTransform() { return &transform; }


void EngineObject::UpdateTransform() const
{
    OBJ_CLEAR_DIRTY; 
    transform = glm::mat4(1.0f) * glm::mat4_cast(rotation); 
    transform = glm::scale(transform, scale);
    transform = glm::translate(transform, position);
}
