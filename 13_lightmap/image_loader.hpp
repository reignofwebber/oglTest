#ifndef IMAGE_LOADER_HPP
#define IMAGE_LOADER_HPP

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <GL/glew.h>

#include <iostream>

class ImageLoader
{
public:
    ImageLoader()
        : texture_type_(GL_TEXTURE_2D)
    {
        setDefault();
    }

    ImageLoader(unsigned texture_type)
        : texture_type_(texture_type)
    {
        setDefault();
    }

    ~ImageLoader(){}

    void setWrap(unsigned wrap_s, unsigned wrap_t)
    {
        wrap_s_ = wrap_s;
        wrap_t_ = wrap_t;
    }

    void setFilter(unsigned min_filter, unsigned mag_filter)
    {
        min_filter_ = min_filter;
        mag_filter_ = mag_filter;
    }

    bool load(const std::string &file, unsigned &texture_id)
    {
        glGenTextures(1, &texture_id);
        glBindTexture(texture_type_, texture_id);

        glTexParameteri(texture_type_, GL_TEXTURE_WRAP_S, wrap_s_);
        glTexParameteri(texture_type_, GL_TEXTURE_WRAP_T, wrap_t_);
        glTexParameteri(texture_type_, GL_TEXTURE_MIN_FILTER, min_filter_);
        glTexParameteri(texture_type_, GL_TEXTURE_MAG_FILTER, mag_filter_);

        int width, height, crChannels;
        unsigned char *data = stbi_load(file.c_str(), &width, &height, &crChannels, 0);
        if(!data)
        {
            std::cout << "[Texture Load]Failed to load " << file << std::endl;
            return false;
        }
        GLenum format;
        if(crChannels == 1) format = GL_RED;
        else if(crChannels == 3) format = GL_RGB;
        else if(crChannels == 4) format = GL_RGBA;

        glTexImage2D(texture_type_, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(texture_type_);

        stbi_image_free(data);
        return true;
    }    

private:

    void setDefault()
    {
        wrap_s_ = GL_REPEAT, wrap_t_ = GL_REPEAT;
        min_filter_ = GL_LINEAR, mag_filter_ = GL_LINEAR;
        // flip
        stbi_set_flip_vertically_on_load(true);
    }

    unsigned texture_type_;
    unsigned wrap_s_;
    unsigned wrap_t_;
    unsigned min_filter_;
    unsigned mag_filter_;
};

#endif //!IMAGE_LOADER_HPP