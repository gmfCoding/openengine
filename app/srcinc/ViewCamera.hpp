#ifndef OE_VIEW_CAMERA
#define OE_VIEW_CAMERA
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

class ViewCamera
{   
public:

    enum Flags {
        DirtyMat    = 0b00000001,
        Example1    = 0b00000010,
        Example2    = 0b00000100,
        Example3    = 0b00001000,
        Example4    = 0b00010000,
        Example5    = 0b00100000,
        Example6    = 0b01000000,
        Example7    = 0b10000000 };

    mutable unsigned char flags;

    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 direction;

    float yaw = 225.0f;
    float pitch = 0.0f;

    ViewCamera(float fov, float aspect, float near, float far);
    void UpdateView();

    glm::vec3* PtrPosition();
    glm::vec3* PtrScale();
    glm::quat* PtrRotation();
    glm::mat4* PtrTransform();

    glm::vec3 GetPosition() const;
    glm::vec3 GetScale() const;
    glm::quat GetRotation() const;
    glm::mat4 GetTransform() const;

    void SetPosition(glm::vec3 pos);
    void SetScale(glm::vec3 pos);
    void SetRotation(glm::quat pos);
    void SetMatrix(glm::mat4 mat);

    void UpdateTransform() const;

    mutable glm::mat4 transform;
    
protected:
    glm::vec3 position;
    glm::vec3 scale;
    glm::quat rotation;


};

struct CameraControls
{
    bool Left;
    bool Right;
    bool Forward;
    bool Backwards;
    bool Down;
    bool Up;
};


#endif
