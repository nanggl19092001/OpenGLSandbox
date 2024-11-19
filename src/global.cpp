#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "./struct.cpp"


GLuint VAO, VBO, IBO, shader, modelUniLocation, projectionUniLocation;

strUniMove uniMove;

glm::mat4 projectionMatrix;

float fov = 45.0f;
float aspect = (float)1024/(float)720;
float zNear = 0.1f;
float zFar = 100.0f;