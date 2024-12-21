#include "BaseWindow.cpp"
#include "../../inc/config.h"

struct GridWindow : public BaseWindow
{
    GLFWwindow *initialize(int width = 800, int height = 800, const char *title = "Grid Window") override
    {
        GLFWwindow *window = BaseWindow::createWindow(width, height, title);

        // Store this instance in the window's user pointer
        glfwSetWindowUserPointer(window, this);

        // Set up grid-specific framebuffer callback
        glfwGetFramebufferSize(window, &width, &height);
        framebuffer_size_callback(window, width, height);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        return window;
    }

protected:
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        float grid_length = max(GRID_HEIGHT, GRID_WIDTH);
        glOrtho(-grid_length / 2.0f * GRID_SPACING, grid_length / 2.0f * GRID_SPACING,
                -grid_length / 2.0f * GRID_SPACING, grid_length / 2.0f * GRID_SPACING,
                -1.0f, 1.0f);
    }
};