#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GL/glew.h>

#include <iostream>
#include <string>

class ImgLoader
{
public:
    ImgLoader()
        : texture_type(GL_TEXTURE_2D),
          wrap_s(GL_REPEAT),
          wrap_t(GL_REPEAT),
          min_filter(GL_LINEAR),
          mag_filter(GL_LINEAR),
          border_color{0}
    {
        // flip y
        stbi_set_flip_vertically_on_load(true);
    }

    void setWrap(int wrap_s, int wrap_t)
    {
        this->wrap_s = wrap_s;
        this->wrap_t = wrap_t;
    }

    void setFilter(int min_filter, int mag_filter)
    {
        this->min_filter = min_filter;
        this->mag_filter = mag_filter;
    }

    void setBorderColor(float color[])
    {
        for(auto i = 0; i < 4; ++i)
            border_color[i] = color[i];
    }

    void load(const std::string &path, unsigned int &oid, GLenum format=GL_RGB)
    {
        // gen and bind
        glGenTextures(1, &oid);
        glBindTexture(texture_type, oid);

        // set attrib
        glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, wrap_s);
        glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, wrap_t);
        glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, min_filter);
        glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, mag_filter);

        glTexParameterfv(texture_type, GL_TEXTURE_BORDER_COLOR, border_color);

        // load from path
        int width, height, crChannels;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &crChannels, 0);
        if(!data)
        {
            std::cout << "Failed to load image " << path;
            return;
        }

        // texture data and gen mipmap
        glTexImage2D(texture_type, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(texture_type);

        // free image
        stbi_image_free(data);
    }

private:
    int texture_type;
    int wrap_s;
    int wrap_t;
    int min_filter;
    int mag_filter;
    float border_color[4];
};


#endif