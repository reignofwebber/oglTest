#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main()
{
    // init glfw
    glfwInit();
    // set window hint
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // create window
    GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OGL", 0, 0);
    if(window == 0)
    {
        std::cout << "Failed to create GLFW window. " << std::endl;
        glfwTerminate();
        return -1;
    }
    

    return 0;
}