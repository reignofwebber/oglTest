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

    camera.processMouseMovement(xoffset, yoffset);
}

static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.processMouseScroll(yoffset);
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
    // std::cout << cameraFront_.x << " " << cameraFront_.y << " " << cameraFront_.z << std::endl;
    if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window_, true);
    }else if(glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.processKeyboard(Camera::FORWARD, deltaTime_);
    }else if(glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.processKeyboard(Camera::BACKWARD, deltaTime_);    
    }else if(glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.processKeyboard(Camera::LEFT, deltaTime_);                    
    }else if(glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.processKeyboard(Camera::RIGHT, deltaTime_);                            
    }
}

void Application::init()
{
    if(has_error_) return;
        
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    glGenBuffers(1, &vbo_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao_);    
    glBindVertexArray(vao_);    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &lampVao_);
    glBindVertexArray(lampVao_);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);
    glEnableVertexAttribArray(0);

    ImageLoader loader;
    loader.setFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    loader.setWrap(GL_REPEAT, GL_REPEAT);
    loader.load("container2.png", diffuseMap_);
    loader.load("container2_specular.png", specularMap_);

    lampShader_.setSource("lamp.vs", "lamp.fs");
    shader_.setSource("light.vs", "light.fs");
    shader_.use();
    shader_.setInt("material.diffuse", 0);
    shader_.setInt("material.specular", 1);
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

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    while(!glfwWindowShouldClose(window_))
    {
        float currentFrame = glfwGetTime();
        deltaTime_ = currentFrame - lastFrame_;
        lastFrame_ = currentFrame;
        processInput();
        glfwPollEvents();

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader_.use();
        // random light color
        // lightColor.x = sin(glfwGetTime() * 2.0f);
        // lightColor.y = sin(glfwGetTime() * 0.7f);
        // lightColor.z = sin(glfwGetTime() * 1.3f);

        glm::vec3 ambientColor = lightColor * glm::vec3(0.2f);
        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
        // Material
        shader_.setFloat("material.shininess", 32.0f);
        
        shader_.setVec3("light.ambient", ambientColor);
        shader_.setVec3("light.diffuse", diffuseColor);
        shader_.setVec3("light.specular", lightColor);
        shader_.setVec3("light.position", lightPos.x, lightPos.y, lightPos.z);

        // camera
        // coor
        glm::mat4 projection{1.0f};
        projection = glm::perspective(glm::radians(camera.getZoom()), 800.0f/600.0f, 0.1f, 100.0f);
        // projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

        glm::mat4 view = camera.getViewMatrix();
        shader_.setMat4("view", view);
        shader_.setMat4("projection", projection);
        shader_.setMat4("model", glm::mat4{1.0f});
        
        shader_.setVec3("viewPos", camera.getPosition());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap_);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap_);

        glBindVertexArray(vao_);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        lampShader_.use();
        lampShader_.setMat4("projection", projection);
        lampShader_.setMat4("view", view);
        glm::mat4 model{1.0f};
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3{0.2f});
        lampShader_.setMat4("model", model);
        lampShader_.setVec3("lightColor", lightColor);

        glBindVertexArray(lampVao_);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glfwSwapBuffers(window_);       
    }

    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
        
    return 0;
}