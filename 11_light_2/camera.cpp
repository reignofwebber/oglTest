#include "camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, float zoom, float yaw, float pitch)
    : position_(position), worldUp_(up), 
      zoom_(zoom), yaw_(yaw), pitch_(pitch)
{
    updateCamera();
}

Camera::~Camera()
{

}

void Camera::updateCamera()
{
    glm::vec3 front;
    front.x = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = -cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front);

    right_ = glm::normalize(glm::cross(front_, worldUp_));
    up_ = glm::normalize(glm::cross(right_, front_));
}

void Camera::processKeyboard(Camera_Movement dir, float deltaTime)
{
    float velocity = speed_ * deltaTime;
    
    switch (dir)
    {
        case FORWARD:
            position_ += front_ * velocity;
            break;
        case BACKWARD:
            position_ -= front_ * velocity;
            break;
        case LEFT:
            position_ -= right_ * velocity;
            break;
        case RIGHT:
            position_ += right_ * velocity;
            break;
    
        default:
            break;
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= sensitivity_;
    yoffset *= sensitivity_;

    yaw_ += xoffset;
    pitch_ -= yoffset;

    if(constrainPitch)
    {
        if(pitch_ > 89.0f)
            pitch_ = 89.0f;
        if(pitch_ < -89.0f)
            pitch_ = -89.0f;
    }

    updateCamera();
}

void Camera::processMouseScroll(float yoffset)
{
    if(zoom_ >= 1.0f && zoom_ <= 45.0f)
        zoom_ -= yoffset;
    if(zoom_ <= 1.0f)
        zoom_ = 1.0f;
    if(zoom_ >=45.0f)
        zoom_ = 45.0f;
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position_, position_ + front_, up_);
}

float Camera::getZoom()
{
    return zoom_;
}

glm::vec3 Camera::getPosition()
{
    return position_;
}