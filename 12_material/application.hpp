#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "camera.hpp"

static Camera camera{glm::vec3{0.0f, 0.0f, 3.0f}};
static float firstMouse{true};
static float lastCursorPosX_{800.0f / 2.0f}, lastCursorPosY_{600 / 2.0f};
static void mouse_callback(GLFWwindow *, double, double);
static void scroll_callback(GLFWwindow *, double, double);

class Application
{
public:
    Application();

    ~Application();
 
    void init();

    int exec();

private:
    static void framebuffer_size_callback(GLFWwindow *, int, int);
    
    void processInput();

    GLFWwindow *window_;
    bool has_error_;

    Shader lampShader_;
    Shader shader_;
    unsigned vao_, vbo_;
    unsigned lampVao_;

    float lastFrame_{0.0f}, deltaTime_{0.0f};
};

#endif //!APPLICATION_HPP