#include <iostream>
#include <string>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "./const.h"

#include "./shader.cpp"
#include "./struct.cpp"
#include "./global.cpp"
#include "./input.cpp"

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void createTriangle()
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

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void addShader(GLenum shaderType, const char *shaderCode, GLuint shaderProgram)
{
    GLuint pShader = glCreateShader(shaderType);

    const GLchar *sCode[1];
    sCode[0] = shaderCode;

    GLint shaderLength[1];
    shaderLength[0] = strlen(shaderCode);

    glShaderSource(pShader, 1, sCode, shaderLength);
    glCompileShader(pShader);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glGetShaderiv(pShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(pShader, sizeof(eLog), NULL, eLog);
        std::cout << "Error Compile Shader: " << shaderType << eLog << std::endl;
        return;
    }
    glAttachShader(shaderProgram, pShader);
}

void compileShader()
{
    shader = glCreateProgram();

    if (!shader)
    {
        std::cout << "Create Shader Program Failed" << std::endl;
        return;
    }

    addShader(GL_VERTEX_SHADER, vShader, shader);
    addShader(GL_FRAGMENT_SHADER, fShader, shader);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        std::cout << "Error Linking Shader: " << eLog << std::endl;
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        std::cout << "Error In Shader: " << eLog << std::endl;
        return;
    }

    modelUniLocation = glGetUniformLocation(shader, C_TRANSFORMATION_UNIFORM);
    projectionUniLocation = glGetUniformLocation(shader, C_PROJECTION_UNIFORM);
}

int main()
{
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window;
    window = glfwCreateWindow(1024, 720, C_WINDOW_TITLE, NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to open GLFW window" << endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        glfwDestroyWindow(window);
        return -1;
    }

    glViewport(0, 0, 1024, 720);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    glEnable(GL_DEPTH_TEST);

    projectionMatrix = glm::perspective(fov, aspect, zNear, zFar);
    createTriangle();
    compileShader();

    while (!glfwWindowShouldClose(window))
    {

        if (uniMove.angY >= 360.0f)
        {
            uniMove.angY -= 360.0f;
        }

        uniMove.angY += 0.1f;
        
        glm::mat4 model4 = glm::mat4(1.0f);
        model4 = glm::scale(model4, glm::vec3(uniMove.size, uniMove.size, uniMove.size));
        model4 = glm::translate(model4, glm::vec3(uniMove.x, uniMove.y, -4.0f));
        model4 = glm::rotate(model4, uniMove.angX * C_TO_RAD, glm::vec3(1.0f, 0.0f, 0.0f));
        model4 = glm::rotate(model4, uniMove.angY * C_TO_RAD, glm::vec3(0.0f, 1.0f, 0.0f));
        model4 = glm::rotate(model4, uniMove.angZ * C_TO_RAD, glm::vec3(0.0f, 0.0f, 1.0f));

        glfwPollEvents();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

        glUniformMatrix4fv(modelUniLocation, 1, GL_FALSE, glm::value_ptr(model4));
        glUniformMatrix4fv(projectionUniLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}