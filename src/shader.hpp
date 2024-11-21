#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
public:
    Shader();
    ~Shader();

    void createFromString(const char *vShader, const char *fShader);
    void createFromFile(const char *vShaderFilePath, const char *fShaderFilePath);

    void use();
    void clear();

    GLuint getProjectionUni();
    GLuint getModelViewUni();

    GLuint getViewUni();
    GLuint getTexUni();

    const char* projectionUniName = "projectionMatrix";
    const char* modelViewUniName = "modelViewMatrix";
    const char* viewUniName = "viewMatrix";
    const char* texUniName = "texUni";
private:
    GLuint shaderId, projectionUni, modelViewUni, viewUni, texUni;

    void compileShader(const char *vShader, const char *fShader);

    void addShader(GLuint program, const char *shaderCode, GLenum shaderType);
};
