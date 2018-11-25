#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

static float firstMouse{true};
static float lastCursorPosX_{800.0f / 2.0f}, lastCursorPosY_{600 / 2.0f};
static float s_yaw{-90.0f}, s_pitch{0.0f};
static glm::vec3 cameraFront_{0.0f, 0.0f, -1.0f};
static float s_fov{45.0f};
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

    Shader shader_;
    unsigned vao_, vbo_;

    glm::vec3 cameraPos_{0.0f, 0.0f, 3.0f};
    
    glm::vec3 cameraUp_{0.0f, 1.0f, 0.0f};
    
    float lastFrame_{0.0f}, deltaTime_{0.0f};
    
};

#endif //!APPLICATION_HPP