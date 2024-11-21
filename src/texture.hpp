#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "stb_image.h"

class Texture
{
public:
    Texture();
    Texture(const char* fileLoc);
    ~Texture();

    void load();

    void use();
    void destroy();

private:
    const char* texFileLoc;
    GLuint texID;
    int width, height, bitDepth;
};
