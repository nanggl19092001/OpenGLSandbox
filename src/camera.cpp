#include "camera.hpp"

Camera::Camera()
{}
Camera::Camera(glm::vec3 sPosition, glm::vec3 sUp, GLfloat sYaw, GLfloat sPitch, GLfloat sMoveSpeed, GLfloat sTurnSpeed)
{
    this->position = sPosition;
    this->worldUp = sUp;
    this->yaw = sYaw;
    this->pitch = sPitch;
    this->front = glm::vec3(0.0f, 0.0f, 0.1f);

    this->movementSpeed = sMoveSpeed;
    this->turnSpeed = sTurnSpeed;

    this->update();
}

Camera::~Camera()
{
}

void Camera::keyControl(bool *keys, GLfloat deltaTime)
{
    GLfloat velocity = this->movementSpeed * deltaTime;

    if (keys[GLFW_KEY_W])
    {
        this->position += this->front * velocity;
    }

    if (keys[GLFW_KEY_S])
    {
        this->position -= this->front * velocity;
    }
    
    if (keys[GLFW_KEY_A])
    {
        this->position -= this->right * velocity;
    }

    if (keys[GLFW_KEY_D])
    {
        this->position += this->right * velocity;
    }
}

void Camera::mouseControl(bool* mouseButtons, GLfloat deltaTime, GLfloat xChange, GLfloat yChange)
{   
    if (!mouseButtons[GLFW_MOUSE_BUTTON_RIGHT])
    {
        return;
    }
    
    xChange *= this->turnSpeed * deltaTime;
    yChange *= this->turnSpeed * deltaTime;

    this->yaw += xChange;
    this->pitch += yChange;

    if  (pitch >= 89.9f)
    {
        pitch = 89.9f;
    }

    if (pitch <= -89.9f)
    {
        pitch = -89.9f;
    }
    
    this->update();
}
glm::mat4 Camera::calculateViewMatrix()
{
    return glm::lookAt(this->position, this->position + this->front, up);
}

void Camera::update()
{
    this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front.y = sin(glm::radians(this->pitch));
    this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

    this->front = glm::normalize(this->front);

    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up = glm::normalize(glm::cross(this->right, this->front));

}