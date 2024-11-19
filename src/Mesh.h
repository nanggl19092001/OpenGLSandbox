#pragma once

#include <glad/glad.h>

class Mesh {
    public:
        Mesh();
        ~Mesh();

        void create(const GLfloat *vertices, const GLuint *indices, const GLuint verticesNumber, const GLuint indicesNumber);
        void draw();
        void destroy();
    private:
        GLuint VAO, VBO, IBO;
        GLuint indexNumber;
};