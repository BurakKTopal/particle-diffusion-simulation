#include "../inc/TwoDimensionalRenderMachine.h"
#include <GLFW/glfw3.h>
namespace TwoDimensionalRenderMachine
{
    void fillGridBox(int row, int col, float r, float g, float b)
    {
        float xStart = -width / 2.0f * grid_spacing + col * grid_spacing + 0.1f;
        float yStart = -height / 2.0f * grid_spacing + row * grid_spacing + 0.1f;
        glColor3f(r, g, b);
        glBegin(GL_QUADS);
        glVertex2f(xStart, yStart);
        glVertex2f(xStart + grid_spacing - 0.2f, yStart);
        glVertex2f(xStart + grid_spacing - 0.2f, yStart + grid_spacing - 0.2f);
        glVertex2f(xStart, yStart + grid_spacing - 0.2f);
        glEnd();
    }

    void drawGrid()
    {
        glLineWidth(2.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);

        // Draw horizontal lines
        for (int i = 0; i <= height; ++i)
        {
            float y = -height / 2.0f * grid_spacing + i * grid_spacing;
            glVertex2f(-width / 2.0f * grid_spacing, y);
            glVertex2f(width / 2.0f * grid_spacing, y);
        }

        // Draw vertical lines
        for (int i = 0; i <= width; ++i)
        {
            float x = -height / 2.0f * grid_spacing + i * grid_spacing;
            glVertex2f(x, -width / 2.0f * grid_spacing);
            glVertex2f(x, height / 2.0f * grid_spacing);
        }

        glEnd();
    }

    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            cameraY -= 0.01f / zoom;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            cameraY += 0.01f / zoom;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            cameraX += 0.01f / zoom;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            cameraX -= 0.01f / zoom;

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void drawBoxes(Particle **particles)
    {
        size_t index = 0;
        while (particles[index] != NULL)
        {
            int pos = particles[index]->getPosition();
            int row = particles[index]->getPosition() / width;
            int col = particles[index]->getPosition() % width;
            if (particles[index]->getState() == MOVING)
            {
                fillGridBox((height - 1) - row, (width - 1) - col, 0.0f, 1.0f, 0.0f);
            }
            else
            {
                fillGridBox((height - 1) - row, (width - 1) - col, 1.0f, 0.0f, 0.0f);
            }
            index++;
        }
    }

    void render(GLFWwindow *window, Particle **particles)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glScalef(zoom, zoom, 1.0f);
        glTranslatef(cameraX, cameraY, 0.0f);
        drawGrid();
        // Drawing the boxes
        drawBoxes(particles);
        glfwSwapBuffers(window);
    }

}
