#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static const GLchar* vShader = "                            \n\
#version 330                                                \n\
                                                            \n\
layout (location = 0) in vec3 pos;                          \n\
                                                            \n\
out vec4 vCol;                                              \n\
                                                            \n\
uniform float iMove;                                        \n\
uniform mat4 transformMatrix;                               \n\
uniform mat4 projectionMatrix;                               \n\
                                                            \n\
void main() {                                               \n\
                                                            \n\
    gl_Position = projectionMatrix * transformMatrix * vec4(pos, 1.0);         \n\
    vCol = vec4(clamp(pos, 0.0, 1.0), 1.0);                \n\
}                                                           \n\
";

static const GLchar* fShader = "        \n\
#version 330                            \n\
                                        \n\
in vec4 vCol;                      \n\
                                        \n\
out vec4 colour;                        \n\
                                        \n\
void main(){                            \n\
    colour = vec4(vCol);  \n\
}                                       \n\
";