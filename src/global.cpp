#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "./struct.cpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "window.hpp"
#include "camera.hpp"

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

GLuint VAO, VBO, IBO, shader, modelUniLocation, projectionUniLocation, viewUniLocation, texUniLocation;

strUniMove uniMove;

glm::mat4 projectionMatrix;

Camera* camera;

float fov = 45.0f;
float aspect = (float)1024/(float)720;
float zNear = 0.1f;
float zFar = 100.0f;

GLsizei windowBufferWidth = 1024;
GLsizei windowBufferHeight = 720;