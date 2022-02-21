#include <iostream>
#include <glad/glad.h>
#include <math.h>
#include <GLFW/glfw3.h>
#define GLFW_INCLUDE_NONE
#include <memory>
const unsigned int WIDTH = 800, HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
// Fragment Shader source code
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
                                   "}\n\0";

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed initialization!" << std::endl;
    }
    //  GWFL SETTINGS
    //  version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //  letting GWFL know that we want only modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f};

    // Create glfw window
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Made", NULL, NULL);
    // making sure it was created succesfully
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Linking window with the current context
    glfwMakeContextCurrent(window);
    // loading glad for OpenGL configuration
    gladLoadGL();
    // sizing opengl
    glViewport(0, 0, WIDTH, HEIGHT);
    // color background
    glClearColor(0.00f, 0.3f, 0.3f, 1.0f);
    // clearing backbuffer and assigning the color background we created to it
    glClear(GL_COLOR_BUFFER_BIT);
    // swapping buffers
    glfwSwapBuffers(window);
    // running program
    while (!glfwWindowShouldClose(window))
    {
        // color mashup
        float time = glfwGetTime();
        glClearColor(sin(time + M_PI / 2), sin(time), cos(time + 3 * M_PI / 4), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        // handling window events
        glfwPollEvents();
    }
    // clearing pointers
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
