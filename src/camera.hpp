#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera();
    Camera(glm::vec3 sPosition, glm::vec3 sUp, GLfloat sYaw, GLfloat sPitch,GLfloat sMoveSpeed, GLfloat sTurnSpeed);
    ~Camera();

    void keyControl(bool *keys, GLfloat deltaTime);

    void mouseControl(bool* mouseButtons, GLfloat deltaTime, GLfloat xChange, GLfloat yChange);
    glm::mat4 calculateViewMatrix();
    void update();

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;

    GLfloat movementSpeed;
    GLfloat turnSpeed;

};
