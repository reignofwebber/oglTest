#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>

class Shader
{
public:
    GLuint ID;
    
    Shader(const char *vertexPath, const char *fragmentPath);

    // use shader
    void use();

    // get and set uniform
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

private:
    void checkCompile(GLuint shader);
    void checkLink(GLuint Program);

};






#endif