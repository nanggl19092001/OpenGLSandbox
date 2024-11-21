#include "texture.hpp"

Texture::Texture()
{
    this->width = 0;
    this->height = 0;
    this->bitDepth = 0;
    this->texFileLoc = "";
}
Texture::Texture(const char *fileLoc)
{
    this->width = 0;
    this->height = 0;
    this->bitDepth = 0;
    this->texFileLoc = fileLoc;
}

Texture::~Texture()
{
    this->destroy();
}

void Texture::load()
{
    unsigned char *texData = stbi_load(this->texFileLoc, &this->width, &this->height, &this->bitDepth, 0);
    if (!texData)
    {
        std::cout << stbi_failure_reason() << std::endl;
        return;
    }
    
    glGenTextures(1, &this->texID);
    glBindTexture(GL_TEXTURE_2D, this->texID);

    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // std::cout << "1" << std::endl;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
    // std::cout << "2" << std::endl;
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    stbi_image_free(texData);
}

void Texture::use()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texID);
}

void Texture::destroy()
{
    glDeleteTextures(1, &this->texID);
    this->texID = 0;
    this->width = 0;
    this->height = 0;
    this->bitDepth = 0;
}
