#include <iostream>
#include <string>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "./const.hpp"

#include "./shader.cpp"
#include "./struct.cpp"
#include "./global.cpp"
#include "./input.cpp"

#include "./mesh.cpp"
#include "./shader.cpp"
#include "./window.cpp"

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void createMesh()
{
    GLfloat vertices[] = {
        -1.0f, -1.0f, -1.0f,
        0.0f, -1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, -1.0f};

    GLuint indicies[] = {
        0, 2, 3,
        0, 1, 2,
        1, 2, 3,
        0, 1, 3
    };

    Mesh *mesh = new Mesh();
    mesh->create(vertices, indicies, 12, 12);
    meshList.push_back(mesh);

    Mesh *mesh2 = new Mesh();
    mesh2->create(vertices, indicies, 12, 12);
    meshList.push_back(mesh2);
}

void createShader(){
    Shader *shaderObj = new Shader();
    // shaderObj->createFromString(vShader, fShader);
    shaderObj->createFromFile("./src/content/shader/triangle.vert", "./src/content/shader/triangle.frag");
    shaderList.push_back(*shaderObj);
}

int main()
{

    Window mainWindow = Window( 1024, 720 );
    glViewport(0, 0, 1024, 720);
    mainWindow.setFrameBufferSizeCallback(framebuffer_size_callback);
    mainWindow.setKeyboardInputCallback(keyCallback);
    mainWindow.setMouseButtonCallback(mouseButtonCallback);

    glEnable(GL_DEPTH_TEST);

    projectionMatrix = glm::perspective(fov, aspect, zNear, zFar);
    createMesh();
    createShader();

    while (!mainWindow.getShouldClose())
    {

        if (uniMove.angY >= 360.0f)
        {
            uniMove.angY -= 360.0f;
        }

        uniMove.angY += 0.1f;

        glfwPollEvents();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0].use();
        modelUniLocation = shaderList[0].getModelViewUni();
        projectionUniLocation = shaderList[0].getProjectionUni();

        glm::mat4 model4 = glm::mat4(1.0f);
        model4 = glm::scale(model4, glm::vec3(uniMove.size, uniMove.size, uniMove.size));
        model4 = glm::translate(model4, glm::vec3(uniMove.x - 1.0f, uniMove.y, -4.0f));
        model4 = glm::rotate(model4, uniMove.angX * C_TO_RAD, glm::vec3(1.0f, 0.0f, 0.0f));
        model4 = glm::rotate(model4, uniMove.angY * C_TO_RAD, glm::vec3(0.0f, 1.0f, 0.0f));
        model4 = glm::rotate(model4, uniMove.angZ * C_TO_RAD, glm::vec3(0.0f, 0.0f, 1.0f));

        glUniformMatrix4fv(modelUniLocation, 1, GL_FALSE, glm::value_ptr(model4));
        glUniformMatrix4fv(projectionUniLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        meshList[0]->draw();

        model4 = glm::mat4(1.0f);
        model4 = glm::scale(model4, glm::vec3(uniMove.size, uniMove.size, uniMove.size));
        model4 = glm::translate(model4, glm::vec3(uniMove.x + 1.0f, uniMove.y, -4.0f));
        model4 = glm::rotate(model4, uniMove.angX * C_TO_RAD, glm::vec3(1.0f, 0.0f, 0.0f));
        model4 = glm::rotate(model4, -1.0f * uniMove.angY * C_TO_RAD, glm::vec3(0.0f, 1.0f, 0.0f));
        model4 = glm::rotate(model4, uniMove.angZ * C_TO_RAD, glm::vec3(0.0f, 0.0f, 1.0f));

        glUniformMatrix4fv(modelUniLocation, 1, GL_FALSE, glm::value_ptr(model4));
        // glUniformMatrix4fv(projectionUniLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        meshList[1]->draw();

        mainWindow.swapBuffer();
    }

    mainWindow.~Window();
    return 0;
}