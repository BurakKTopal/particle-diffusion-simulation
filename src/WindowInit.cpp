#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include "../inc/config.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float grid_length = max(GRID_HEIGHT, GRID_WIDTH);
    glOrtho(-grid_length / 2.0f * GRID_SPACING, grid_length / 2.0f * GRID_SPACING,
            -grid_length / 2.0f * GRID_SPACING, grid_length / 2.0f * GRID_SPACING,
            -1.0f, 1.0f);
}

GLFWwindow *initializeWindow()
{
    // Initialize GLFW and create a window
    if (!glfwInit())
    {
        cerr << "Failed to initialize GLFW" << endl;
        exit(-1);
    }

    GLFWwindow *window = glfwCreateWindow(800, 800, "Diffusion-limited-aggregation-simulation", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    // Initialize OpenGL loader (GLAD)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cerr << "Failed to initialize GLAD" << endl;
        exit(-1);
    }

    // Set up the framebuffer size callback
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    framebuffer_size_callback(window, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set the background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return window;
}