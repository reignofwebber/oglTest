#include <GL/glew.h>
#include <GLFW/glfw3.h>    
#include <iostream>
#include <fstream>

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

std::string initShaderSource(const char *filename)
{
    std::ifstream in(filename);
    if(!in.is_open())
    {
        std::cout << "can not open vertex_shader.glsl" << std::endl;
        return "";
    }
    //in >> std::noskipws;
    return std::string(std::istreambuf_iterator<char>(in), {});
}

void checkCompile(GLuint shader)
{
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR: " << infoLog << std::endl;
    }

}

void checkLink(GLuint shaderProgram)
{
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR: " << infoLog << std::endl;
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow *window = glfwCreateWindow(800,600,"Learn OpenGL", nullptr,nullptr);
    if(window == nullptr)
    {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glew
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW." << std::endl;
        return -1;
    }

    glViewport(0,0,800,600);

    //register callbacks
    glfwSetKeyCallback(window, key_callback);

    std::string s(initShaderSource("vertex_shader.glsl"));
    std::string s2(initShaderSource("fragment_shader.glsl"));
    const GLchar *vertexShaderSource = s.c_str();
    const GLchar *fragmentShaderSource = s2.c_str();


    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    checkCompile(vertexShader);

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    checkCompile(vertexShader);

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    checkLink(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    GLfloat vertices[] = {
        0.5f,0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        -0.5f,-0.5f,0.0f,
        -0.5f,0.5f,0.0f
    };

    GLuint indices[] = {
        0,1,2,
        0,2,3
    };
        
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    //wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        //render commands here.
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}