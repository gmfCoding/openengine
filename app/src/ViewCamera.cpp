#include "ViewCamera.hpp"

#define OBJ_DIRTYMATRIX 0x0
#define OBJ_SETDIRTY flags |= ViewCamera::Flags::DirtyMat;
#define OBJ_CLEAR_DIRTY flags &= ~ViewCamera::Flags::DirtyMat;

ViewCamera::ViewCamera(float fov, float aspect, float near, float far) : transform(glm::mat4(1.0f)), position({0,0,0}), scale({1,1,1}), rotation(glm::quat())
{
    this->projection = glm::perspective(
        glm::radians(fov), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
        aspect,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
        near,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
        far             // Far clipping plane. Keep as little as possible.
    );
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(direction);
}

void ViewCamera::UpdateView()
{
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(direction);

    this->view = glm::lookAt(
        this->position,
        this->position + direction,
        up
    );
}

void ViewCamera::SetPosition(glm::vec3 pos) { OBJ_SETDIRTY; position = pos;}
void ViewCamera::SetScale(glm::vec3 sca)  { OBJ_SETDIRTY; scale = sca;}
void ViewCamera::SetRotation(glm::quat rot) { OBJ_SETDIRTY; rotation = rot;}
void ViewCamera::SetMatrix(glm::mat4 mat) { OBJ_CLEAR_DIRTY; transform = mat;}

glm::vec3 ViewCamera::GetPosition() const { return position; }
glm::vec3 ViewCamera::GetScale() const { return scale; }
glm::quat ViewCamera::GetRotation() const { return rotation; }
glm::mat4 ViewCamera::GetTransform() const
{ 
    if(flags & ViewCamera::Flags::DirtyMat)
        UpdateTransform();
    return transform;     
}

glm::vec3* ViewCamera::PtrPosition() { OBJ_SETDIRTY; return &position; }
glm::vec3* ViewCamera::PtrScale() { OBJ_SETDIRTY; return &scale; }
glm::quat* ViewCamera::PtrRotation() { OBJ_SETDIRTY; return &rotation; }
glm::mat4* ViewCamera::PtrTransform() { return &transform; }


void ViewCamera::UpdateTransform() const
{
    OBJ_CLEAR_DIRTY; 
    transform = glm::mat4(1.0f) * glm::mat4_cast(rotation); 
    transform = glm::scale(transform, scale);
    transform = glm::translate(transform, position);
}
