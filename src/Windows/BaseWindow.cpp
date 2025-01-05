#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <algorithm>

using namespace std;

struct BaseWindow
{
    virtual ~BaseWindow() = default;

    virtual GLFWwindow *createWindow(int width = 800, int height = 800, const char *title = "Base Window")
    {
        if (!glfwInit())
        {
            cerr << "Failed to initialize GLFW" << endl;
            exit(-1);
        }

        GLFWwindow *window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            exit(-1);
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            cerr << "Failed to initialize GLAD" << endl;
            glfwTerminate();
            exit(-1);
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        return window;
    }
    virtual GLFWwindow *initialize(int width, int height, const char *title) = 0;

protected:
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
};