#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./shader.hpp"
#include "shader.hpp"

Shader::Shader()
{
    this->shaderId = 0;
    this->projectionUni = 0;
    this->modelViewUni = 0;
}

Shader::~Shader()
{
    this->clear();
}

void Shader::createFromString(const char *vShader, const char *fShader)
{
    this->compileShader(vShader, fShader);
}

void Shader::createFromFile(const char *vShaderFilePath, const char *fShaderFilePath)
{
    std::string vShader;
    std::string fShader;
    std::string lineTxtV, lineTxtF;

    // Read Vertex Shader File
    std::ifstream readFileV(vShaderFilePath);

    if (!readFileV.is_open())
    {
        std::cout << "Error reading Vertex Shader File" << std::endl;
        if (readFileV.bad())
        {
            std::cerr << "Fatal error: badbit is set." << std::endl;
        }

        if (readFileV.fail())
        {
            std::cerr << "Error details: " << strerror(errno)
                      << std::endl;
        }
        return;
    }

    while (std::getline(readFileV, lineTxtV))
    {
        vShader = vShader + lineTxtV + "\n";
    }
    readFileV.close();

    // //Read Fragment Shader File
    std::ifstream readFileF(fShaderFilePath);
    if (!readFileF.is_open())
    {
        std::cout << "Error reading Vertex Shader File" << std::endl;
        if (readFileF.bad())
        {
            std::cerr << "Fatal error: badbit is set." << std::endl;
        }

        if (readFileF.fail())
        {
            std::cerr << "Error details: " << strerror(errno)
                      << std::endl;
        }
        return;
    }

    while (std::getline(readFileF, lineTxtF))
    {
        fShader  = fShader + lineTxtF + "\n";
    }
    readFileF.close();

    this->compileShader(vShader.data(), fShader.data());
}

void Shader::use()
{
    glUseProgram(this->shaderId);
}

void Shader::clear()
{
    if (this->shaderId != 0)
    {
        glDeleteProgram(this->shaderId);
        this->shaderId = 0;
    }

    this->projectionUni = 0;
    this->modelViewUni = 0;
}

GLuint Shader::getProjectionUni()
{
    return this->projectionUni;
}

GLuint Shader::getModelViewUni()
{
    return this->modelViewUni;
}

GLuint Shader::getViewUni()
{
    return this->viewUni;
}
GLuint Shader::getTexUni()
{
    return this->texUni;
}
void Shader::compileShader(const char *vShader, const char *fShader)
{
    GLuint shader = glCreateProgram();

    if (!shader)
    {
        std::cout << "Create Shader Program Failed" << std::endl;
        return;
    }

    this->addShader(shader, vShader, GL_VERTEX_SHADER);
    this->addShader(shader, fShader, GL_FRAGMENT_SHADER);

    glLinkProgram(shader);
    GLint result = 0;
    GLchar eLog[1024] = {0};

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

    this->projectionUni = glGetUniformLocation(shader, this->projectionUniName);
    this->modelViewUni = glGetUniformLocation(shader, this->modelViewUniName);
    this->viewUni = glGetUniformLocation(shader, this->viewUniName);
    this->texUni = glGetUniformLocation(shader, this->texUniName);
    shaderId = shader;
}

void Shader::addShader(GLuint program, const char *shaderCode, GLenum shaderType)
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
    glAttachShader(program, pShader);
}
