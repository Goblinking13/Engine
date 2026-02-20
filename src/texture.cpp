#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "texture.h"

#include <iostream>
#include <ostream>
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
#include<OpenGL/gl3.h>


game::texture::texture(const char *path) {

    glGenTextures(1, &tex_);
    glBindTexture(GL_TEXTURE_2D, tex_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::cout << "Texture created: " << path << " ID: " << tex_ << std::endl;

    // stbi_set_flip_vertically_on_load(true);
    unsigned char* textureData = stbi_load(path, &width_, &height_, &numberOfChannels_, 0 );
    if (textureData)
    {
        GLenum format;
        if (numberOfChannels_ == 1)
            format = GL_RED;
        else if (numberOfChannels_ == 3)
            format = GL_RGB;
        else if (numberOfChannels_ == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width_, height_, 0, format, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "TEXTURE::FAILED::LOAD" << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(textureData);

}


int game::texture::getHeight() const {
    return height_;
}

int game::texture::getWidth() const {
    return width_;
}

unsigned int game::texture::getTexture() const {
    return tex_;
}

void game::texture::bind() const {
    // glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex_);
}

