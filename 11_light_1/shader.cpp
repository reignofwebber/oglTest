#include "shader.hpp"

// std
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>

// glew
#include <GL/glew.h>

Shader::Shader()
{

}

Shader::Shader(const std::string &v, const std::string &f)
{
    setSource(v, f);
}

void Shader::setSource(const std::string &v, const std::string &f)
{
    v_ = v, f_ = f;
    // read shader
    std::ifstream vfs(v), ffs(f);
    if(!vfs.is_open() || !ffs.is_open())
    {
        std::cout << "can not open shader file vertex or fragment" << std::endl;
    }

    std::string vs{std::istreambuf_iterator<char>(vfs), 
                   std::istreambuf_iterator<char>()};
    std::string fs{std::istreambuf_iterator<char>(ffs),
                   std::istreambuf_iterator<char>()};

    auto vSource = vs.c_str();
    auto fSource = fs.c_str();
    // compile vertex shader
    unsigned vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vSource, 0);
    glCompileShader(vertex);
    if(!checkCompile(vertex, GL_VERTEX_SHADER)) return;
    // compile fragment shader
    unsigned fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fSource, 0);
    glCompileShader(fragment);
    if(!checkCompile(fragment, GL_FRAGMENT_SHADER)) return;

    // link shader
    id_ = glCreateProgram();
    glAttachShader(id_, vertex);
    glAttachShader(id_, fragment);
    glLinkProgram(id_);
    if(!checkLink(id_)) return;
    // delete
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::setInt(const std::string &name, int val)
{
    glUniform1i(glGetUniformLocation(id_, name.c_str()), val);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &val)
{
    glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::setVec3(const std::string &name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(id_, name.c_str()), x, y, z);
}

Shader::~Shader()
{
    
}

bool Shader::checkCompile(unsigned shader_id, unsigned shader_type)
{
    int success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        std::string shader_type_s;
        char infoLog[512];
        glGetShaderInfoLog(shader_id, 512, 0, infoLog);
        if(shader_type == GL_VERTEX_SHADER) shader_type_s = "VERTEX SHADER " + v_;
        else shader_type_s = "FRAGMENT SHADER " + f_;
        std::cout << shader_type_s << " COMPILE ERROR: " << infoLog << std::endl;
        return false;
    }
    return true;
}

bool Shader::checkLink(unsigned program_id)
{
    int success;
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program_id, 512, 0, infoLog);
        std::cout << "LINK ERROR: " << infoLog << std::endl;
        return false;
    }
    return true;
}

void Shader::use()
{
    glUseProgram(id_);
}