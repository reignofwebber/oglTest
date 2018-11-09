#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.h"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}


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
    // make this window context current ?
    glfwMakeContextCurrent(window);
    
    // use advance features
    glewExperimental = GL_TRUE;
    // init glew
    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW." << std::endl;
        return -1;
    }

    // set view port
    glViewport(0, 0, 800, 600);
    // set key callback
    glfwSetKeyCallback(window, key_callback);

    // opengl start ........................................................
    GLfloat vertices[] = {
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    Shader shader("vertex_shader.glsl", "fragment_shader.glsl");

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);

        // use shader
        shader.use();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    

    return 0;
}