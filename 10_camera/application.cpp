#include "application.hpp"

#include <iostream>
#include <functional>

#include "image_loader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastCursorPosX_ = xpos;
        lastCursorPosY_ = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastCursorPosX_;
    float yoffset = ypos - lastCursorPosY_;
    lastCursorPosX_ = xpos;
    lastCursorPosY_ = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    s_yaw += xoffset;
    s_pitch += yoffset;

    if(s_pitch > 89.0f) s_pitch = 89.0f;
    if(s_pitch < -89.0f) s_pitch = -89.0f;
    glm::vec3 front;
    front.x = cos(glm::radians(s_pitch)) * cos(glm::radians(s_yaw));
    front.y = sin(glm::radians(s_pitch));
    front.z = sin(glm::radians(s_yaw)) * cos(glm::radians(s_pitch));
    std::cout << s_pitch << " " << s_yaw << " " <<  front.z << std::endl;
    cameraFront_ = glm::normalize(front);
}

static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    if(s_fov >= 1.0f && s_fov <= 45.0f)
        s_fov -= yoffset;
    if(s_fov <= 1.0f)
        s_fov = 1.0f;
    if(s_fov >= 45.0f)
        s_fov = 45.0f;
}

Application::Application()
    : window_(0), has_error_(false)
{
    // init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // create
    window_ = glfwCreateWindow(800, 600, "Learn OGL", 0, 0);
    if(window_ == 0)
    {
        std::cout << "Failed to create glfw window." << std::endl;
        has_error_ = true;
        return;
    }

    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, Application::framebuffer_size_callback);
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window_, mouse_callback);
    glfwSetScrollCallback(window_, scroll_callback);

    // use advance features
    glewExperimental = GL_TRUE;
    // init glew
    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to init glew." << std::endl;
        has_error_ = true;
        return; 
    }

    glViewport(0, 0, 800, 600);

}

Application::~Application()
{
    glfwTerminate();
}

void Application::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Application::processInput()
{
    float speed = 2.5f * deltaTime_;
    
    // std::cout << cameraFront_.x << " " << cameraFront_.y << " " << cameraFront_.z << std::endl;
    if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window_, true);
    }else if(glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos_ += speed * cameraFront_;
    }else if(glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos_ -= speed * cameraFront_;
    }else if(glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos_ -= glm::normalize(glm::cross(cameraFront_, cameraUp_)) * speed;
    }else if(glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos_ += glm::normalize(glm::cross(cameraFront_, cameraUp_)) * speed;
    }
}

void Application::init()
{
    if(has_error_) return;
        
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);

    glBindVertexArray(vao_);    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned container, face;
    ImageLoader loader;
 
    loader.load("container.jpg", container, GL_RGB); 
    loader.load("awesomeface.png", face, GL_RGBA);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, container);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, face);

    shader_.setSource("vertex_shader.glsl", "fragment_shader.glsl");
    shader_.use();
    // texture
    shader_.setInt("container", 0);
    shader_.setInt("face", 1);

}

int Application::exec()
{
    if(has_error_) return -1;
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    float i = 0.0f;
    while(!glfwWindowShouldClose(window_))
    {
        float currentFrame = glfwGetTime();
        deltaTime_ = currentFrame - lastFrame_;
        lastFrame_ = currentFrame;
        processInput();
        glfwPollEvents();

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // camera
        // coor
        glm::mat4 projection{1.0f};
        projection = glm::perspective(glm::radians(s_fov), 800.0f/600.0f, 0.1f, 100.0f);
        // projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

        glm::mat4 view = glm::lookAt(cameraPos_, cameraPos_ + cameraFront_, cameraUp_);
        shader_.use();        
        shader_.setMat4("view", view);
        // coor
        shader_.setMat4("projection", projection);
        
        for(auto i = 0; i < 10; ++i)
        {
            glm::mat4 model{1.0f};
            //model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 1.0f, 0.0f));
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));

            shader_.use();    
            shader_.setMat4("model", model);
            
            glBindVertexArray(vao_);
            glDrawArrays(GL_TRIANGLES, 0, 36);

        }

        glfwSwapBuffers(window_);       
    }

    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
        
    return 0;
}