#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    enum Camera_Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
    }; 
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
           float zoom = 45.0f, float yaw = 0.0f, float pitch = 0.0f);

    ~Camera();
    
    void processKeyboard(Camera_Movement dir, float deltaTime);

    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    void processMouseScroll(float yoffset);    

    glm::mat4 getViewMatrix();

    float getZoom();    

private:

    void updateCamera();

    glm::vec3 worldUp_;
    glm::vec3 position_, up_, front_, right_;
    float zoom_;
    float yaw_, pitch_;
    // move speed and mouse sensitivity
    float speed_{2.5f}, sensitivity_{0.1f};
};

#endif //!CAMERA_HPP