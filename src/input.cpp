#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "./struct.cpp"
#include "./global.cpp"

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    return;
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W){
        uniMove.y += 0.01;
    }
    if(key == GLFW_KEY_S){
        uniMove.y -= 0.01;
    }
    if(key == GLFW_KEY_A){
        uniMove.x -= 0.01;
    }
    if(key == GLFW_KEY_D){
        uniMove.x += 0.01;
    }
}