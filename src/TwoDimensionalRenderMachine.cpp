
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include "../inc/config.h"
#include "../inc/Particle.h"

namespace TwoDimensionalRenderMachine
{
    void fillGridBox(int row, int col, float r, float g, float b)
    {
        // Fill a grid box with the specified color
        float xStart = -GRID_WIDTH / 2.0f * GRID_SPACING + col * GRID_SPACING + 0.1f;
        float yStart = -GRID_HEIGHT / 2.0f * GRID_SPACING + row * GRID_SPACING + 0.1f;
        glColor3f(r, g, b);
        glBegin(GL_QUADS);
        glVertex2f(xStart, yStart);
        glVertex2f(xStart + GRID_SPACING - 0.2f, yStart);
        glVertex2f(xStart + GRID_SPACING - 0.2f, yStart + GRID_SPACING - 0.2f);
        glVertex2f(xStart, yStart + GRID_SPACING - 0.2f);
        glEnd();
    }

    void drawGrid()
    {
        glLineWidth(2.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);

        // Draw horizontal lines
        for (int i = 0; i <= GRID_HEIGHT; ++i)
        {
            float y = -GRID_HEIGHT / 2.0f * GRID_SPACING + i * GRID_SPACING;
            glVertex2f(-GRID_WIDTH / 2.0f * GRID_SPACING, y);
            glVertex2f(GRID_WIDTH / 2.0f * GRID_SPACING, y);
        }

        // Draw vertical lines
        for (int i = 0; i <= GRID_WIDTH; ++i)
        {
            float x = -GRID_WIDTH / 2.0f * GRID_SPACING + i * GRID_SPACING;
            glVertex2f(x, -GRID_HEIGHT / 2.0f * GRID_SPACING);
            glVertex2f(x, GRID_HEIGHT / 2.0f * GRID_SPACING);
        }

        glEnd();
    }

    void drawBoxes(Particle **&particles)
    {
        size_t index = 0;
        while (particles[index] != nullptr)
        {
            int pos = particles[index]->getPosition();
            int row = pos / GRID_WIDTH;
            int col = pos % GRID_WIDTH;

            // Set box color based on particle state
            float r = (particles[index]->getState() == MOVING) ? 0.0f : 1.0f;
            float g = (particles[index]->getState() == MOVING) ? 1.0f : 0.0f;
            fillGridBox((GRID_HEIGHT - 1) - row, (GRID_WIDTH - 1) - col, r, g, 0.0f);
            index++;
        }
    }

    void render(GLFWwindow *window, Particle **&particles)
    {
        // Clear the screen and set up the camera
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glScalef(zoom, zoom, 1.0f);
        glTranslatef(cameraX, cameraY, 0.0f);

        // Draw the grid and the boxes
        TwoDimensionalRenderMachine::drawGrid();
        TwoDimensionalRenderMachine::drawBoxes(particles);

        // Swap buffers to render
        glfwSwapBuffers(window);
    }

}