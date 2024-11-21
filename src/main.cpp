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
#include "./camera.cpp"
#include "./texture.cpp"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "stb_image.h"

using namespace std;

void createMesh()
{
    GLfloat vertices[] = {
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f, 0.5f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
        1.0f, -1.0f, -1.0f, 0.5f, 0.0f};

    GLuint indicies[] = {
        0, 2, 3,
        0, 1, 2,
        1, 2, 3,
        0, 1, 3};

    Mesh *mesh = new Mesh();
    mesh->create(vertices, indicies, 20, 12);   
    meshList.push_back(mesh);

    Mesh *mesh2 = new Mesh();
    mesh2->create(vertices, indicies, 20, 12);
    meshList.push_back(mesh2);
}

void createShader()
{
    Shader *shaderObj = new Shader();
    shaderObj->createFromFile("./src/content/shader/triangle.vert", "./src/content/shader/triangle.frag");
    shaderList.push_back(*shaderObj);
}

int main()
{

    Window mainWindow = Window(windowBufferWidth, windowBufferHeight);
    glViewport(0, 0, windowBufferWidth, windowBufferHeight);
    mainWindow.setCallbacks();

    glEnable(GL_DEPTH_TEST);

    camera = new Camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 10.0f);
    projectionMatrix = glm::perspective(fov, aspect, zNear, zFar);

    createMesh();
    createShader();
    Texture soilTex = Texture("./src/content/texture/dry_soil_texture.jpg");
    soilTex.load();
    Texture woodTex = Texture("./src/content/texture/images.png");
    woodTex.load();

    GLfloat deltaTime;
    GLfloat sTime = glfwGetTime();
    GLfloat eTime;
    while (!mainWindow.getShouldClose())
    {
        eTime = glfwGetTime();
        deltaTime = eTime - sTime;
        sTime = eTime;

        camera->keyControl(mainWindow.getKeys(), deltaTime);
        camera->mouseControl(mainWindow.getMouseButton(), deltaTime, mainWindow.getChangedX(), mainWindow.getChangedY());

        if (uniMove.angY >= 360.0f)
        {
            uniMove.angY -= 360.0f;
        }

        uniMove.angY += 90.0f * deltaTime;

        glfwPollEvents();

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0].use();
        modelUniLocation = shaderList[0].getModelViewUni();
        projectionUniLocation = shaderList[0].getProjectionUni();
        viewUniLocation = shaderList[0].getViewUni();
        texUniLocation = shaderList[0].getTexUni();

        glm::mat4 model4 = glm::mat4(1.0f);
        model4 = glm::scale(model4, glm::vec3(uniMove.size, uniMove.size, uniMove.size));
        model4 = glm::translate(model4, glm::vec3(uniMove.x - 1.0f, uniMove.y, -4.0f));
        model4 = glm::rotate(model4, glm::radians(uniMove.angX), glm::vec3(1.0f, 0.0f, 0.0f));
        model4 = glm::rotate(model4, glm::radians(uniMove.angY), glm::vec3(0.0f, 1.0f, 0.0f));
        model4 = glm::rotate(model4, glm::radians(uniMove.angZ), glm::vec3(0.0f, 0.0f, 1.0f));

        glUniformMatrix4fv(modelUniLocation, 1, GL_FALSE, glm::value_ptr(model4));
        glUniformMatrix4fv(projectionUniLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        glUniformMatrix4fv(viewUniLocation, 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));

        glUniform1i(texUniLocation, 0);

        soilTex.use();

        meshList[0]->draw();

        model4 = glm::mat4(1.0f);
        model4 = glm::scale(model4, glm::vec3(uniMove.size, uniMove.size, uniMove.size));
        model4 = glm::translate(model4, glm::vec3(uniMove.x + 1.0f, uniMove.y, -4.0f));
        model4 = glm::rotate(model4, glm::radians(uniMove.angX), glm::vec3(1.0f, 0.0f, 0.0f));
        model4 = glm::rotate(model4, glm::radians(-1.0f * uniMove.angY), glm::vec3(0.0f, 1.0f, 0.0f));
        model4 = glm::rotate(model4, glm::radians(uniMove.angZ), glm::vec3(0.0f, 0.0f, 1.0f));

        glUniformMatrix4fv(modelUniLocation, 1, GL_FALSE, glm::value_ptr(model4));
        // glUniformMatrix4fv(projectionUniLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        woodTex.use();

        meshList[1]->draw();

        mainWindow.swapBuffer();
    }

    mainWindow.~Window();
    return 0;
}