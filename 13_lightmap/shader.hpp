#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader();
    Shader(const std::string &v, const std::string &f);
    ~Shader();

    void setSource(const std::string &v, const std::string &f);
    void use();
    // set uniform value to shader location
    void setInt(const std::string &name, int val);
    void setFloat(const std::string &name, float val);
    void setMat4(const std::string &name, const glm::mat4 &val);
    void setVec3(const std::string &name, float x, float y, float z);
    void setVec3(const std::string &name, const glm::vec3 &val);

private:

    bool checkCompile(unsigned shader_id, unsigned shader_type);

    bool checkLink(unsigned program_id);

    unsigned id_;
    std::string v_, f_;
};


#endif //!SHADER_HPP