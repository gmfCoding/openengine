#include "Legacy/LegacyObject.hpp"
#include <string>
#include <glm/gtc/type_ptr.hpp>

LegacyObject::LegacyObject() : transform(glm::mat4(1.0f)), position({0,0,0}), scale({1,1,1}), rotation(glm::quat()), renderer(nullptr)
{

}

void LegacyObject::SetPosition(glm::vec3 pos) { OBJ_SETDIRTY; position = pos;}
void LegacyObject::SetScale(glm::vec3 sca)  { OBJ_SETDIRTY; scale = sca;}
void LegacyObject::SetRotation(glm::quat rot) { OBJ_SETDIRTY; rotation = rot;}
void LegacyObject::SetMatrix(glm::mat4 mat) { OBJ_CLEAR_DIRTY; transform = mat;}

glm::vec3 LegacyObject::GetPosition() const { return position; }
glm::vec3 LegacyObject::GetScale() const { return scale; }
glm::quat LegacyObject::GetRotation() const { return rotation; }
glm::mat4 LegacyObject::GetTransform() const
{ 
    if(flags & LegacyObject::Flags::DirtyMat)
        UpdateTransform();
    return transform;     
}

glm::vec3* LegacyObject::PtrPosition() { OBJ_SETDIRTY; return &position; }
glm::vec3* LegacyObject::PtrScale() { OBJ_SETDIRTY; return &scale; }
glm::quat* LegacyObject::PtrRotation() { OBJ_SETDIRTY; return &rotation; }
glm::mat4* LegacyObject::PtrTransform() { return &transform; }


void LegacyObject::UpdateTransform() const
{
    OBJ_CLEAR_DIRTY; 
    transform = glm::mat4(1.0f) * glm::mat4_cast(rotation); 
    transform = glm::scale(transform, scale);
    transform = glm::translate(transform, position);
}
