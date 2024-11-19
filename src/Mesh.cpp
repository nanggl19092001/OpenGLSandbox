#include "./mesh.hpp"

Mesh::Mesh()
{
    this->VAO = 0;
    this->VBO = 0;
    this->IBO = 0;
    this->indexNumber = 0;
    return;
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &this->VAO); 
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->IBO);
    this->indexNumber = 0;
}

void Mesh::create(const GLfloat *vertices, const GLuint *indices, const GLuint verticesNumber, const GLuint indicesNumber)
{
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indicesNumber, indices, GL_STATIC_DRAW);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * verticesNumber, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->indexNumber = indicesNumber;
}

void Mesh::draw()
{   glBindVertexArray(this->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);

    glDrawElements(GL_TRIANGLES, this->indexNumber, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}