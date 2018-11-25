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
    void setMat4(const std::string &name, const glm::mat4 &val);

private:

    bool checkCompile(unsigned shader_id);

    bool checkLink(unsigned program_id);

    unsigned id_;
};


#endif //!SHADER_HPP