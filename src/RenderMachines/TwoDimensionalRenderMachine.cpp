#include "../../inc/RenderMachines/TwoDimensionalRenderMachine.h"
#include <glad/glad.h>

// Fills a grid box with the specified color
void TwoDimensionalRenderMachine::fillBox(int row, int col, float r, float g, float b)
{
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

// Draws the grid lines
void TwoDimensionalRenderMachine::drawSpace()
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

// Draws the boxes representing particles
void TwoDimensionalRenderMachine::drawBoxes(Particle **&particles)
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
        fillBox((GRID_HEIGHT - 1) - row, (GRID_WIDTH - 1) - col, r, g, 0.0f);
        index++;
    }
}
