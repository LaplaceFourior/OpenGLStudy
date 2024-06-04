#include "Texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

#include <queue>

using namespace TenetEngine;

class TextureManager
{
public:
    TextureManager(unsigned int maxTextureNumber)
    {
        for (unsigned int i = 0; i < maxTextureNumber; i++) {
            freeTextureUnits.push(i);
        }
    }
public:
    unsigned int allocateTexture()
    {
        if (freeTextureUnits.empty()) {
            std::cerr << "No free texture units, please free some textures" << std::endl;
            return -1;
        }
        unsigned int unit = freeTextureUnits.front();
        freeTextureUnits.pop();
        return unit;
    }
    void freeTexture(unsigned int textureID)
    {
        freeTextureUnits.push(textureID);
    }
private:
    std::queue<unsigned int> freeTextureUnits;
};

TextureManager sTextureManager(32);

Texture::Texture(const std::string& filePath)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// x
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);// y
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    // flip the image
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if( data ) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind()
{
    if (texturePositionID == (unsigned int)-1) {
        unsigned int unit = sTextureManager.allocateTexture();
        if (unit != (unsigned int)-1) {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, texture);
            texturePositionID = unit;
        }
    } else {
        glActiveTexture(GL_TEXTURE0 + texturePositionID);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}

void Texture::unbind()
{
    if (texturePositionID != (unsigned int)-1) {
        sTextureManager.freeTexture(texturePositionID);
        texturePositionID = -1;
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}